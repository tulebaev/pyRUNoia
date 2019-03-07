// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// $Id: pyInterpreter.h,v 1.15.18.1 2007/03/25 21:25:21 oliver Exp $ 
//

#ifndef PYTHON_PYINTERPRETER_H
#define PYTHON_PYINTERPRETER_H

#include <Python.h>
#include <QtCore/QList>
#include <QtCore/QPair>
//#include <QtCore/QVector>
#include <QtCore/QString>
  #include <QtCore\qdebug.h>

/** Embedded Python interpreter.
		There's just one global instance of the interpreter,
		so all methods are static. The use of subinterpreters
		is not yet supported.
		\ingroup PythonExtensions
*/
class PyInterpreter
{
private:
	// We don't want anybody to instantiate this!
	PyInterpreter();
	~PyInterpreter() {}

public:
	/**	@name Type definitions */
	//@{
	/// Used to encode the individual paths appended to sys.path for dynamic loading of modules.
	typedef QVector<QString> PathStrings;
	//@}

	/**	@name Initialization */
	//@{

	/**	Initialize the interpreter.
			Initialize the interpreter (by calling <tt>Py_Initialize</tt>)
			and load the module <tt>sys</tt>.
			A second call to <tt>initialize</tt> may be used to restart the intepreter.
			Upon start, the paths defined by \link setSysPath \endlink are added to sys.path.
			If your interpreter cannot load specific modules, add the location of your
			modules here.
	*/
	static void initialize();

	/**	Stop the interpreter.
			Deallocate all memory occupied by the interpreter
			(by calling <tt>PY_Finalize</tt>.
	*/
	static void finalize();

	///	Append additional search paths to sys.path upon initialization
	//static void setSysPath(const PathStrings& path_strings) { sys_path = path_strings; }

	///	Get the current paths added to sys.path
	//static const PathStrings& getSysPath() { return sys_path; }

	///
	static bool isValid() { return valid; }

	///
	static QString getStartupLog() { return start_log; }

	//@}

	/**	@name Execution */
	//@{
	/**	Execute a string.
			@param code the string to run (may contain multiple lines with correct indentation)
			@param result bool reference which contains the result after call of function
			@return the output of the interpreter (may also contain error messages)
	*/
	static QString run(const QString& code, bool& result);

	/**	Run a Python program from a file.
			@param file_name the name of the program file
	*/
	static bool runFile(const QString& filename);

	/**	Import a module.
			The module with name <tt>module_name</tt> is imported
			using <tt>PyImport_ImportModule</tt> and initialized.
			When called
			@return true if the modules was found an initialized correctly
	*/
	static bool importModule(const QString& module_name);
	//@}

	static bool execute(const QString& module, const QString& func, const QList<QPair<QString, QString> >& params);

protected:
	static bool valid;
	static QString start_log;
	//static PathStrings sys_path;
};

#endif // PYTHON_PYINTERPRETER_H
