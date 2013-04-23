
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = life
TEMPLATE = app

SOURCES += main.cpp \
	mainwindow.cpp \
	lifeview.cpp \
    life.cpp

HEADERS += \
	mainwindow.hpp \
	lifeview.hpp \
    life.hpp

FORMS += mainwindow.ui

RESOURCES += resources.qrc

RC_FILE = icon.rc

