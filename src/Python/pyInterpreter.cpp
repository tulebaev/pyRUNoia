// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// $Id: pyInterpreter.cpp,v 1.13.18.1 2007/03/25 21:42:50 oliver Exp $
//
#include "Python/pyInterpreter.h"

QString error_message;
PyObject* context;
QString PyInterpreter::start_log;
bool PyInterpreter::valid;

PyObject* runSingleString(const QString& str, int mode)
{
	// clear previous errors
	PyErr_Clear();
	error_message = "";
	// run the string through the interpreter
	PyObject* result = PyRun_String(str.toLatin1().constData(), mode, context, context);
	if (PyErr_Occurred())
	{
		PyObject* type;
		PyObject* value;
		PyObject* range;
		char* message;
		error_message = "ERROR: ";
		PyErr_Fetch(&type, &value, &range);
		if (PyArg_Parse(value, "s", &message))
		{
			error_message += message;
		}
		else
		{
			error_message += " (error message could not be parsed)";
		}
		PyErr_Print();
		error_message += "\n";
		return 0;
	}
	return result;
}

PyInterpreter::PyInterpreter()
{
	valid = false;
}

void PyInterpreter::finalize()
{
	if (Py_IsInitialized())
	{
		// TODO: for some reason, finalize crashes on Windows, at least if no python
		//       module has been found. We need to fix this correctly.
//#ifndef _MSC_VER
		Py_Finalize();
//#endif
	}
	valid = false;
}

void PyInterpreter::initialize()
{
	valid = false;
	start_log.clear();

	// finalize the interpreter if it is already running
	if (Py_IsInitialized())
	{
		Py_Finalize();
	}

	// initialize the interpreter
	Py_Initialize();

	// get a borrowed reference to the __main__ module
	PyObject* main_module = PyImport_AddModule("__main__");
	if (main_module == NULL)
	{
		//Log.error() << "Python intialization failed: could not add \"__main__\" module! No Python support available." << std::endl;
		return;
	}

	// and create a valid context for our further Python calls
	context = PyModule_GetDict(main_module);
	if (context == NULL)
	{
		//Log.error() << "Could not get valid context for Python module \"__main__\"! No Python support available." << std::endl;
		return;
	}

	// import sys
	runSingleString("import sys", Py_single_input);
	start_log += error_message;

	// import the site module, and the one required for the output redirection
	runSingleString("import site, cStringIO", Py_single_input);
	start_log += error_message;

	valid = true;
}

PyObject* loadModule(const QString& name)
{
	PyObject* module_dict = PyImport_GetModuleDict();
	if (!module_dict)
	{
		//Log.error() << "Could not obtain module dictionary" << std::endl;
		return 0;
	}

	PyObject* mod_name = PyString_FromString(name.toLatin1().data());
	PyObject* module = 0;
	if (PyDict_Contains(module_dict, mod_name))
	{
		module = PyDict_GetItem(module_dict, mod_name);
	}
	else
	{
		//This could leak the imported module. Need to check...
		module = PyImport_ImportModule(name.toLatin1().data());
	}

	Py_XDECREF(mod_name);

	if (!module || PyErr_Occurred())
	{
		PyErr_Print();
		return 0;
	}

	return module;
}

bool PyInterpreter::execute(const QString& module, const QString& func_name, const QList<QPair<QString, QString> >& params)
{
	PyObject* mod = loadModule(module);
	if (mod == NULL)
	{
		//Log.error() << "Could not load module " << module.toAscii().data() << std::endl;
		return false;
	}

	PyObject* func = PyObject_GetAttrString(mod, func_name.toLatin1().data());
	if (!func || !PyCallable_Check(func))
	{
		PyErr_Print();
		return false;
	}

	PyObject* dict = PyDict_New();
	if (!dict)
	{
		//Log.error() << "Error: Could not create named arguments dictionary" << std::endl;
		return false;
	}

	for (QList<QPair<QString, QString> >::const_iterator it = params.begin(); it != params.end(); ++it)
	{
		if (it->first == "action" || it->first == "module" || it->first == "method")
		{
			continue;
		}

		PyObject* val = PyString_FromString(it->second.toLatin1().data());
		if (!val)
		{
			//Log.error() << "Could not create parameter" << it->first.toAscii().data() << "=" << it->second.toAscii().data() << " Skipping." << std::endl;
			continue;
		}

		PyDict_SetItemString(dict, it->first.toLatin1().data(), val);
	}

	Py_DECREF(dict);

	PyObject* dummy = PyTuple_New(0);
	if (!dummy)
	{
		//Log.error() << "Could not allocate dummy tuple" << std::endl;
		return false;
	}

	PyObject* res = PyObject_Call(func, dummy, dict);
	Py_XDECREF(res);
	Py_DECREF(dummy);

	return true;
}

QString PyInterpreter::run(const QString& code, bool& state)
{
	if (!valid) return "";

	state = false;
	if (runSingleString("CIO = cStringIO.StringIO()", Py_single_input) == 0 ||
	    runSingleString("stdout=sys.stdout", Py_single_input) == 0 ||
	    runSingleString("stderr=sys.stderr", Py_single_input) == 0 ||
	    runSingleString("sys.stdout=CIO", Py_single_input) == 0 ||
	    runSingleString("sys.stderr=CIO", Py_single_input) == 0)
	{
		return error_message;
	}

	state = (runSingleString(code, Py_single_input) != 0);
	QString runError(error_message);

	// retrieve output
	char* buf = 0;
	PyObject* result = runSingleString("str(CIO.getvalue())", Py_eval_input);
	if (result != 0)
	{
		PyArg_Parse(result, "s", &buf);
	}
	runSingleString("sys.stdout=stdout", Py_single_input);
	runSingleString("sys.stderr=stderr", Py_single_input);

	if (state)
		return QString(buf);
	else
		return runError;
}

bool PyInterpreter::runFile(const QString& filename)
{
	if (!valid) return false;

	const char* fileName = filename.toLatin1().constData();
	FILE* file = fopen(fileName, "r");
	if (!file)
	{
		//throw Exception::FileNotFound(__FILE__, __LINE__, filename);
		return false;
	}

	PyErr_Clear();
	PyRun_SimpleFileEx(file, fileName, true);
	if (PyErr_Occurred())
	{
		//std::cout << "Error occured while executing " << filename << "\nPrinting Traceback:" << std::endl;
		PyErr_Print();
		return false;
	}

	return true;
}
