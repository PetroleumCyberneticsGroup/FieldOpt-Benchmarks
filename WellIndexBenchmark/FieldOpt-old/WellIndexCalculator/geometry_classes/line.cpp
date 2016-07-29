#include "line.h"

WellIndexCalculator::GeometryClasses::Line::Line(Model::Reservoir::Grid::XYZCoordinate p1,Model::Reservoir::Grid::XYZCoordinate p2){
    p1_ = p1;
    p2_ = p2;
}
