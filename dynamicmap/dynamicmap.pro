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
    authentication.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    mapcreator.h \
    authentication.h

FORMS    += mainwindow.ui \
    logindialog.ui
    
RESOURCES +=
