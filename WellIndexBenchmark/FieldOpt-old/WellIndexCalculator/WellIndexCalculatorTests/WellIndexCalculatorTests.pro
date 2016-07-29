include(../../defaults.pri)
QT       += core
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11
LIBS += -L$$OUT_PWD/../../Utilities -lutilities
LIBS += -L$$OUT_PWD/../../WellIndexCalculator -lWellIndexCalculator
LIBS += -L$$OUT_PWD/../../ERTWrapper -lertwrapper
LIBS += -L$$OUT_PWD/../../Model -lmodel
LIBS += -larmadillo
LIBS += -lrpoly_plus_plus

LIBS += -lpthread -lgtest -pthread

SOURCES += \
    gtest_wic_main.cpp \
    test_geometryfunctions.cpp \
    test_single_cell_wellindex.cpp \
    well_constraint_projections_tests.cpp \
    test_intersected_cells.cpp
