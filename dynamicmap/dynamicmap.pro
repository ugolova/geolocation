#-------------------------------------------------
#
# Project created by QtCreator 2014-03-30T14:01:46
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dynamicmap
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    mapcreator.cpp \
    authentication.cpp \
    container/serialization.cpp \
    container/station.cpp \
    container/algorithm.cpp \
    container/road.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    mapcreator.h \
    authentication.h \
    container/serialization.h \
    container/station.h \
    container/dynamicarray.h \
    container/multigraph.h \
    container/algorithm.h \
    container/dynamicarrayutill.h \
    container/road.h

FORMS    += mainwindow.ui \
    logindialog.ui
    
RESOURCES +=

OTHER_FILES += \
    container/test.txt
