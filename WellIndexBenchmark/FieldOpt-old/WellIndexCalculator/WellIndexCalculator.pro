include(../defaults.pri)

CONFIG   -= app_bundle
CONFIG += c++11

#LIBS += -L$$OUT_PWD/../Model -lmodel
LIBS += -larmadillo
LIBS += -lrpoly_plus_plus
LIBS += -L$$OUT_PWD/../Utilities -lutilities

TEMPLATE = lib

TARGET = WellIndexCalculator

HEADERS += \
    ../Model/reservoir/grid/cell.h \
    ../Model/reservoir/grid/grid.h \
    ../Model/reservoir/grid/grid_exceptions.h \
    ../Model/reservoir/grid/ijkcoordinate.h \
    ../Model/reservoir/grid/xyzcoordinate.h \
    ../Model/reservoir/grid/eclgrid.cpp \
    geometry_functions/geometryfunctions.h \
    geometry_functions/geometryfunctions_exceptions.h \
    geometry_classes/line.h \
    geometry_classes/squareplane.h \
    well_constraint_projections/well_constraint_projections.h \
    wellindexcalculator.h

SOURCES += \
    ../Model/reservoir/grid/cell.cpp \
    ../Model/reservoir/grid/grid.cpp \
    ../Model/reservoir/grid/ijkcoordinate.cpp \
    ../Model/reservoir/grid/xyzcoordinate.cpp \
    ../Model/reservoir/grid/eclgrid.cpp \
    geometry_functions/geometryfunctions.cpp \
    geometry_classes/line.cpp \
    geometry_classes/squareplane.cpp \
    well_constraint_projections/well_constraint_projections.cpp \
    wellindexcalculator.cpp
