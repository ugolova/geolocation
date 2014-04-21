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
    container/road.cpp \
    controller_gui.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    mapcreator.h \
    authentication.h \
    container/serialization.h \
    container/station.h \
    container/multigraph.h \
    container/algorithm.h \
    container/road.h \
    container/dynamic_array.h \
    controller_gui.h

FORMS    += mainwindow.ui \
    logindialog.ui
    
RESOURCES +=
