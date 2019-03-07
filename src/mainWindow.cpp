// mainWindow.cpp
#include "mainWindow.h"
#include "scene3D.h"
#include "molecular.h"
#include "tutorialDialog.h"
#include "Python/pyWidget.h"
#include <QtCore/QSettings>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QMenuBar>
//#include <QtWidgets/QUndoStack>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QFileDialog>

MainWindow::MainWindow()
{
	tutorialDialog = NULL;
	readSettings();
	molecularSystem.clear();

	createActions();
	createMenus();
	createToolBar();

	sceneView = new Scene3D;
	sceneView->setFocusPolicy(Qt::StrongFocus);
	sceneView->setToolTip("3D viewer");
	setCentralWidget(sceneView);

	pyWidget = new PyWidget(this, " Python Interpreter");
	addDockWidget(Qt::BottomDockWidgetArea, pyWidget);

	structuresView = new QDockWidget(" Structures");
	structuresView->setToolTip("Structures viewer");
	structuresTree = new QTreeView(structuresView);
	structuresTree->setModel(&molecularSystem.structuralModel);
	structuresTree->setEditTriggers(QAbstractItemView::NoEditTriggers);
	structuresTree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
	connect(&molecularSystem.structuralModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(structuresTreeChanged(QStandardItem*)));
	changedLevel = 0;
	structuresView->setWidget(structuresTree);
	addDockWidget(Qt::LeftDockWidgetArea, structuresView);
}

MainWindow::~MainWindow()
{
	if (tutorialDialog) tutorialDialog->close();
	//writeSettings();
}

void MainWindow::readSettings()
{
	/*settings = new QSettings(INIFILENAME, QSettings::IniFormat);
	resize(settings->value("MainWindow/size", QSize(1280,1024)).toSize());
	move(settings->value("MainWindow/pos", QPoint(150,10)).toPoint());*/
resize(QSize(1280,1024)); move(QPoint(150,10));
}

void MainWindow::writeSettings()
{
	settings->setValue("MainWindow/size", size());
	settings->setValue("MainWindow/pos", pos());
	settings->sync();
}

void MainWindow::createActions()
{
	openAct = new QAction(QIcon(":/images/open.png"), "&Open HIN", this);
	openAct->setShortcut(QKeySequence::Open);
	openAct->setStatusTip("Open a HIN file");
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	saveAct = new QAction(QIcon(":/images/save.png"), "&Save XML", this);
	saveAct->setShortcut(QKeySequence::Save);
	saveAct->setStatusTip("Save configuration to the disk");
	connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

	quitAct = new QAction(QIcon(":/images/quit.png"), "&Quit", this);
#ifdef Q_WS_WIN
	quitAct->setShortcut(QKeySequence("Ctrl+Q"));
#else
	quitAct->setShortcut(QKeySequence::Quit);
#endif
	quitAct->setStatusTip("Quit from Mutagen");
	connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));

	undoAct = new QAction(QIcon(":/images/undo.png"), "&Undo", this);
	undoAct->setShortcut(QKeySequence::Undo);
	undoAct->setStatusTip("Undo the last operation");
	connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));
	undoAct->setEnabled(false);

	redoAct = new QAction(QIcon(":/images/redo.png"), "&Redo", this);
	redoAct->setShortcut(QKeySequence::Redo);
	redoAct->setStatusTip("Redo the last operation");
	connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));
	redoAct->setEnabled(false);

	cutAct = new QAction(QIcon(":/images/cut.png"), "&Cut", this);
	cutAct->setShortcut(QKeySequence::Cut);
	cutAct->setStatusTip("Cut the current content to the clipboard");
	connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

	copyAct = new QAction(QIcon(":/images/copy.png"), "C&opy", this);
	copyAct->setShortcut(QKeySequence::Copy);
	copyAct->setStatusTip("Copy the current content to the clipboard");
	connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

	pasteAct = new QAction(QIcon(":/images/paste.png"), "&Paste", this);
	pasteAct->setShortcut(QKeySequence::Paste);
	pasteAct->setStatusTip("Paste the clipboard's content into the project");
	connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));

	deleteAct = new QAction(QIcon(":/images/delete.png"), "&Delete", this);
	deleteAct->setShortcut(QKeySequence::Delete);
	deleteAct->setStatusTip("Delete the current content from project");
	connect(deleteAct, SIGNAL(triggered()), this, SLOT(deleteSlot()));

	changeWindowStateAct = new QAction(QIcon(":/images/fullscreen.png"), "&Full Screen", this);
	changeWindowStateAct->setShortcut(QKeySequence(Qt::Key_F11));
	changeWindowStateAct->setStatusTip("Entry to full-screen mode");
	connect(changeWindowStateAct, SIGNAL(triggered()), this, SLOT(changeWindowState()));

	helpAct = new QAction(QIcon(":/images/help.png"), "Quick &Help", this);
	helpAct->setShortcut(QKeySequence::HelpContents);
	helpAct->setStatusTip("Help online");
	connect(helpAct, SIGNAL(triggered()), this, SLOT(help()));

	aboutAct = new QAction("&About pyRUNoia", this);
	aboutAct->setStatusTip("About pyRUNoia");
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu("&File");
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addSeparator();
	fileMenu->addAction(quitAct);

	editMenu = menuBar()->addMenu("&Edit");
	editMenu->addAction(undoAct);
	editMenu->addAction(redoAct);
	editMenu->addSeparator();
	editMenu->addAction(cutAct);
	editMenu->addAction(copyAct);
	editMenu->addAction(pasteAct);
	editMenu->addAction(deleteAct);

	displayMenu = menuBar()->addMenu("&Display");
	displayMenu->addAction(changeWindowStateAct);

	helpMenu = menuBar()->addMenu("&Help");
	helpMenu->addAction(helpAct);
	helpMenu->addAction(aboutAct);
}

