#include "Python/pyWidget.h"
#include "Python/pyInterpreter.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>

PyWidget::PyWidget(QWidget* parent, const char* title)
	:	QDockWidget(title, parent),
		silent(false),
		running(false),
		historyPosition(0)
{
	output = new QPlainTextEdit;
	output->setReadOnly(true);
	output->setFrameShape(QFrame::NoFrame);
	output->setToolTip("Output for Python commands");

	lineEdit = new QLineEdit;
	lineEdit->setFrame(false);
	lineEdit->setToolTip("Enter a Python command and press return for execution");
	connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));

	QWidget* mainArea = new QWidget(this);
	QVBoxLayout* layout = new QVBoxLayout;
	QHBoxLayout* commandArea = new QHBoxLayout;
	QLabel* prompt = new QLabel(">");
	prompt->setFrameShape(QFrame::NoFrame);
	prompt->setStyleSheet("QLabel { background-color : white; }");
	commandArea->addWidget(prompt);
	commandArea->addWidget(lineEdit);
	layout->addWidget(output);
	layout->addLayout(commandArea);
	layout->setMargin(0); layout->setSpacing(0);
	mainArea->setLayout(layout);
	setWidget(mainArea);

	startInterpreter();
	if (!PyInterpreter::isValid())
	{
		setEnabled(false);
		appendOutput("No Python support available!");
		//statusBar()->showMessage("No Python support available!");
		return;
	}

	lineEdit->setFocus();
}

PyWidget::~PyWidget()
{
	history.clear();
	PyInterpreter::finalize();
}

void PyWidget::appendOutput(const QString& text)
{
	if (silent) return;
	output->insertPlainText(text);
}

void PyWidget::keyPressEvent(QKeyEvent* event)
{
	if (history.isEmpty()) return;
	bool retrieveHistory = false;
	switch (event->key())
	{
		case Qt::Key_Up:
			historyPosition--;
			if (historyPosition < 0) historyPosition = 0;
			retrieveHistory = true;
			break;
		case Qt::Key_Down:
			historyPosition++;
			if (historyPosition > history.size()-1) historyPosition = history.size()-1;
			retrieveHistory = true;
			break;
		case Qt::Key_PageUp:
			historyPosition = 0;
			retrieveHistory = true;
			break;
		case Qt::Key_PageDown:
			historyPosition = history.size()-1;
			retrieveHistory = true;
	}
	if (retrieveHistory)
	{
		lineEdit->setText(history[historyPosition]);
	}
}

bool PyWidget::returnPressed()
{
	QString line = lineEdit->text().trimmed();
	if (line.isEmpty()) return true;
	appendOutput(">"+line+"\n");
	history.push_back(line);
	historyPosition = history.size();
	lineEdit->clear();
	bool state;
	QString result = PyInterpreter::run(line, state);
	appendOutput(result);
	return true;
}

void PyWidget::startInterpreter()
{
	// initialize the interpreter
	PyInterpreter::initialize();
	if (!PyInterpreter::isValid())
	{
		appendOutput(PyInterpreter::getStartupLog());
		return;
	}
}
