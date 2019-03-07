TEMPLATE = app
TARGET = pyRUNoia

QT += opengl
CONFIG += release

DESTDIR = ./
MOC_DIR = ./tmp
RCC_DIR = ./tmp
UI_DIR = ./tmp
OBJECTS_DIR = ./tmp
INCLUDEPATH += ./src C:/Python27/include
LIBS += -LC:/Python27/libs

HEADERS = \
  src/mainWindow.h \
  src/scene3D.h \
  src/tutorialDialog.h \
  src/Python/pyWidget.h

SOURCES = \
  src/main.cpp \
  src/mainWindow.cpp \
  src/scene3D.cpp \
  src/molecular.cpp \
  src/Python/pyWidget.cpp \
  src/Python/pyInterpreter.cpp \
  src/CommonLib/Exception.cpp \
  src/CommonLib/Logger.cpp \
  src/CommonLib/PeriodicTable.cpp \
  src/FileIOLib/FileIOBase.cpp

FORMS = \
  src/tutorialDialog.ui

RESOURCES = \
  src/icons.qrc \
  src/tutorial.qrc