void MainWindow::createToolBar()
{
	toolBar = addToolBar("pyRUNoia");
	toolBar->addAction(openAct);
	toolBar->addAction(saveAct);
	//toolBar->addSeparator();
	//toolBar->addAction(undoAct);
	//toolBar->addAction(redoAct);
	toolBar->addAction(quitAct);
}

void MainWindow::open()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Open HyperChem file", QString(), "HyperChem files (*.hin)");
	if (fileName.isEmpty()) return;
	QFileInfo fi(fileName);
	if (!fi.exists())
	{
		QMessageBox::critical(this, "Error", QString("A molecular file `%1' does not exist.").arg(fileName));
		return;
	}
	int startRow = molecularSystem.structuralModel.rowCount();
	structuresTree->setModel(0);
	if (molecularSystem.load(fileName))
	{
		//qDebug() << QString("Molecular file `%1' loaded").arg(fileName);
		molecularSystem.calculateScope();
		sceneView->setInitialViewPoint();
		sceneView->repaint();
		sceneView->setFocus();
	}
	structuresTree->setModel(&molecularSystem.structuralModel);
	structuresTree->expand(molecularSystem.structuralModel.index(startRow, 0));
}

void MainWindow::save()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Save configuration As...", QString(), "XML files (*.xml)");
	if (fileName.isEmpty()) return;
	//saveAs(fileName);
	//qDebug() << QString("Configuration file `%1' saved").arg(fileName);
}

void MainWindow::cut()
{
molecularSystem.clear();
}

void MainWindow::copy()
{
}

void MainWindow::paste()
{
}

void MainWindow::deleteSlot()
{
}

void MainWindow::undo()
{
}

void MainWindow::redo()
{
}

void MainWindow::changeWindowState()
{
	if (isFullScreen())
	{
		showNormal();//setWindowState(windowState() & ~Qt::WindowFullScreen);
		changeWindowStateAct->setText("&Full Screen");
		changeWindowStateAct->setIcon(QIcon(":/images/fullscreen.png"));
		toolBar->setVisible(true);
		structuresView->setVisible(true);
		pyWidget->setVisible(true);
	}
	else
	{
		changeWindowStateAct->setText("&Normal Size");
		changeWindowStateAct->setIcon(QIcon(":/images/no_fullscreen.png"));
		toolBar->setVisible(false);
		structuresView->setVisible(false);
		pyWidget->setVisible(false);
		showFullScreen();//setWindowState(windowState() | Qt::WindowFullScreen);
	}
}

void MainWindow::help()
{
	if (!tutorialDialog) tutorialDialog = new TutorialDialog();
	tutorialDialog->show();
	tutorialDialog->activateWindow();
}

void MainWindow::about()
{
	QMessageBox::about(this, "About pyRUNoia",
		"v.0.2a Jan 2015"
		"<p>Copyright(c) 2015 InterX, Inc."
		"<p><a href=\"http://interxinc.com\">interxinc.com</a>");
}

void MainWindow::structuresTreeChanged(QStandardItem* item)
{
	changedLevel++;
	if (item->hasChildren())
	{
		Qt::CheckState parentState = item->checkState();
		for (int i = 0; i < item->rowCount(); ++i)
		{
			item->child(i)->setCheckState(parentState);
		}
	}
	changedLevel--;
	if ((changedLevel == 0) && (molecularSystem.representation != MolecularSystem::INVISIBLE)) sceneView->repaint();
}
