#ifndef LINE_H
#define LINE_H

#include "../FieldOpt-old/Model/reservoir/grid/xyzcoordinate.h"

namespace WellIndexCalculator {
namespace GeometryClasses {

class Line
{
private:
    Model::Reservoir::Grid::XYZCoordinate p1_;
    Model::Reservoir::Grid::XYZCoordinate p2_;

public:
    Line(){}
    Line(Model::Reservoir::Grid::XYZCoordinate p0, Model::Reservoir::Grid::XYZCoordinate p1);

    Model::Reservoir::Grid::XYZCoordinate p0() const {return p1_;}
    Model::Reservoir::Grid::XYZCoordinate p1() const {return p2_;}

};

}
}

#endif // LINE_H
