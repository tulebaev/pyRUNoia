#ifndef PYTHON_PYWIDGET_H
#define PYTHON_PYWIDGET_H

#include <QtWidgets/QDockWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>

/** Python Widget
		This class is a Window for a Python interpreter interface.
		So it is possible to access all data in the running application in realtime with the script language.
		PyWidget also has the capablities to run a Python script from a file at startup, or on demand from the user.
*/
class PyWidget : public QDockWidget
{
	Q_OBJECT
public:
	PyWidget(QWidget* parent = 0, const char* title = 0);
	~PyWidget();
private slots:
	bool returnPressed();
	void appendOutput(const QString& text);
private:
	void startInterpreter();
	void keyPressEvent(QKeyEvent* e);
private:
	bool silent;
	QVector<QString> history;
	int historyPosition;
	bool running;
	QString currentScript;
	QLineEdit* lineEdit;
	QPlainTextEdit* output;
};

#endif // PYTHON_PYWIDGET_H
