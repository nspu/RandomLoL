#-------------------------------------------------
#
# Project created by QtCreator 2012-11-22T04:14:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RandomLoL
TEMPLATE = app
RESOURCES = images.qrc

SOURCES += main.cpp\
        mainwindow.cpp \
    listes.cpp \
    configuration.cpp

HEADERS  += mainwindow.h \
    listes.h \
    configuration.h

FORMS    += mainwindow.ui \
    listes.ui \
    configuration.ui


