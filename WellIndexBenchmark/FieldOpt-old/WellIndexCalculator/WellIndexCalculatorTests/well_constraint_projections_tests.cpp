
#include <gtest/gtest.h>
#include <QList>
#include <QVector3D>
#include "Model/reservoir/grid/grid.h"
#include "Model/reservoir/grid/grid_exceptions.h"
#include "Model/reservoir/grid/cell.h"
#include "Model/reservoir/grid/eclgrid.h"
#include "WellIndexCalculator/geometry_functions/geometryfunctions.h"
#include "WellIndexCalculator/geometry_functions/geometryfunctions_exceptions.h"
#include "WellIndexCalculator/well_constraint_projections/well_constraint_projections.h"
#include <cblas.h>
#include <armadillo>
#include <Eigen/Dense>
#include <fstream>

using namespace WellIndexCalculator;
using namespace Model::Reservoir::Grid;

namespace {

class WellConstraintProjectionsTests : public ::testing::Test {
protected:
    WellConstraintProjectionsTests() {
    }

    virtual ~WellConstraintProjectionsTests() {
    }

    virtual void SetUp() {

        real_roots = new Eigen::VectorXd(6);
        img_roots = new Eigen::VectorXd(6);

        x1 = Model::Reservoir::Grid::XYZCoordinate(-4,20,0);
        x2 = Model::Reservoir::Grid::XYZCoordinate(2,2,0);
        x3 = Model::Reservoir::Grid::XYZCoordinate(-1,-2,-3);
        x4 = Model::Reservoir::Grid::XYZCoordinate(1,-20,2);
        x5 = Model::Reservoir::Grid::XYZCoordinate(0,0,0.2);
        coords.append(x1);
        coords.append(x2);
        coords.append(x3);
        coords.append(x4);
        coords_3d.append(x5);
        coords_3d.append(x1);
        coords_3d.append(x2);
        /* This does work, why??*
        x_1 = new QVector3D(-3,2,1);
        x_2 = new QVector3D(4,3,-1);
        x_3 = new QVector3D(0,-2,-3);
        x_4 = new QVector3D(1,-20,2);
        // Not work

        x_1 = new QVector3D(-3,2,2);
        x_2 = new QVector3D(4,3,0);
        x_3 = new QVector3D(2,-2,-3);
        x_4 = new QVector3D(-1,-2,2);
        x_5 = new QVector3D(0,0,0.2);
        */
        x_1 = QVector3D(3,2,0);
        x_2 = QVector3D(-2,2,0);
        x_3 = QVector3D(2,-2,0);
        x_4 = QVector3D(-3,-2,0);
        x_5 = QVector3D(0,0,0.2);
        coords_qvec.append(x_1);
        coords_qvec.append(x_2);
        coords_qvec.append(x_3);
        coords_qvec.append(x_4);
        coords_3d_qvec.append(x_3);
        coords_3d_qvec.append(x_1);
        coords_3d_qvec.append(x_2);
        d=2;

    }

    virtual void TearDown() { }

    // Move3dPointFalse test input variables
    Eigen::VectorXd *real_roots;
    Eigen::VectorXd *img_roots;

    Model::Reservoir::Grid::XYZCoordinate x1;
    Model::Reservoir::Grid::XYZCoordinate x2;
    Model::Reservoir::Grid::XYZCoordinate x3;
    Model::Reservoir::Grid::XYZCoordinate x4;
    Model::Reservoir::Grid::XYZCoordinate x5;

    QVector3D x_1;
    QVector3D x_2;
    QVector3D x_3;
    QVector3D x_4;
    QVector3D x_5;

    QList<Model::Reservoir::Grid::XYZCoordinate> coords;
    QList<Model::Reservoir::Grid::XYZCoordinate> coords_3d;

    QList<QVector3D> coords_qvec;
    QList<QVector3D> coords_3d_qvec;

