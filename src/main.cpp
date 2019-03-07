#include "mainWindow.h"
#include <QtWidgets/QApplication>
#include <QtCore/QFile>
#include <QtCore/QTextCodec>
#include <QtCore/QTextStream>

static QTextStream* logStream;
static QFile* logFile;

void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
	if (logStream && logStream->device())
	{
		QString text;
		switch (type) {
		case QtDebugMsg:
			text = msg;
			break;
		case QtWarningMsg:
			text = QString("Warning: %1").arg(msg);
			break;
		case QtCriticalMsg:
			text = QString("Critical: %1").arg(msg);
			break;
		case QtFatalMsg:
			text = QString("Fatal: %1").arg(msg);
		break;
		}
		(*logStream) << text << endl;
	}
}

void startLogging()
{
	logFile = new QFile(LOGFILENAME);
	if (logFile->open(QFile::WriteOnly | QIODevice::Append | QIODevice::Unbuffered))
	logStream = new QTextStream(logFile);
#ifdef Q_WS_WIN
	logStream->setCodec("Windows-1251");
#else
	logStream->setCodec("utf-8");
#endif
	qInstallMessageHandler(customMessageHandler);
//qDebug("Success opening log file");
}

void finishLogging()
{
//qDebug("Success closing log file");
	delete logStream;
	logStream = 0;
	delete logFile;
	logFile = 0;
	qInstallMessageHandler(0);
}

int main(int argc, char** argv)
{
	QApplication qapp(argc, argv);
	qapp.setWindowIcon(QIcon(":/images/cube_molecule.png"));
#ifdef LOGGING
  startLogging();
#endif
	MainWindow mainWindow;
	mainWindow.show();
	int res = qapp.exec();
#ifdef LOGGING
	finishLogging();
#endif
	return res;
}
