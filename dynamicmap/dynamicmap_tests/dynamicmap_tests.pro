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
    ../dynamicmap_src/container/road.h \
    ../dynamicmap_src/container/algorithm.h \
    ../dynamicmap_src/container/serialization.h \
    ../dynamicmap_src/controller_gui.h \
    ../dynamicmap_src/exceptions/unknown_station_exception.h \
    ../dynamicmap_src/exceptions/unknown_link_exception.h \
    ../dynamicmap_src/exceptions/cannot_open_file_exception.h \
    ../dynamicmap_src/exceptions/incorrect_file_format_exception.h \
    container/algorithm_test.h \


SOURCES += \
    main.cpp \
    sample_test.cpp \
    authentication_test.cpp \
    ../dynamicmap_src/authentication.cpp \
    container/station_test.cpp \
    ../dynamicmap_src/container/station.cpp \
    container/road_test.cpp \
    ../dynamicmap_src/container/road.cpp \
    ../dynamicmap_src/container/algorithm.cpp \
    ../dynamicmap_src/container/serialization.cpp \
    ../dynamicmap_src/controller_gui.cpp \
    ../dynamicmap_src/exceptions/unknown_station_exception.cpp \
    ../dynamicmap_src/exceptions/unknown_link_exception.cpp \
    ../dynamicmap_src/exceptions/cannot_open_file_exception.cpp \
    ../dynamicmap_src/exceptions/incorrect_file_format_exception.cpp \
    container/algorithm_test.cpp

OTHER_FILES += \
    algorithmTest.txt

