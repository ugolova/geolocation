#-------------------------------------------------
#
# Project created by QtCreator 2014-04-19T15:08:03
#
#-------------------------------------------------

QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += testcase

HEADERS += \
    sample_test.h \
    authentication_test.h \
    ../dynamicmap_src/authentication.h \
    container/station_test.h \
    ../dynamicmap_src/container/station.h \
    container/road_test.h \
    ../dynamicmap_src/container/road.h

SOURCES += \
    main.cpp \
    sample_test.cpp \
    authentication_test.cpp \
    ../dynamicmap_src/authentication.cpp \
    container/station_test.cpp \
    ../dynamicmap_src/container/station.cpp \
    container/road_test.cpp \
    ../dynamicmap_src/container/road.cpp

