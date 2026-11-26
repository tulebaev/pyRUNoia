// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// $Id: pyInterpreter.cpp,v 1.13.18.1 2007/03/25 21:42:50 oliver Exp $
//
#include "Python/pyInterpreter.h"
#include <Python.h>

bool PyInterpreter::valid;
PyObject* PyInterpreter::context;
//PyInterpreter::PathStrings PyInterpreter::sys_path;

PyObject* pyRUNnoia_save(PyObject* self);

PyDoc_STRVAR(save_method_doc, "Save current configuration to the disk.");
static PyMethodDef pyRUNnoia_methods[] = {
	{"save", (PyCFunction)pyRUNnoia_save, METH_NOARGS, save_method_doc},
	{NULL, NULL, 0, NULL}
};

PyDoc_STRVAR(module_doc, "pyRUNnoia module");
static struct PyModuleDef pyRUNnoia_module = {
	PyModuleDef_HEAD_INIT,
	"pyRUNnoia",
	module_doc,
	-1,
	pyRUNnoia_methods
};

PyMODINIT_FUNC init_pyRUNnoia(void) { return PyModule_Create(&pyRUNnoia_module); }

void PyInterpreter::initialize()
{
	valid = false;

	// finalize the interpreter if it is already running
	if (Py_IsInitialized())
	{
		Py_Finalize();
	}

	PyImport_AppendInittab(pyRUNnoia_module.m_name, init_pyRUNnoia);

	// initialize the interpreter
	Py_Initialize();

	// Create a valid context for our further Python calls
	context = PyDict_New();
	valid = (context != NULL);

	auto code = std::string("from ") + std::string(pyRUNnoia_module.m_name) + std::string(" import *");
	valid = valid && (PyRun_String(code.c_str(), Py_single_input, context, NULL) != NULL);
}

void PyInterpreter::finalize()
{
	if (Py_IsInitialized())
	{
		Py_DECREF(context);
		Py_Finalize();
	}
	valid = false;
}

PyObject* loadModule(const QString& name)
{
	PyObject* module_dict = PyImport_GetModuleDict();
	if (!module_dict)
	{
		//Log.error() << "Could not obtain module dictionary" << std::endl;
		return 0;
	}

	PyObject* mod_name = PyUnicode_FromString(name.toLatin1().data());
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

		PyObject* val = PyUnicode_FromString(it->second.toLatin1().data());
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

QString PyInterpreter::run(const QString& code)
{
	if (!valid) return QString::null;
	QString message;

	// Run the string through the interpreter
	PyObject* result = PyRun_String(code.toLatin1().constData(), Py_single_input, context, NULL);
	if (result == NULL) { //PyErr_Occurred()
		PyObject *type, *value, *traceback;
		PyErr_Fetch(&type, &value, &traceback);
		if (value) {
			auto error_type = QString(value->ob_type->tp_name);
			if (error_type == "SyntaxError") {
				PyObject* obj = PyObject_GetAttrString(value, "text");
				if (obj) {
					message += QString(PyUnicode_AsUTF8(obj));
					message += '\n';
					Py_DECREF(obj);
				}
				obj = PyObject_GetAttrString(value, "offset");
				if (obj && PyLong_Check(obj)) {
					auto offset = PyLong_AsLong(obj);
					message += QString(offset, ' ');
					message += '^';
					message += '\n';
					Py_DECREF(obj);
				}
				obj = PyObject_GetAttrString(value, "msg");
				if (obj) {
					message += error_type;
					message += ": ";
					message += QString(PyUnicode_AsUTF8(obj));
					message += '\n';
					Py_DECREF(obj);
				}
			}
			else {
				message += error_type;
				message += ": ";
				message += QString(PyUnicode_AsUTF8(PyObject_Str(value)));
				message += '\n';
			}
		}
		PyErr_Clear();
	}

	return message;
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
