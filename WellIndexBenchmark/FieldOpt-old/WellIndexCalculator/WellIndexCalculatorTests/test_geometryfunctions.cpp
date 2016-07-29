
#include <gtest/gtest.h>
#include <QList>
#include <QVector3D>
#include "Model/reservoir/grid/grid.h"
#include "Model/reservoir/grid/grid_exceptions.h"
#include "Model/reservoir/grid/cell.h"
#include "Model/reservoir/grid/eclgrid.h"
#include "WellIndexCalculator/geometry_functions/geometryfunctions.h"
#include "WellIndexCalculator/geometry_functions/geometryfunctions_exceptions.h"
#include "Utilities/file_handling/filehandling.h"

using namespace Model::Reservoir::Grid;

namespace {

class GeometryFunctionsTest : public ::testing::Test {
protected:
    GeometryFunctionsTest() {
        grid_ = new ECLGrid(file_path_);
    }

    virtual ~GeometryFunctionsTest() {
        delete grid_;
    }

    virtual void SetUp() {
        point_ = new XYZCoordinate(1,2,3);
        test_point_ = new XYZCoordinate(2,3,4);

        corner1_ = new Model::Reservoir::Grid::XYZCoordinate(0, 0, 0);
        corner2_ = new Model::Reservoir::Grid::XYZCoordinate(0, 4, 0);
        corner3_ = new Model::Reservoir::Grid::XYZCoordinate(4, 0, 0);
        corner4_ = new Model::Reservoir::Grid::XYZCoordinate(4, 4, 0);
        line_point1_ = new Model::Reservoir::Grid::XYZCoordinate(2, 2, 2);
        line_point2_ = new Model::Reservoir::Grid::XYZCoordinate(2, 2, 0);
        middle_line_point = new Model::Reservoir::Grid::XYZCoordinate(2, 2, 1);
        plane_ = new WellIndexCalculator::GeometryClasses::SquarePlane(*corner1_, *corner2_, *corner3_, *corner4_);
        line_ = new WellIndexCalculator::GeometryClasses::Line(*line_point1_, *line_point2_);
        parallell_line_ = new WellIndexCalculator::GeometryClasses::Line(*corner1_, *corner2_);
        line_with_middle_line_point_ = new WellIndexCalculator::GeometryClasses::Line(*middle_line_point, *line_point1_);
        point1_ = new Model::Reservoir::Grid::XYZCoordinate(0, 0, 2);
        pro_point1_ = new Model::Reservoir::Grid::XYZCoordinate(0, 0, 0);
        point2_ = new Model::Reservoir::Grid::XYZCoordinate(2, 2, 12);
        pro_point2_ = new Model::Reservoir::Grid::XYZCoordinate(2, 2, 0);
        point12_line_ = new WellIndexCalculator::GeometryClasses::Line(*point1_, *point2_);

        // XYZ to QVector3D and back again
        vector_point_ = new QVector3D(4,4,0);


    }

    virtual void TearDown() { }

    // Move3dPointFalse test input variables
    XYZCoordinate* point_;
    XYZCoordinate* test_point_;

    // LineInterceptsPlaneTest test input variables
    Model::Reservoir::Grid::XYZCoordinate* corner1_;
    Model::Reservoir::Grid::XYZCoordinate* corner2_;
    Model::Reservoir::Grid::XYZCoordinate* corner3_;
    Model::Reservoir::Grid::XYZCoordinate* corner4_;
    Model::Reservoir::Grid::XYZCoordinate* line_point1_;
    Model::Reservoir::Grid::XYZCoordinate* line_point2_;
    Model::Reservoir::Grid::XYZCoordinate* middle_line_point;
    Model::Reservoir::Grid::XYZCoordinate* point1_;
    Model::Reservoir::Grid::XYZCoordinate* pro_point1_;
    Model::Reservoir::Grid::XYZCoordinate* point2_;
    Model::Reservoir::Grid::XYZCoordinate* pro_point2_;
    // XYZ to QVector3D
    QVector3D* vector_point_;

