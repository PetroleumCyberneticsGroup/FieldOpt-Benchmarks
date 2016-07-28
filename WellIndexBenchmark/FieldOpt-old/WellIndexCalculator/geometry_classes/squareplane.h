#ifndef SQUAREPLANE_H
#define SQUAREPLANE_H

#include "../FieldOpt-old/Model/reservoir/grid/xyzcoordinate.h"

namespace WellIndexCalculator {
namespace GeometryClasses {

/*!
 * \brief SquarePlane is a plane restricted by 4 points/corners.
 * A SquarePlane object is the physcial representation of
 * a side of a regular or irregular three-dimensional cube
 * It is uniqely defined by its 4 convex corners (all of which
 * must lie in the same plane).
 */

class SquarePlane
{

private:
    Model::Reservoir::Grid::XYZCoordinate c1_;
    Model::Reservoir::Grid::XYZCoordinate c2_;
    Model::Reservoir::Grid::XYZCoordinate c3_;
    Model::Reservoir::Grid::XYZCoordinate c4_;
public:
    SquarePlane(){}
    SquarePlane(Model::Reservoir::Grid::XYZCoordinate c1, Model::Reservoir::Grid::XYZCoordinate c2,
                Model::Reservoir::Grid::XYZCoordinate c3, Model::Reservoir::Grid::XYZCoordinate c4);

    Model::Reservoir::Grid::XYZCoordinate c1() const { return c1_; }
    Model::Reservoir::Grid::XYZCoordinate c2() const { return c2_; }
    Model::Reservoir::Grid::XYZCoordinate c3() const { return c3_; }
    Model::Reservoir::Grid::XYZCoordinate c4() const { return c4_; }

};

}
}

#endif // SQUAREPLANE_H
