// mainWindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

#define LOGFILENAME "pyRUNoia.log"
#define INIFILENAME "pyRUNoia.ini"

class QSettings;
class QUndoStack;
class QStandardItem;
class Scene3D;
class PyWidget;
class QTreeView;
class QDockWidget;
class TutorialDialog;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow();
	~MainWindow();
public slots:
	void open();
	void save();
	void cut();
	void copy();
	void paste();
	void delete_();
	void undo();
	void redo();
	void help();
	void about();
private slots:
	void changeWindowState();
	void structuresTreeChanged(QStandardItem*);
private:
	void readSettings();
	void writeSettings();
	void createActions();
	void createMenus();
	void createToolBar();
private:
	QMenu* fileMenu;
	QMenu* editMenu;
	QMenu* displayMenu;
	QMenu* helpMenu;
	QToolBar* toolBar;
	QAction* openAct;
	QAction* saveAct;
	QAction* quitAct;
	QAction* undoAct;
	QAction* redoAct;
	QAction* cutAct;
	QAction* copyAct;
	QAction* pasteAct;
	QAction* deleteAct;
	QAction* changeWindowStateAct;
	QAction* helpAct;
	QAction* aboutAct;
	QSettings* settings;
	QUndoStack* undoStack;
	int changedLevel;
private:
	Scene3D* sceneView;
	PyWidget* pyWidget;
	QStatusBar* status;
	QTreeView* structuresTree;
	QDockWidget* structuresView;
	TutorialDialog* tutorialDialog;
};

#endif
