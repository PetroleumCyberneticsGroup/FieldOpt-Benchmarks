#include "squareplane.h"

WellIndexCalculator::GeometryClasses::SquarePlane::SquarePlane(Model::Reservoir::Grid::XYZCoordinate c1, Model::Reservoir::Grid::XYZCoordinate c2,
                                                               Model::Reservoir::Grid::XYZCoordinate c3, Model::Reservoir::Grid::XYZCoordinate c4){
    c1_ = c1;
    c2_ = c2;
    c3_ = c3;
    c4_ = c4;

}
