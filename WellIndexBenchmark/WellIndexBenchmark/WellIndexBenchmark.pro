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

TEMPLATE = app


SOURCES += main.cpp \
    src/file_handling.cpp \
    src/well_pcg.cpp

HEADERS += \
    src/file_handling.h \
    src/well_pcg.h
