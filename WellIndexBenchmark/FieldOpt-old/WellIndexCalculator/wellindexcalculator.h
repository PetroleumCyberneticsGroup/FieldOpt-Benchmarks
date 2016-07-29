#ifndef WELLINDEXCALCULATOR_H
#define WELLINDEXCALCULATOR_H

#include <QList>
#include "Model/reservoir/grid/grid.h"
#include "Model/reservoir/grid/xyzcoordinate.h"

namespace WellIndexCalculator {

class WellIndexCalculator
{
public:
    WellIndexCalculator(Model::Reservoir::Grid::Grid *grid, double wellbore_radius);

    struct BlockData {
        int i;
        int j;
        int k;
        double well_index;
    };

    QList<BlockData> GetBlocks(QList<Model::Reservoir::Grid::XYZCoordinate> points);

private:
    Model::Reservoir::Grid::Grid *grid_;
    double wellbore_radius_;
};

}

#endif // WELLINDEXCALCULATOR_H
