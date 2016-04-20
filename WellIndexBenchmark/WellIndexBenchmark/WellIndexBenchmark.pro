#-------------------------------------------------
#
# Project created by QtCreator 2016-03-15T14:28:43
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = WellIndexBenchmark
CONFIG   += console
CONFIG   -= app_bundle

LIBS += -L/usr/lib -lboost_system -lboost_filesystem

TEMPLATE = app

SOURCES += main.cpp \
    src/file_handling.cpp \
    src/well_data_pcg.cpp \
    src/test_wells.cpp \
    src/well_rms.cpp \
    src/well_pcg.cpp

HEADERS += \
    src/file_handling.h \
    src/well_data_pcg.h \
    test_well.h \
    src/test_wells.h \
    src/well_rms.h \
    src/well_pcg.h
