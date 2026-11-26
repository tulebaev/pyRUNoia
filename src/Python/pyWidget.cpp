#include "Python/pyWidget.h"
#include "Python/pyInterpreter.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>

PyWidget::PyWidget(QWidget* parent, const char* title)
	:	QDockWidget(title, parent),
		historyPosition(0)
{
	output = new QPlainTextEdit;
	output->setReadOnly(true);
	//output->setFrameShape(QFrame::NoFrame);
	output->setToolTip("Output of Python commands");

	lineEdit = new QLineEdit;
	lineEdit->setFrame(false);
	lineEdit->setMaximumHeight(24);
	lineEdit->setToolTip("Enter a Python command and press return for execution");
	connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));

	QLabel* prompt = new QLabel(">");
	prompt->setFrameShape(QFrame::NoFrame);
	prompt->setStyleSheet("QLabel { background-color : white; }");
	QHBoxLayout* commandArea = new QHBoxLayout;
	commandArea->addWidget(prompt);
	commandArea->addWidget(lineEdit);
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(output);
	layout->addLayout(commandArea);
	layout->setMargin(0); layout->setSpacing(0);
	QWidget* mainArea = new QWidget(this);
	mainArea->setLayout(layout);
	setWidget(mainArea);

	startInterpreter();
	if (!PyInterpreter::isValid())
	{
		setEnabled(false);
		output->insertPlainText("No Python support available!");
		return;
	}

	lineEdit->setFocus();
}

PyWidget::~PyWidget()
{
	history.clear();
	PyInterpreter::finalize();
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

void PyWidget::returnPressed()
{
	QString line = lineEdit->text().trimmed();
	if (line.isEmpty()) return;
	output->insertPlainText(">"+line+"\n");
	history.push_back(line);
	historyPosition = history.size();
	lineEdit->clear();
	QString result = PyInterpreter::run(line);
	output->insertPlainText(result);
}

void PyWidget::startInterpreter()
{
	// initialize the interpreter
	PyInterpreter::initialize();
	if (!PyInterpreter::isValid())
	{
		//output->insertPlainText(PyInterpreter::Log().error());
	}
}