    double d;

};


TEST_F(WellConstraintProjectionsTests, sumTests) {
    EXPECT_TRUE( WellConstraintProjections::sum_i(2,3,-10)==-5 );
    EXPECT_FALSE( WellConstraintProjections::sum_i(2,3,-10)== 5 );
    EXPECT_TRUE( WellConstraintProjections::sum_ij(2,5,1)==17 );
    EXPECT_FALSE( WellConstraintProjections::sum_ij(2,5,5)==-5 );
    EXPECT_TRUE( WellConstraintProjections::prod_i(2,5,3)==30 );
    EXPECT_FALSE( WellConstraintProjections::prod_i(2,5,3)==10 );

}

TEST_F(WellConstraintProjectionsTests, root_alg_test){
    Eigen::VectorXd coeffs(7);
    coeffs(0)=1;
    for (int ii=1; ii<7; ii++){
            coeffs(ii) = 0;
            //std::cout << coeffs(ii) << std::endl;
    }

    coeffs(1)=-9;
    coeffs(2)=135.0/4;
    coeffs(3)=-135.0/2;
    coeffs(4)=1215.0/16;
    coeffs(5)=-729.0/16;
    coeffs(6)=729.0/64;
    Eigen::VectorXd real_roots(6);
    Eigen::VectorXd img_roots(6);

    rpoly_plus_plus::FindPolynomialRootsJenkinsTraub(coeffs,&real_roots,&img_roots);

    // Only print here if you wish to see roots
    /*std::cout <<"root i =" << realroots[0] << std::endl;
    std::cout <<"root i =" << realroots[1] << std::endl;
    std::cout <<"root i =" << realroots[2] << std::endl;
    std::cout <<"root i =" << realroots[3] << std::endl;
    std::cout <<"root i =" << realroots[4] << std::endl;
    std::cout <<"root i =" << realroots[5] << std::endl;
    */
    EXPECT_TRUE(1);
}

TEST_F(WellConstraintProjectionsTests, eigvalues_test){
    using namespace arma;
    mat eigvec;
    vec eigval;
    //mat A = WellIndexCalculator::WellConstraintProjections::build_A_3p_qvec(coords_3d_qvec);
    // Create matrix with known eig_vec and eig_val
    // see: http://mathforum.org/library/drmath/view/51988.html
    mat A(3,3);
    A(0,0) = 3;
    A(0,1) = 4;
    A(0,2) = -1;
    A(1,0) = 4;
    A(1,1) = 3;
    A(1,2) = 1;
    A(2,0) = -1;
    A(2,1) = 1;
    A(2,2) = 1;

    eig_sym(eigval,eigvec,A);
    std::cout <<"Here is matrix A = (" << std::endl << A(0,0)<<"," << A(0,1) <<"," << A(0,2)<<")" << std::endl
                                                     <<A(1,0)<<"," << A(1,1) <<"," << A(1,2)<<")" << std::endl
                                                     <<A(2,0)<<"," << A(2,1) <<"," << A(2,2)<<")" << std::endl;

    std::cout <<"eigenval 1 = " << eigval(0) << std::endl;
    std::cout <<"eigenvector 1 = (" << eigvec(0,0)<<"," << eigvec(1,0) <<"," << eigvec(2,0)<<")" << std::endl;
    std::cout <<"eigenval 2 = " << eigval.at(1) << std::endl;
    std::cout <<"eigenvector 2 = (" << eigvec(0,1)<<"," << eigvec(1,1) <<"," << eigvec(2,1)<<")" << std::endl;
    std::cout <<"eigenval 3 = " << eigval.at(2) << std::endl;
    std::cout <<"eigenvector 3 = (" << eigvec(0,2)<<"," << eigvec(1,2) <<"," << eigvec(2,2)<<")" << std::endl;


    EXPECT_TRUE(abs(eigval.at(0) + sqrt(3)) < 10e-10);
    EXPECT_TRUE(eigval.at(1) - sqrt(3) < 10e-10);
    EXPECT_TRUE(eigval.at(2) == 7);
}

/*TEST_F(WellConstraintProjectionsTests, find_potential_vectors){
    double d = 1;


    QList<QVector3D*> cords_qvec;
    cords_qvec.append(WellIndexCalculator::GeometryFunctions::XYZ_to_qvec(coords.at(0)));
    cords_qvec.append(WellIndexCalculator::GeometryFunctions::XYZ_to_qvec(coords.at(1)));
    cords_qvec.append(WellIndexCalculator::GeometryFunctions::XYZ_to_qvec(coords.at(2)));
    cords_qvec.append(WellIndexCalculator::GeometryFunctions::XYZ_to_qvec(coords.at(3)));
    if(WellConstraintProjections::shortest_distance(cords_qvec)<d){
        std::cout << "shortest distance between line segments before moving = " << WellConstraintProjections::shortest_distance(cords_qvec) << std::endl;
        QList<QVector3D*> vectors = WellConstraintProjections::compute_interwell_vector_4d(coords,d);

        QVector3D *s = vectors.at(1);
        std::cout <<"(s1,s2,s3) = (" << s->x() << ", " << s->y() << ", " << s->z() << ") length = " << sqrt(s->x()*s->x() + s->y()*s->y() +s->z()*s->z()) << std::endl;
        QList<QVector3D*> moved_cords = WellConstraintProjections::move_points_4p(cords_qvec,d,s);
        std::cout << "moving corrds with s below" << std::endl;
        std::cout << "x0 moved from (" << coords.at(0)->x() <<"," << coords.at(0)->y() << "," << coords.at(0)->z() << ") to ("
                  << moved_cords.at(0)->x() <<"," << moved_cords.at(0)->y() << "," << moved_cords.at(0)->z()<< ")" << std::endl;
        std::cout << "x1 moved from (" << coords.at(1)->x() <<"," << coords.at(1)->y() << "," << coords.at(1)->z() << ") to ("
                  << moved_cords.at(1)->x() <<"," << moved_cords.at(1)->y() << "," << moved_cords.at(1)->z()<< ")" << std::endl;
        std::cout << "x2 moved from (" << coords.at(2)->x() <<"," << coords.at(2)->y() << "," << coords.at(2)->z() << ") to ("
                  << moved_cords.at(2)->x() <<"," << moved_cords.at(2)->y() << "," << moved_cords.at(2)->z()<< ")" << std::endl;
        std::cout << "x3 moved from (" << coords.at(3)->x() <<"," << coords.at(3)->y() << "," << coords.at(3)->z() << ") to ("
                  << moved_cords.at(3)->x() <<"," << moved_cords.at(3)->y() << "," << moved_cords.at(3)->z()<< ")" << std::endl;
        std::cout << "shortest distance between line segments after moving = " << WellConstraintProjections::shortest_distance(moved_cords) << std::endl;
    }
    else{std::cout << "shortest distance between line segments is = " << WellConstraintProjections::shortest_distance(cords_qvec) <<
                      " which is already more than d = " << d << std::endl;}

    EXPECT_TRUE(1);
}*/

/*TEST_F(WellConstraintProjectionsTests, interwell_4p_projection_test){
    double d = 6;
    // INITIALIZE
    QList<QVector3D*> cords_qvec;
    cords_qvec.append(WellIndexCalculator::GeometryFunctions::XYZ_to_qvec(coords.at(0)));
    cords_qvec.append(WellIndexCalculator::GeometryFunctions::XYZ_to_qvec(coords.at(1)));
    cords_qvec.append(WellIndexCalculator::GeometryFunctions::XYZ_to_qvec(coords.at(2)));
    cords_qvec.append(WellIndexCalculator::GeometryFunctions::XYZ_to_qvec(coords.at(3)));

    QList<QVector3D*> moved_cords = WellIndexCalculator::WellConstraintProjections::interwell_projection_4p(cords_qvec, d);
    std::cout << "inter-well 4p projection test" << std::endl;
    std::cout << "x0 moved from (" << coords.at(0)->x() <<"," << coords.at(0)->y() << "," << coords.at(0)->z() << ") to ("
              << moved_cords.at(0)->x() <<"," << moved_cords.at(0)->y() << "," << moved_cords.at(0)->z()<< ")" << std::endl;
    std::cout << "x1 moved from (" << coords.at(1)->x() <<"," << coords.at(1)->y() << "," << coords.at(1)->z() << ") to ("
              << moved_cords.at(1)->x() <<"," << moved_cords.at(1)->y() << "," << moved_cords.at(1)->z()<< ")" << std::endl;
    std::cout << "x2 moved from (" << coords.at(2)->x() <<"," << coords.at(2)->y() << "," << coords.at(2)->z() << ") to ("
              << moved_cords.at(2)->x() <<"," << moved_cords.at(2)->y() << "," << moved_cords.at(2)->z()<< ")" << std::endl;
    std::cout << "x3 moved from (" << coords.at(3)->x() <<"," << coords.at(3)->y() << "," << coords.at(3)->z() << ") to ("
              << moved_cords.at(3)->x() <<"," << moved_cords.at(3)->y() << "," << moved_cords.at(3)->z()<< ")" << std::endl;
    std::cout << "shortest distance between line segments after moving = " << WellConstraintProjections::shortest_distance(moved_cords) << std::endl;

    EXPECT_TRUE(1);
}*/

TEST_F(WellConstraintProjectionsTests, 3p_interwell_projection_test){
    // INITIALIZE

    QList<QVector3D> moved_cords = WellIndexCalculator::WellConstraintProjections::interwell_projection_3p(coords_3d_qvec, d);
    std::cout << "3 point inter-well projection test. shortest distance before moving = " << WellConstraintProjections::shortest_distance_3p(coords_3d_qvec) << std::endl;
    std::cout << "x0 moved from (" << coords_3d_qvec.at(0).x() <<"," << coords_3d_qvec.at(0).y() << "," << coords_3d_qvec.at(0).z() << ") to ("
              << moved_cords.at(0).x() <<"," << moved_cords.at(0).y() << "," << moved_cords.at(0).z()<< ")" << std::endl;
    std::cout << "x1 moved from (" << coords_3d_qvec.at(1).x() <<"," << coords_3d_qvec.at(1).y() << "," << coords_3d_qvec.at(1).z() << ") to ("
              << moved_cords.at(1).x() <<"," << moved_cords.at(1).y() << "," << moved_cords.at(1).z()<< ")" << std::endl;
    std::cout << "x2 moved from (" << coords_3d_qvec.at(2).x() <<"," << coords_3d_qvec.at(2).y() << "," << coords_3d_qvec.at(2).z() << ") to ("
              << moved_cords.at(2).x() <<"," << moved_cords.at(2).y() << "," << moved_cords.at(2).z()<< ")" << std::endl;
    std::cout << "shortest distance between line segments after moving = " << WellConstraintProjections::shortest_distance_3p(moved_cords) << std::endl;

    EXPECT_TRUE(1);
}

TEST_F(WellConstraintProjectionsTests, 3p_inter_updated_test){
    // INITIALIZE

    QList<QVector3D> moved_cords = WellIndexCalculator::WellConstraintProjections::interwell_projection_3p_eigen(coords_3d_qvec,d);
    if(moved_cords.length()>0){
        std::cout << "3 point inter-well projection test. shortest distance before moving = " << WellConstraintProjections::shortest_distance_3p(coords_3d_qvec) << std::endl;
        std::cout << "x0 moved from (" << coords_3d_qvec.at(0).x() <<"," << coords_3d_qvec.at(0).y() << "," << coords_3d_qvec.at(0).z() << ") to ("
                  << moved_cords.at(0).x() <<"," << moved_cords.at(0).y() << "," << moved_cords.at(0).z()<< ")" << std::endl;
        std::cout << "x1 moved from (" << coords_3d_qvec.at(1).x() <<"," << coords_3d_qvec.at(1).y() << "," << coords_3d_qvec.at(1).z() << ") to ("
                  << moved_cords.at(1).x() <<"," << moved_cords.at(1).y() << "," << moved_cords.at(1).z()<< ")" << std::endl;
        std::cout << "x2 moved from (" << coords_3d_qvec.at(2).x() <<"," << coords_3d_qvec.at(2).y() << "," << coords_3d_qvec.at(2).z() << ") to ("
                  << moved_cords.at(2).x() <<"," << moved_cords.at(2).y() << "," << moved_cords.at(2).z()<< ")" << std::endl;
        std::cout << "shortest distance between line segments after moving = " << WellConstraintProjections::shortest_distance_3p(moved_cords) << std::endl;

    }
    else std::cout << "no solution was found at all" << std::endl;
    EXPECT_TRUE(1);
}

TEST_F(WellConstraintProjectionsTests, interwell_projection_test){
    // INITIALIZE

    QList<QVector3D> moved_cords = WellIndexCalculator::WellConstraintProjections::interwell_constraint_projection_2nd(coords_qvec, d);
    std::cout << "inter-well 4p projection test. shortest distance before moving = " << WellConstraintProjections::shortest_distance(coords_qvec) << std::endl;
    if(moved_cords.length()>0){
        std::cout << "x0 moved from (" << coords_qvec.at(0).x() <<"," << coords_qvec.at(0).y() << "," << coords_qvec.at(0).z() << ") to ("
                  << moved_cords.at(0).x() <<"," << moved_cords.at(0).y() << "," << moved_cords.at(0).z()<< ")" << std::endl;
        std::cout << "x1 moved from (" << coords_qvec.at(1).x() <<"," << coords_qvec.at(1).y() << "," << coords_qvec.at(1).z() << ") to ("
                << moved_cords.at(1).x() <<"," << moved_cords.at(1).y() << "," << moved_cords.at(1).z()<< ")" << std::endl;
        std::cout << "x2 moved from (" << coords_qvec.at(2).x() <<"," << coords_qvec.at(2).y() << "," << coords_qvec.at(2).z() << ") to ("
                 << moved_cords.at(2).x() <<"," << moved_cords.at(2).y() << "," << moved_cords.at(2).z()<< ")" << std::endl;
        std::cout << "x3 moved from (" << coords_qvec.at(3).x() <<"," << coords_qvec.at(3).y() << "," << coords_qvec.at(3).z() << ") to ("
                  << moved_cords.at(3).x() <<"," << moved_cords.at(3).y() << "," << moved_cords.at(3).z()<< ")" << std::endl;
        std::cout << "shortest distance between line segments after moving = " << WellConstraintProjections::shortest_distance(moved_cords) << std::endl;
    }
    else std::cout << "no solution was found at all" << std::endl;
    EXPECT_TRUE(1);
}


/*TEST_F(WellConstraintProjectionsTests, find_potential_vectors_3d){
    double d = 6;

    QList<QVector3D*> cords_qvec;
    cords_qvec.append(WellIndexCalculator::GeometryFunctions::XYZ_to_qvec(coords_3d.at(0)));
    cords_qvec.append(WellIndexCalculator::GeometryFunctions::XYZ_to_qvec(coords_3d.at(1)));
    cords_qvec.append(WellIndexCalculator::GeometryFunctions::XYZ_to_qvec(coords_3d.at(2)));

    if(WellConstraintProjections::shortest_distance_3p(cords_qvec)<d){
        std::cout << "shortest distance between line segments before moving = " << WellConstraintProjections::shortest_distance_3p(cords_qvec) << std::endl;
        QList<QVector3D*> vectors = WellConstraintProjections::compute_interwell_vector_3d(coords_3d,d);
        QVector3D *s = vectors.at(0);
        std::cout <<"(s1,s2,s3) = (" << s->x() << ", " << s->y() << ", " << s->z() << ") length = " << sqrt(s->x()*s->x() + s->y()*s->y() +s->z()*s->z()) << std::endl;
        QList<QVector3D*> moved_cords = WellConstraintProjections::move_points_3p(cords_qvec,d,s);
        std::cout << "moving corrds with s below" << std::endl;
        std::cout << "x0 moved from (" << coords_3d.at(0)->x() <<"," << coords_3d.at(0)->y() << "," << coords_3d.at(0)->z() << ") to ("
                  << moved_cords.at(0)->x() <<"," << moved_cords.at(0)->y() << "," << moved_cords.at(0)->z()<< ")" << std::endl;
        std::cout << "x1 moved from (" << coords_3d.at(1)->x() <<"," << coords_3d.at(1)->y() << "," << coords_3d.at(1)->z() << ") to ("
                  << moved_cords.at(1)->x() <<"," << moved_cords.at(1)->y() << "," << moved_cords.at(1)->z()<< ")" << std::endl;
        std::cout << "x2 moved from (" << coords_3d.at(2)->x() <<"," << coords_3d.at(2)->y() << "," << coords_3d.at(2)->z() << ") to ("
                  << moved_cords.at(2)->x() <<"," << moved_cords.at(2)->y() << "," << moved_cords.at(2)->z()<< ")" << std::endl;
        std::cout << "shortest distance between point(x0) and line segment after moving = " << WellConstraintProjections::shortest_distance_3p(moved_cords) << std::endl;
    }
    else{
        std::cout << "shortest distance between point(x0) and line segment already large enough and = " << WellConstraintProjections::shortest_distance_3p(cords_qvec) << std::endl;
    }


    EXPECT_TRUE(1);
}*/

TEST_F(WellConstraintProjectionsTests, well_distance_test){
    // SLIGHT ERRORS; FIX
    double max = 8;
    double max_1 = 3;
    double min = 5;
    double min_1 = 5;
    QVector3D heel = QVector3D(0,0,0);
    QVector3D toe = QVector3D(10,0,0);
    QVector3D heel_1 = QVector3D(0,0,0);
    QVector3D toe_1 = QVector3D(3,0,0);
    QList<QVector3D> moved_points;
    QList<QVector3D> moved_points_1;
    QList<QVector3D> moved_points_2;
    moved_points = WellConstraintProjections::well_distance_projection(heel,toe,max,min,0);
    moved_points_1 = WellConstraintProjections::well_distance_projection(heel_1,toe_1,max_1,min_1,0);
    moved_points_2 = WellConstraintProjections::well_distance_projection(heel,toe,12,2,0);
    EXPECT_TRUE(moved_points.at(0).x()==1);
    EXPECT_TRUE(moved_points_1.at(0).x()==-1);
    EXPECT_TRUE(moved_points_1.at(1).x()==4);
    EXPECT_TRUE(moved_points_2.at(0) == heel);
}

TEST_F(WellConstraintProjectionsTests, LU_factorisation){

    Eigen::Matrix3d A;
    A << 8, 0, 0,
         0, 6, 6,
         0, 6, 6;
    Eigen::Vector3d b;
    b << 1, 4, 2;
    QList<Eigen::Vector3d> solution_vectors = WellIndexCalculator::WellConstraintProjections::non_inv_solution(A,b);

    for(int i=0; i<solution_vectors.length(); i++){
        std::cout << "solution vector with length "<< sqrt(solution_vectors.at(i)(0)*solution_vectors.at(i)(0)
                                                          +solution_vectors.at(i)(1)*solution_vectors.at(i)(1)
                                                          +solution_vectors.at(i)(2)*solution_vectors.at(i)(2)) <<
                                          " ="<< std::endl << solution_vectors.at(i) << std::endl;
    }

}

TEST_F(WellConstraintProjectionsTests, kkt_eq_solutions_test){

    arma::mat A = WellIndexCalculator::WellConstraintProjections::build_A_4p_qvec(coords_qvec);
    arma::vec b = WellIndexCalculator::WellConstraintProjections::build_b_4p_qvec(coords_qvec,d);
    QList<QVector3D> solution_vectors = WellConstraintProjections::kkt_eq_solutions(A,b);

    std::cout << "x3 = (" << coords_3d_qvec.at(0).x() << "," << coords_3d_qvec.at(0).y() << "," << coords_3d_qvec.at(0).z() << ")" << std::endl;
    std::cout << "x1 = (" << coords_3d_qvec.at(1).x() << "," << coords_3d_qvec.at(1).y() << "," << coords_3d_qvec.at(1).z() << ")" << std::endl;
    std::cout << "x2 = (" << coords_3d_qvec.at(2).x() << "," << coords_3d_qvec.at(2).y() << "," << coords_3d_qvec.at(2).z() << ")" << std::endl;
    std::cout << "distance between x1 x3 = " << (coords_3d_qvec.at(0)-coords_3d_qvec.at(1)).length() << std::endl;
    std::cout << "distance between x2 x3 = " << (coords_3d_qvec.at(0)-coords_3d_qvec.at(2)).length() << std::endl;

    std::cout << "shortest distance = " << WellIndexCalculator::WellConstraintProjections::shortest_distance(coords_qvec) << std::endl;
    for(int i=0; i<solution_vectors.length(); i++){
        std::cout << "solution vector with length "<< sqrt(solution_vectors.at(i).x()*solution_vectors.at(i).x()
                                                          +solution_vectors.at(i).y()*solution_vectors.at(i).y()
                                                          +solution_vectors.at(i).z()*solution_vectors.at(i).z());

        std::cout << " = (" << solution_vectors.at(i).x() << ", ";
        std::cout << solution_vectors.at(i).y() << ", ";
        std::cout << solution_vectors.at(i).z() << ") " << std::endl;
    }

}

TEST_F(WellConstraintProjectionsTests, diagonalize_orthogonality_test){

    arma::mat A = WellIndexCalculator::WellConstraintProjections::build_A_3p_qvec(coords_3d_qvec);
    arma::mat eigvec;
    arma::vec eigval;
    Eigen::Matrix3d A_temp;

    arma::eig_sym(eigval,eigvec,A);

    std::cout << "eigvec1 = (" << eigvec(0,0) << "," << eigvec(1,0) << "," << eigvec(2,0) << ") with length = "<<
              sqrt(eigvec(0,0)*eigvec(0,0) + eigvec(1,0)*eigvec(1,0) +eigvec(2,0)*eigvec(2,0))<< " and eigenvalue "<< eigval(0) << std::endl;
    std::cout << "eigvec2 = (" << eigvec(0,1) << "," << eigvec(1,1) << "," << eigvec(2,1) << ") with eigenvalue "<< eigval(1)<< ")" << std::endl;
    std::cout << "eigvec3 = (" << eigvec(0,2) << "," << eigvec(1,2) << "," << eigvec(2,2) << ") with eigenvalue "<< eigval(2)<< ")" << std::endl;

    std::cout << "dot product 1,2 = " << eigvec(0,0)*eigvec(0,1) + eigvec(1,0)*eigvec(1,1) +eigvec(2,0)*eigvec(2,1) << std::endl;
    std::cout << "dot product 1,3 = " << eigvec(0,0)*eigvec(0,2) + eigvec(1,0)*eigvec(1,2) +eigvec(2,0)*eigvec(2,2) << std::endl;
    std::cout << "dot product 3,1 = " << eigvec(0,2)*eigvec(0,1) + eigvec(1,2)*eigvec(1,1) +eigvec(2,2)*eigvec(2,1) << std::endl;


}

TEST_F(WellConstraintProjectionsTests, eigen_eigensolver_test){

    using namespace std;
    using namespace Eigen;

    Eigen::Vector3d xx1;
    Eigen::Vector3d xx2;
    Eigen::Vector3d xx3;
    Eigen::Vector3d xx4;
    xx1 << x_1.x(), x_1.y(), x_1.z();
    xx2 << x_2.x(), x_2.y(), x_2.z();
    xx3 << x_3.x(), x_3.y(), x_3.z();
    xx4 << x_4.x(), x_4.y(), x_4.z();
    QList<Eigen::Vector3d> coords;
    coords.append(xx1);
    coords.append(xx2);
    coords.append(xx3);
    coords.append(xx4);
    MatrixXd A = WellIndexCalculator::WellConstraintProjections::build_A_4p_eigen(coords);

    cout << "Here is a random symmetric 5x5 matrix, A:" << endl << A << endl << endl;
    SelfAdjointEigenSolver<MatrixXd> es(A);
    cout << "The eigenvalues of A are:" << endl << es.eigenvalues() << endl;
    cout << "The matrix of eigenvectors, V, is:" << endl << es.eigenvectors() << endl << endl;
    double lambda = es.eigenvalues()[1];
    cout << "Consider the second eigenvalue, lambda = " << lambda << endl;
    VectorXd v = es.eigenvectors().col(1);
    cout << "If v is the corresponding eigenvector, then lambda * v = " << endl << lambda * v << endl;
    cout << "... and A * v = " << endl << A * v << endl << endl;
    MatrixXd D = es.eigenvalues().asDiagonal();
    MatrixXd V = es.eigenvectors();
    cout << "Finally, V * D * V^(-1) = " << endl << V * D * V.inverse() << endl;

    cout << "checking eigenvector dot products, should all be zero" << endl;
    cout <<"v1,v2 = " << es.eigenvectors().col(0).transpose()*es.eigenvectors().col(1) << endl;
    cout <<"v1,v3 = " << es.eigenvectors().col(0).transpose()*es.eigenvectors().col(2) << endl;
    cout <<"v3,v2 = " << es.eigenvectors().col(2).transpose()*es.eigenvectors().col(1) << endl;
}

TEST_F(WellConstraintProjectionsTests, eigen_kkt_solver){

    Eigen::Vector3d xx1;
    Eigen::Vector3d xx2;
    Eigen::Vector3d xx3;
    Eigen::Vector3d xx4;
    xx1 << x_1.x(), x_1.y(), x_1.z();
    xx2 << x_2.x(), x_2.y(), x_2.z();
    xx3 << x_3.x(), x_3.y(), x_3.z();
    xx4 << x_4.x(), x_4.y(), x_4.z();
    QList<Eigen::Vector3d> newcoords;
    newcoords.append(xx1);
    newcoords.append(xx2);
    newcoords.append(xx3);
    newcoords.append(xx4);

    std::cout << "shortest distance" << WellIndexCalculator::WellConstraintProjections::shortest_distance_eigen(newcoords) << std::endl;

    Eigen::Matrix3d A = WellIndexCalculator::WellConstraintProjections::build_A_4p_eigen(newcoords);
    Eigen::Vector3d b = WellIndexCalculator::WellConstraintProjections::build_b_4p_eigen(newcoords,d);
    A = WellConstraintProjections::rm_entries_eps_matrix(A,10e-10);
    std::cout <<"A = " << std::endl << A << std::endl;
    std::cout <<"b = " << std::endl << b << std::endl;
    QList<Eigen::Vector3d> moved_points = WellConstraintProjections::interwell_constraint_projection_eigen(newcoords,d);

    std::cout <<"ksi 1 = " << std::endl << xx1 << std::endl;
    std::cout <<"ksi 2 = " << std::endl << xx2 << std::endl;
    std::cout <<"ksi 3 = " << std::endl << xx3 << std::endl;
    std::cout <<"ksi 4 = " << std::endl << xx4 << std::endl;

    std::cout << "solution is " << std::endl;
    for(int i =0; i<moved_points.length(); i++){
        std::cout << "x_" << i << std::endl << moved_points.at(i) << std::endl;
    }
    if (moved_points.length() >0){
        std::cout << "with movement cost = " << WellIndexCalculator::WellConstraintProjections::movement_cost_eig(newcoords,moved_points) << std::endl;
    }

}

TEST_F(WellConstraintProjectionsTests, interwell_multiple_wells_test){

    // Create 3 wells.
    Eigen::Vector3d x1;
    Eigen::Vector3d x2;
    Eigen::Vector3d y1;
    Eigen::Vector3d y2;
    Eigen::Vector3d z1;
    Eigen::Vector3d z2;
    Eigen::Vector3d q1;
    Eigen::Vector3d q2;
    Eigen::Vector3d w1;
    Eigen::Vector3d w2;
    x1 << -4, 1, 1;
    x2 << -1, 0, 0;
    y1 << 0, 1, 3;
    y2 << 0, -1, 0;
    z1 << -3, 1, 0;
    z2 << -2, -1, -1;
    //q1 << 4, -1, -1;
    //q2 << 1, 0, -2;
    //w1 << 3, 1, 0;
    //w2 << -2, 4, -2;
    q1 << -2, -2, 0;
    q2 << -2, 2, 0;
    w1 << 0, 0, 0;
    w2 << 3, 0, 0;

    QList<Eigen::Vector3d> well_1;
    well_1.append(x1);
    well_1.append(x2);
    QList<Eigen::Vector3d> well_2;
    well_2.append(y1);
    well_2.append(y2);
    QList<Eigen::Vector3d> well_3;
    well_3.append(z1);
    well_3.append(z2);
    QList<Eigen::Vector3d> well_4;
    well_4.append(q1);
    well_4.append(q2);
    QList<Eigen::Vector3d> well_5;
    well_5.append(w1);
    well_5.append(w2);

    QList<QList<Eigen::Vector3d>> all_wells;
    //all_wells.append(well_1);
    //all_wells.append(well_2);
    //all_wells.append(well_3);
    all_wells.append(well_4);
    all_wells.append(well_5);

    QList<QList<Eigen::Vector3d>> all_wells_moved = WellIndexCalculator::WellConstraintProjections::interwell_constraint_multiple_wells(all_wells, 4, 10e-4);
    QList<QList<Eigen::Vector3d>> all_wells_length_moved = WellIndexCalculator::WellConstraintProjections::well_length_constraint_multiple_wells(all_wells,10, 5,10e-8);
    QList<QList<Eigen::Vector3d>> all_wells_both_proj = WellIndexCalculator::WellConstraintProjections::both_constraints_multiple_wells(all_wells, 4, 10e-4, 10, 5, 10e-8);

    WellIndexCalculator::WellConstraintProjections::write_eigen_to_tikz(all_wells, "wells.txt");
    WellIndexCalculator::WellConstraintProjections::write_eigen_to_tikz(all_wells_moved, "wells_moved.txt");
    WellIndexCalculator::WellConstraintProjections::write_eigen_to_tikz(all_wells_length_moved, "wells_moved_length.txt");
    WellIndexCalculator::WellConstraintProjections::write_eigen_to_tikz(all_wells_both_proj, "wells_moved_both.txt");

    Eigen::Vector3d temp_comp_vec;
    temp_comp_vec << -2, -2, 1;

    if( q1.isApprox(temp_comp_vec)){
        std::cout << "Vectors are almost the same" << std::endl;
    }
    else std::cout << "Vectors are NOT almost the same" << std::endl;

}

}
