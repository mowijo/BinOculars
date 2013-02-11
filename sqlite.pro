#-------------------------------------------------
#
# Project created by QtCreator 2013-02-11T07:18:59
#
#-------------------------------------------------

QT       += core gui sql

TARGET = sqlite
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Settings.cpp \
    DataBase.cpp \
    Column.cpp \
    Table.cpp \
    DatabaseStructureModel.cpp

HEADERS  += MainWindow.h \
    Settings.h \
    DataBase.h \
    Table.h \
    Column.h \
    DatabaseStructureModel.h


FORMS    += MainWindow.ui
