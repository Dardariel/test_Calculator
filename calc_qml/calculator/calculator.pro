TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    myvalidator.cpp \
    appcore.cpp \
    mythread.cpp

RESOURCES += qml.qrc

LIBS += -L../../lib -lMyMath

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    myvalidator.h \
    appcore.h \
    myqueue.h \
    mythread.h

DISTFILES +=

