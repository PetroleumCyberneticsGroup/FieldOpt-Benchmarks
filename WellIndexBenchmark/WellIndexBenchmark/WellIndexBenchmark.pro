#-------------------------------------------------
#
# Project created by QtCreator 2016-03-15T14:28:43
#
#-------------------------------------------------
include(local_paths.pri)

# FIELDOPT_BIN_PATH=../../WellIndexBenchmark/build-FieldOpt-old
FIELDOPT_BIN_PATH=../../WellIndexBenchmark/build-FieldOpt-old-Desktop_Qt_5_4_1_GCC_64bit-Debug

QT       += core

QT       += gui

QT       += widgets
TARGET = wellindexbenchmark
CONFIG += c++11
CONFIG   += console
CONFIG   -= app_bundle

#LIBS += -L/usr/lib -lboost_system -lboost_filesystem
#LIBS += -lcurses
LIBS += -L$$FIELDOPT_BIN_PATH/WellIndexCalculator -lWellIndexCalculator
LIBS += -L$$FIELDOPT_BIN_PATH/ERTWrapper -lertwrapper
LIBS += -L$$FIELDOPT_BIN_PATH/Model -lmodel
LIBS += -L$$FIELDOPT_BIN_PATH/Utilities -lutilities
LIBS += -larmadillo
LIBS += -lrpoly_plus_plus
INCLUDEPATH += $$FIELDOPT_LIB_PATH

TEMPLATE = app

SOURCES += main.cpp \
    src/file_handling.cpp \
    src/well_data_pcg.cpp \
    src/test_wells.cpp \
    src/well_rms.cpp \
    src/well_pcg.cpp
#    ../../../FieldOpt/FieldOpt/ERTWrapper/eclgridreader.cpp \
#    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/cell.cpp \
#    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/grid.cpp \
#    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/grid_exceptions.cpp \
#    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/ijkcoordinate.cpp \
#    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/xyzcoordinate.cpp \
#    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/eclgrid.cpp \
#    ../../../FieldOpt/FieldOpt/WellIndexCalculator/geometry_functions/geometryfunctions.cpp \
#    ../../../FieldOpt/FieldOpt/WellIndexCalculator/geometry_functions/geometryfunctions_exceptions.cpp \
#    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/xyzcoordinate.cpp

HEADERS += \
    src/file_handling.h \
    src/well_data_pcg.h \
    test_well.h \
    src/test_wells.h \
    src/well_rms.h \
    src/well_pcg.h
#    ../../../FieldOpt/FieldOpt/ERTWrapper/eclgridreader.h \
#    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/cell.h \
#    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/grid.h \
#    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/grid_exceptions.h \
#    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/ijkcoordinate.h \
#    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/xyzcoordinate.h \
#    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/eclgrid.h \
#    ../../../FieldOpt/FieldOpt/WellIndexCalculator/geometry_functions/geometryfunctions.cpp \
#    ../../../FieldOpt/FieldOpt/WellIndexCalculator/geometry_functions/geometryfunctions_exceptions.cpp \
#    ../../../FieldOpt/FieldOpt/Model/reservoir/grid/xyzcoordinate.cpp

DISTFILES += \
    local_paths.pri
