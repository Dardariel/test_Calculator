#-------------------------------------------------
#
# Project created by QtCreator 2018-03-25T11:06:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = calculator
TEMPLATE = app

DEPENDPATH += ../../lib
INCLUDEPATH += ../../lib

LIBS += -L../../lib -lMyMath

SOURCES += main.cpp\
        mainwindow.cpp \
        mythread.cpp

HEADERS  += mainwindow.h \
    mypushbutton.h \
    myvalidator.h \
    defs.h \
    mythread.h \
    myqueue.h