    WellIndexCalculator::GeometryClasses::SquarePlane* plane_;
    WellIndexCalculator::GeometryClasses::Line* line_;
    WellIndexCalculator::GeometryClasses::Line* parallell_line_;
    WellIndexCalculator::GeometryClasses::Line* line_with_middle_line_point_;
    WellIndexCalculator::GeometryClasses::Line* point12_line_;

    Grid* grid_;
    QString file_path_ = Utilities::FileHandling::GetBuildDirectoryPath() + "/../examples/ADGPRS/5spot/ECL_5SPOT.EGRID";

};


TEST_F(GeometryFunctionsTest, Move3dPointFalse) {
    EXPECT_FALSE( point_->Equals( WellIndexCalculator::GeometryFunctions::move3dpoint(*test_point_) ) );
    EXPECT_TRUE( test_point_->Equals( WellIndexCalculator::GeometryFunctions::move3dpoint(*point_) ) );
}

TEST_F(GeometryFunctionsTest, DistanceFunction) {

    EXPECT_TRUE( WellIndexCalculator::GeometryFunctions::distance_coordinates(*corner1_, *corner2_)==4 );
    EXPECT_TRUE( WellIndexCalculator::GeometryFunctions::distance_coordinates(*corner1_, *corner4_)==sqrt(32) );
}

TEST_F(GeometryFunctionsTest, LineInterceptsPlane) {
    EXPECT_TRUE( line_point2_->Equals( WellIndexCalculator::GeometryFunctions::line_intersects_plane(*plane_, *line_) ) );
}

TEST_F(GeometryFunctionsTest, LineInterceptsPlaneExceptionTest) {
    EXPECT_ANY_THROW( WellIndexCalculator::GeometryFunctions::line_intersects_plane(*plane_, *parallell_line_) );
}

TEST_F(GeometryFunctionsTest, OutsideLineSegmentException) {
EXPECT_THROW( WellIndexCalculator::GeometryFunctions::line_intersects_plane(*plane_, *line_with_middle_line_point_), geometryfunctions::LineIntersectsPlane_OutsideLineSegmentException );
}

TEST_F(GeometryFunctionsTest, LineInterceptsPlaneVectorized) {
    EXPECT_TRUE( line_point2_->Equals( WellIndexCalculator::GeometryFunctions::line_intersects_plane_vectorized(*plane_, *line_) ) );
}

TEST_F(GeometryFunctionsTest, LineInterceptsPlaneVectorizedExceptionTest) {
    EXPECT_ANY_THROW( WellIndexCalculator::GeometryFunctions::line_intersects_plane_vectorized(*plane_, *parallell_line_) );
}

TEST_F(GeometryFunctionsTest, LineInterceptsPlaneVectorizedOutsideException) {
EXPECT_THROW( WellIndexCalculator::GeometryFunctions::line_intersects_plane_vectorized(*plane_, *line_with_middle_line_point_), geometryfunctions::LineIntersectsPlane_OutsideLineSegmentException );
}

TEST_F(GeometryFunctionsTest, ProjectionFunction) {
EXPECT_TRUE(pro_point1_->Equals(WellIndexCalculator::GeometryFunctions::project_line_to_plane(*point12_line_, *plane_).p0()  ) );
EXPECT_TRUE(pro_point2_->Equals(WellIndexCalculator::GeometryFunctions::project_line_to_plane(*point12_line_, *plane_).p1()  ) );
}

TEST_F(GeometryFunctionsTest, XYZtoVector) {
EXPECT_TRUE( corner4_->Equals(WellIndexCalculator::GeometryFunctions::qvec_to_XYZ(*vector_point_)) );
//EXPECT_TRUE( corner3_->Equals(WellIndexCalculator::GeometryFunctions::qvec_to_XYZ(vector_point_)) );
}

TEST_F(GeometryFunctionsTest, XYZtoVectortoXYZ) {
EXPECT_TRUE( corner4_->Equals(WellIndexCalculator::GeometryFunctions::qvec_to_XYZ( WellIndexCalculator::GeometryFunctions::XYZ_to_qvec(*corner4_)  )) );
}

TEST_F(GeometryFunctionsTest, XYZpoints_to_qvector) {
EXPECT_TRUE(1);
}

}
