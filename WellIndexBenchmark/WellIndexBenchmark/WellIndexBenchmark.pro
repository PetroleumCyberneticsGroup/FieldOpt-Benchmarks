#-------------------------------------------------
#
# Project created by QtCreator 2016-03-15T14:28:43
#
#-------------------------------------------------

QT       += core

QT       += gui

QT       += widgets

TARGET = wellindexbenchmark
CONFIG   += console
CONFIG   -= app_bundle

#LIBS += -L/usr/lib -lboost_system -lboost_filesystem
#LIBS += -lcurses

TEMPLATE = app

SOURCES += main.cpp \
    src/file_handling.cpp \
    src/well_data_pcg.cpp \
    src/test_wells.cpp \
    src/well_rms.cpp \
    src/well_pcg.cpp \
    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/cell.cpp \
    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/grid.cpp \
    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/grid_exceptions.cpp \
    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/ijkcoordinate.cpp \
    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/xyzcoordinate.cpp \
    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/eclgrid.cpp \
    ../../../FieldOpt/FieldOpt/WellIndexCalculator/geometry_functions/geometryfunctions.cpp \
    ../../../FieldOpt/FieldOpt/WellIndexCalculator/geometry_functions/geometryfunctions_exceptions.cpp \
    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/xyzcoordinate.cpp

HEADERS += \
    src/file_handling.h \
    src/well_data_pcg.h \
    test_well.h \
    src/test_wells.h \
    src/well_rms.h \
    src/well_pcg.h \
    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/cell.h \
    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/grid.h \
    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/grid_exceptions.h \
    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/ijkcoordinate.h \
    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/xyzcoordinate.h \
    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/eclgrid.h \
    ../../../FieldOpt/FieldOpt/WellIndexCalculator/geometry_functions/geometryfunctions.cpp \
    ../../../FieldOpt/FieldOpt/WellIndexCalculator/geometry_functions/geometryfunctions_exceptions.cpp \
    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/xyzcoordinate.cpp
