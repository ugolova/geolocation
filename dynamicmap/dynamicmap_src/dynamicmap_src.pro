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
    controller_gui.cpp \
    exceptions/unknown_station_exception.cpp \
    exceptions/invalid_coordinate_exception.cpp \
    exceptions/unknown_link_exception.cpp \
    exceptions/invalid_distance_exception.cpp \
    exceptions/cannot_open_file_exception.cpp \
    exceptions/incorrect_file_format_exception.cpp

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
    controller_gui.h \
    exceptions/unknown_station_exception.h \
    exceptions/dynamicmap_exception.h \
    exceptions/invalid_coordinate_exception.h \
    exceptions/unknown_link_exception.h \
    exceptions/invalid_distance_exception.h \
    exceptions/cannot_open_file_exception.h \
    exceptions/incorrect_file_format_exception.h

FORMS    += mainwindow.ui \
    logindialog.ui
    
RESOURCES +=
