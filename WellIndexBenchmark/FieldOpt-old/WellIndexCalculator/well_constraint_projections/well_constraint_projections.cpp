#include "well_constraint_projections.h"

namespace WellIndexCalculator{

double WellConstraintProjections::sum_i(double a,double b,double c)
{
    return(a+b+c);
}

double WellConstraintProjections::sum_ij(double a, double b, double c)
{
    return(a*b + b*c + c*a);
}

double WellConstraintProjections::prod_i(double a, double b, double c)
{
    return(a*b*c);
}

double WellConstraintProjections::prod_Qtb(arma::mat Qt, arma::vec b, int k)
{
    arma::mat mat_Qt_k = Qt.row(k);
    return arma::dot(mat_Qt_k,b);
}

arma::mat WellConstraintProjections::Q_trans(arma::mat A)
{
    arma::vec eigval;
    arma::mat eigvec;
    arma::eig_sym(eigval,eigvec,A);


    return arma::trans(A);
}

arma::mat WellConstraintProjections::build_A(QList<QVector3D> coords)
{
    if(coords.length()==4){
        return WellConstraintProjections::build_A_4p_qvec(coords);
    }
    else return WellConstraintProjections::build_A_3p_qvec(coords);
}

arma::vec WellConstraintProjections::build_b(QList<QVector3D> coords, double d)
{
    if(coords.length()==4){
        return WellConstraintProjections::build_b_4p_qvec(coords,d);
    }
    else return WellConstraintProjections::build_b_3p_qvec(coords,d);
}

arma::mat WellConstraintProjections::build_A_4p_qvec(QList<QVector3D> coords)
{
    arma::vec vec1 = {coords.at(0).x(),coords.at(0).y(),coords.at(0).z()};
    arma::vec vec2 = {coords.at(1).x(),coords.at(1).y(),coords.at(1).z()};
    arma::vec vec3 = {coords.at(2).x(),coords.at(2).y(),coords.at(2).z()};
    arma::vec vec4 = {coords.at(3).x(),coords.at(3).y(),coords.at(3).z()};

    arma::vec avg_vec = 0.25*(vec1+vec2+vec3+vec4);
    vec1 = vec1 - avg_vec;
    vec2 = vec2 - avg_vec;
    vec3 = vec3 - avg_vec;
    vec4 = vec4 - avg_vec;

    arma::mat A = arma::kron(vec1,trans(vec1)) + arma::kron(vec2,trans(vec2)) + arma::kron(vec3,trans(vec3)) + arma::kron(vec4,trans(vec4));

    return A;
}

arma::vec WellConstraintProjections::build_b_4p_qvec(QList<QVector3D> coords, double d)
{
    arma::vec vec1 = {coords.at(0).x(),coords.at(0).y(),coords.at(0).z()};
    arma::vec vec2 = {coords.at(1).x(),coords.at(1).y(),coords.at(1).z()};
    arma::vec vec3 = {coords.at(2).x(),coords.at(2).y(),coords.at(2).z()};
    arma::vec vec4 = {coords.at(3).x(),coords.at(3).y(),coords.at(3).z()};

    arma::vec avg_vec = 0.25*(vec1+vec2+vec3+vec4);
    vec1 = vec1 - avg_vec;
    vec2 = vec2 - avg_vec;
    vec3 = vec3 - avg_vec;
    vec4 = vec4 - avg_vec;

    arma::vec b = 0.5*d*(vec1 + vec2 - vec3 - vec4);
    return b;
}

arma::mat WellConstraintProjections::build_A_3p_qvec(QList<QVector3D> coords)
{
    arma::vec vec1 = {coords.at(0).x(),coords.at(0).y(),coords.at(0).z()};
    arma::vec vec2 = {coords.at(1).x(),coords.at(1).y(),coords.at(1).z()};
    arma::vec vec3 = {coords.at(2).x(),coords.at(2).y(),coords.at(2).z()};

    arma::vec avg_vec = (1.0/3)*(vec1+vec2+vec3);
    vec1 = vec1 - avg_vec;
    vec2 = vec2 - avg_vec;
    vec3 = vec3 - avg_vec;

    arma::mat A = arma::kron(vec1,trans(vec1)) + arma::kron(vec2,trans(vec2)) + arma::kron(vec3,trans(vec3));

    return A;
}

arma::vec WellConstraintProjections::build_b_3p_qvec(QList<QVector3D> coords, double d)
{
    arma::vec vec1 = {coords.at(0).x(),coords.at(0).y(),coords.at(0).z()};
    arma::vec vec2 = {coords.at(1).x(),coords.at(1).y(),coords.at(1).z()};
    arma::vec vec3 = {coords.at(2).x(),coords.at(2).y(),coords.at(2).z()};

    arma::vec avg_vec = (1.0/3)*(vec1+vec2+vec3);
    vec1 = vec1 - avg_vec;
    vec2 = vec2 - avg_vec;
    vec3 = vec3 - avg_vec;

    arma::vec b = (2.0/3)*d*(vec1) -(1.0/3)*d*(vec2 + vec3);
    return b;
}

arma::mat WellConstraintProjections::build_A_4d(QList<Model::Reservoir::Grid::XYZCoordinate> coords)
{
    arma::vec vec1 = {coords.at(0).x(),coords.at(0).y(),coords.at(0).z()};
    arma::vec vec2 = {coords.at(1).x(),coords.at(1).y(),coords.at(1).z()};
    arma::vec vec3 = {coords.at(2).x(),coords.at(2).y(),coords.at(2).z()};
    arma::vec vec4 = {coords.at(3).x(),coords.at(3).y(),coords.at(3).z()};

    arma::vec avg_vec = 0.25*(vec1+vec2+vec3+vec4);
    vec1 = vec1 - avg_vec;
    vec2 = vec2 - avg_vec;
    vec3 = vec3 - avg_vec;
    vec4 = vec4 - avg_vec;

    arma::mat A = arma::kron(vec1,trans(vec1)) + arma::kron(vec2,trans(vec2)) + arma::kron(vec3,trans(vec3)) + arma::kron(vec4,trans(vec4));

    return A;
}

arma::vec WellConstraintProjections::build_b_4d(QList<Model::Reservoir::Grid::XYZCoordinate> coords, double d)
{
    arma::vec vec1 = {coords.at(0).x(),coords.at(0).y(),coords.at(0).z()};
    arma::vec vec2 = {coords.at(1).x(),coords.at(1).y(),coords.at(1).z()};
    arma::vec vec3 = {coords.at(2).x(),coords.at(2).y(),coords.at(2).z()};
    arma::vec vec4 = {coords.at(3).x(),coords.at(3).y(),coords.at(3).z()};

    arma::vec avg_vec = 0.25*(vec1+vec2+vec3+vec4);
    vec1 = vec1 - avg_vec;
    vec2 = vec2 - avg_vec;
    vec3 = vec3 - avg_vec;
    vec4 = vec4 - avg_vec;

    arma::vec b = 0.5*d*(vec1 + vec2 - vec3 - vec4);
    return b;
}

arma::mat WellConstraintProjections::build_A_3d(QList<Model::Reservoir::Grid::XYZCoordinate> coords)
{
    arma::vec vec1 = {coords.at(0).x(),coords.at(0).y(),coords.at(0).z()};
    arma::vec vec2 = {coords.at(1).x(),coords.at(1).y(),coords.at(1).z()};
    arma::vec vec3 = {coords.at(2).x(),coords.at(2).y(),coords.at(2).z()};

    arma::vec avg_vec = (1.0/3)*(vec1+vec2+vec3);
    vec1 = vec1 - avg_vec;
    vec2 = vec2 - avg_vec;
    vec3 = vec3 - avg_vec;

    arma::mat A = arma::kron(vec1,trans(vec1)) + arma::kron(vec2,trans(vec2)) + arma::kron(vec3,trans(vec3));

    return A;
}

arma::vec WellConstraintProjections::build_b_3d(QList<Model::Reservoir::Grid::XYZCoordinate> coords, double d)
{
    arma::vec vec1 = {coords.at(0).x(),coords.at(0).y(),coords.at(0).z()};
    arma::vec vec2 = {coords.at(1).x(),coords.at(1).y(),coords.at(1).z()};
    arma::vec vec3 = {coords.at(2).x(),coords.at(2).y(),coords.at(2).z()};

    arma::vec avg_vec = (1.0/3)*(vec1+vec2+vec3);
    vec1 = vec1 - avg_vec;
    vec2 = vec2 - avg_vec;
    vec3 = vec3 - avg_vec;

    arma::vec b = (2.0/3)*d*(vec1) -(1.0/3)*d*(vec2 + vec3);
    return b;
}

arma::vec WellConstraintProjections::lambdas(QList<Model::Reservoir::Grid::XYZCoordinate> coords, double d)
{
    arma::mat A = WellConstraintProjections::build_A_4d(coords);
    arma::mat b = WellConstraintProjections::build_b_4d(coords,d);
    arma::vec eigval;
    arma::mat eigvec;
    arma::eig_sym(eigval,eigvec,A);

    return 0;
}

Eigen::VectorXd WellConstraintProjections::coeff_vector(arma::vec D, arma::mat Qt, arma::vec b)
{
    double D1 = D(0);
    double D2 = D(1);
    double D3 = D(2);
    double sum_i = WellConstraintProjections::sum_i(D1,D2,D3);
    double sum_ij = WellConstraintProjections::sum_ij(D1,D2,D3);
    double prod_i = WellConstraintProjections::prod_i(D1,D2,D3);
    double Qtb_1 = WellConstraintProjections::prod_Qtb(Qt,b,0)*WellConstraintProjections::prod_Qtb(Qt,b,0);
    double Qtb_2 = WellConstraintProjections::prod_Qtb(Qt,b,1)*WellConstraintProjections::prod_Qtb(Qt,b,1);
    double Qtb_3 = WellConstraintProjections::prod_Qtb(Qt,b,2)*WellConstraintProjections::prod_Qtb(Qt,b,2);

    Eigen::VectorXd lambda(7);
    lambda(0) = 1;
    lambda(1) = -2*sum_i;
    lambda(2) = 2*sum_ij + sum_i*sum_i - (Qtb_1+Qtb_2+Qtb_3);
    lambda(3) = -2*prod_i - 2*sum_i*sum_ij - Qtb_1*(-2*D2 -2*D3)
                                           - Qtb_2*(-2*D3 -2*D1)
                                           - Qtb_3*(-2*D1 -2*D2);
    lambda(4) = 2*sum_i*prod_i + sum_ij*sum_ij - Qtb_1*(D2*D2 +D3*D3 + 4*D2*D3)
                                               - Qtb_2*(D3*D3 +D1*D1 + 4*D3*D1)
                                               - Qtb_3*(D1*D1 +D2*D2 + 4*D1*D2);
    lambda(5) = -2*sum_ij*prod_i - Qtb_1*(-2*D2*D3*D3 -2*D3*D2*D2)
                                 - Qtb_2*(-2*D3*D1*D1 -2*D1*D3*D3)
                                 - Qtb_3*(-2*D1*D2*D2 -2*D2*D1*D1);
    lambda(6) = prod_i*prod_i - Qtb_1*(D2*D2*D3*D3)
                              - Qtb_2*(D3*D3*D1*D1)
                              - Qtb_3*(D1*D1*D2*D2);

    return lambda;
}

Eigen::Vector3d WellConstraintProjections::non_inv_quad_coeffs(Eigen::Vector3d x, Eigen::Vector3d n)
{
    Eigen::Vector3d coeffs;

    coeffs(0) = n(0)*n(0) + n(1)*n(1) + n(2)*n(2);
    coeffs(1) = 2*( x(0)*n(0) + x(1)*n(1) + x(2)*n(2) );
    coeffs(2) = x(0)*x(0) + x(1)*x(1) + x(2)*x(2) - 1;

    return coeffs;
}

Eigen::Vector3d WellConstraintProjections::rm_entries_eps(Eigen::Vector3d m, double eps)
{
    for (int ii=0; ii<3; ii++){
            if (fabs(m[ii])<eps){
                m(ii) = 0;
            }
    }
    return m;
}

Eigen::Matrix3d WellConstraintProjections::rm_entries_eps_matrix(Eigen::Matrix3d m, double eps)
{
    for (int ii=0; ii<3; ii++){
        for(int jj=0; jj<3; jj++){
            if (fabs(m(ii,jj))<eps){
                m(ii,jj) = 0;
            }
        }
    }
    return m;
}

Eigen::VectorXd WellConstraintProjections::rm_entries_eps_coeffs(Eigen::VectorXd m, double eps)
{
    for (int ii=0; ii<7; ii++){
            if (fabs(m[ii])<eps){
                m(ii) = 0;
            }
    }
    return m;
}


QList<QVector3D> WellConstraintProjections::move_points_4p(QList<QVector3D> coords, double d, QVector3D s)
{
    QVector3D normal_vector = s;
    normal_vector.normalize();
    QVector3D avg_point = 0.25*(coords.at(0) + coords.at(1) + coords.at(2) + coords.at(3));
    QVector3D top_plane_point = avg_point + (d/2)*(s);
    QVector3D bot_plane_point = avg_point - (d/2)*(s);

    QVector3D x0moved = QVector3D(WellIndexCalculator::GeometryFunctions::project_point_to_plane(coords.at(0),s, top_plane_point));
    QVector3D x1moved = QVector3D(WellIndexCalculator::GeometryFunctions::project_point_to_plane(coords.at(1),s, top_plane_point));
    QVector3D x2moved = QVector3D(WellIndexCalculator::GeometryFunctions::project_point_to_plane(coords.at(2),s, bot_plane_point));
    QVector3D x3moved = QVector3D(WellIndexCalculator::GeometryFunctions::project_point_to_plane(coords.at(3),s, bot_plane_point));

    QList<QVector3D> moved_coords;
    moved_coords.append(x0moved);
    moved_coords.append(x1moved);
    moved_coords.append(x2moved);
    moved_coords.append(x3moved);
    return moved_coords;
}

QList<QVector3D> WellConstraintProjections::move_points_3p(QList<QVector3D> coords, double d, QVector3D s)
{
    QVector3D normal_vector = s;
    normal_vector.normalize();
    QVector3D avg_point = (1.0/3)*(coords.at(0) + coords.at(1) + coords.at(2));
    QVector3D top_plane_point = avg_point + (2.0*d/3)*(s);
    QVector3D bot_plane_point = avg_point - (1.0*d/3)*(s);

    QVector3D x0moved = QVector3D(WellIndexCalculator::GeometryFunctions::project_point_to_plane(coords.at(0),s, top_plane_point));
    QVector3D x1moved = QVector3D(WellIndexCalculator::GeometryFunctions::project_point_to_plane(coords.at(1),s, bot_plane_point));
    QVector3D x2moved = QVector3D(WellIndexCalculator::GeometryFunctions::project_point_to_plane(coords.at(2),s, bot_plane_point));

    QList<QVector3D> moved_coords;
    moved_coords.append(x0moved);
    moved_coords.append(x1moved);
    moved_coords.append(x2moved);
    return moved_coords;
}

QList<Model::Reservoir::Grid::XYZCoordinate> WellConstraintProjections::move_points_4p_XYZ(QList<Model::Reservoir::Grid::XYZCoordinate> coords, double d, QVector3D s)
{
    QVector3D x0 = QVector3D(WellIndexCalculator::GeometryFunctions::XYZ_to_qvec(coords.at(0)));
    QVector3D x1 = QVector3D(WellIndexCalculator::GeometryFunctions::XYZ_to_qvec(coords.at(1)));
    QVector3D x2 = QVector3D(WellIndexCalculator::GeometryFunctions::XYZ_to_qvec(coords.at(2)));
    QVector3D x3 = QVector3D(WellIndexCalculator::GeometryFunctions::XYZ_to_qvec(coords.at(3)));
    QVector3D normal_vector = s;
    normal_vector.normalize();
    QVector3D avg_point = 0.25*(x0 + x1 + x2 + x3);
    QVector3D top_plane_point = avg_point + (d/2)*(s);
    QVector3D bot_plane_point = avg_point - (d/2)*(s);

    QVector3D x0moved = QVector3D(WellIndexCalculator::GeometryFunctions::project_point_to_plane(x0,s, top_plane_point));
    QVector3D x1moved = QVector3D(WellIndexCalculator::GeometryFunctions::project_point_to_plane(x1,s, top_plane_point));
    QVector3D x2moved = QVector3D(WellIndexCalculator::GeometryFunctions::project_point_to_plane(x2,s, bot_plane_point));
    QVector3D x3moved = QVector3D(WellIndexCalculator::GeometryFunctions::project_point_to_plane(x3,s, bot_plane_point));

    QList<Model::Reservoir::Grid::XYZCoordinate> moved_coords;
    moved_coords.append(WellIndexCalculator::GeometryFunctions::qvec_to_XYZ(x0moved));
    moved_coords.append(WellIndexCalculator::GeometryFunctions::qvec_to_XYZ(x1moved));
    moved_coords.append(WellIndexCalculator::GeometryFunctions::qvec_to_XYZ(x2moved));
    moved_coords.append(WellIndexCalculator::GeometryFunctions::qvec_to_XYZ(x3moved));
    return moved_coords;
}

QList<QVector3D> WellConstraintProjections::kkt_eq_solutions(arma::mat A, arma::vec b)
{
    QList<QVector3D> solution_vectors;

    /* First assume that A-\mu I has an inverse.
     * We can find the inverse of it and solve
     * a sixth degree equation for \mu.
     */

    arma::mat eigvec;
    arma::vec eigval;
    arma::eig_sym(eigval,eigvec,A);
    arma::mat eigvec_trans = arma::inv(eigvec);//arma::trans(eigvec);

    // Compute coefficients of 6th degree polynomial
    Eigen::VectorXd coeffs = WellConstraintProjections::coeff_vector(eigval,eigvec_trans,b);

    // Compute roots of polynomial
    Eigen::VectorXd realroots(6);
    Eigen::VectorXd comproots(6);
    rpoly_plus_plus::FindPolynomialRootsJenkinsTraub(coeffs,&realroots,&comproots);
    std::cout << "polynomial coeffs = " << std::endl << coeffs << std::endl;

    arma::mat invmatr(3,3);
    invmatr.zeros();
    //double tolerance = 0.0001;

    for (int ii=0;ii<6;ii++){

        // Root may not be complex or an eigenvalue of A
        if(comproots[ii]==0 && eigval(0)!=realroots[ii] &&
                eigval(1)!=realroots[ii] && eigval(2)!=realroots[ii]){

            // We have found a valid root. Get vector s.
            double cur_root = realroots[ii];
            invmatr(0,0) = 1.00/(eigval(0)-cur_root);
            invmatr(1,1) = 1.00/(eigval(1)-cur_root);
            invmatr(2,2) = 1.00/(eigval(2)-cur_root);
            arma::vec s = eigvec * invmatr * eigvec_trans * b;
            QVector3D current_s = QVector3D(s(0),s(1),s(2));

            // No need to check that current vector has length 1 +- tolerance
            if( 1){//current_s->length() < 1 + tolerance && current_s->length() > 1 - tolerance){
                solution_vectors.append(current_s);
                std::cout << solution_vectors.length() <<" solution found. mu not eigenvalue of A" << std::endl;
            }
        }
    }

    /* Now for the second part assume that A-\mu I is not
     * invertible, i.e. \mu is an eigenvalue of A. Then
     * we either have an infinite amount of solutions of
     * (A-\mu I)s = b. Require s have length 1 to find
     * at most two solutions as long as all points are
     * not on the same line.
     */

    // Loop through all 3 eigenvalues of A
    for(int i=0; i<3; i++){

        QList<Eigen::Vector3d> eigenvalue_solutions;

        // Create linear system (A-\my I)s = b
        Eigen::Matrix3d A_eig;
        A_eig << A(0,0)-eigval(i), A(0,1)          , A(0,2),
                 A(1,0)          , A(1,1)-eigval(i), A(1,2),
                 A(2,0)          , A(2,1)           ,A(2,2)-eigval(i);
        Eigen::Vector3d b_eig;
        b_eig << b(0), b(1), b(2);

        // Check for existence of solution
        std::cout << "eigenvalue number "<< i << " = " << eigval(i) << std::endl;
        if(WellConstraintProjections::solution_existence(A_eig,b_eig)){
            std::cout << "Indeed solvable" << std::endl;
            eigenvalue_solutions = WellConstraintProjections::non_inv_solution(A_eig, b_eig);
        }

        // If any solutions, add them to solution_vectors
        for(int jj = 0; jj < eigenvalue_solutions.length(); jj++){
            QVector3D temp_solution = QVector3D(eigenvalue_solutions.at(jj)(0),
                                                eigenvalue_solutions.at(jj)(1),
                                                eigenvalue_solutions.at(jj)(2) );
            solution_vectors.append(temp_solution);
            std::cout << solution_vectors.length() <<" solution found. mu eigenvalue of A" << std::endl;
        }
    }

    return solution_vectors;

}

double WellConstraintProjections::shortest_distance_3p(QList<QVector3D> coords)
{
    QList<QVector3D> temp_coords;
    temp_coords.append(coords.at(0));
    temp_coords.append(coords.at(0));
    temp_coords.append(coords.at(1));
    temp_coords.append(coords.at(2));
    return shortest_distance(temp_coords);
}

QList<QVector3D> WellConstraintProjections::interwell_constraint_projection(QList<QVector3D> coords, double d)
{
    /* If the two line segments already satisfy
     * the interwell distance constraint,
     * simply return the same coordinates
     */
    if( WellConstraintProjections::shortest_distance(coords) >=d){
        std::cout <<"Initial points satisfy constraints" << std::endl;
        return coords;
    }

    QList<QVector3D> solution_coords;
    QList<QVector3D> moved_coords;
    QList<QVector3D> temp_coords;
    /* Iterate through moving points. First try moving 2 points, then 3 points
     * then 4 points. If problem can be solved moving k points, moving k+1 points
     * will be a worse solution. Return the best k point solution.
     */

    double cost = INFINITY;

    // Move 2 points
    std::cout <<"Initial points not feasible. Try moving 2 points" << std::endl;
    int two_point_index[4][2] = { {0, 2} ,
                                  {0, 3} ,
                                  {1, 2} ,
                                  {1, 3}  };
    for (int ii=0; ii<4; ii++){
        moved_coords = coords;
        temp_coords = WellConstraintProjections::well_distance_projection(coords.at(two_point_index[ii][0]),coords.at(two_point_index[ii][1]),INFINITY,d,10e-5);
        moved_coords.replace(two_point_index[ii][0],temp_coords.at(0));
        moved_coords.replace(two_point_index[ii][1],temp_coords.at(1));
        std::cout << "shortest distance - d = " << shortest_distance(moved_coords)-d << std::endl;
        if(WellConstraintProjections::shortest_distance(moved_coords) >=d && WellIndexCalculator::GeometryFunctions::movement_cost(coords,moved_coords) < cost){
            // If several moves of two points work, save the one with lovest movement cost
            cost = WellIndexCalculator::GeometryFunctions::movement_cost(coords,moved_coords);
            solution_coords = moved_coords;
        }
    }
    // If there were any succesful configurations, return the best one.
    if (cost < INFINITY){
        std::cout <<"Found 2-point solution" << std::endl;
        return solution_coords;
    }

    // If no 2 point movements were succesful, try moving 3 points.
    std::cout <<"No 2 point solution. Try moving 3 points" << std::endl;
    int three_point_index[4][3] = { {2, 0, 1} ,
                                    {3, 0, 1} ,
                                    {0, 2, 3} ,
                                    {1, 2, 3}  };
    for (int ii=0; ii<4; ii++){
        // Reset moved coords to initial state
        moved_coords = coords;

        // Choose which 3 points to move. (order is important, second and third entry should belong to same line segment)
        QList<QVector3D> input_cords_3p;
        for (int jj=0; jj<3; jj++){
            input_cords_3p.append(coords.at(three_point_index[ii][jj]));
        }

        // Solution of three point problem
        temp_coords = WellConstraintProjections::interwell_projection_3p_eigen(input_cords_3p,d);
        if(temp_coords.length()<1){temp_coords = input_cords_3p;}

        for (int jj=0; jj<3; jj++){
            moved_coords.replace(three_point_index[ii][jj],temp_coords.at(jj));
        }

        std::cout << "shortest distance unmoved 3p = " << shortest_distance_3p(input_cords_3p) << std::endl;
        std::cout << "shortest distance 3p = " << shortest_distance_3p(temp_coords) << std::endl;
        std::cout << "shortest distance 4p = " << shortest_distance(moved_coords) << std::endl;

        if(WellConstraintProjections::shortest_distance(moved_coords) >=d-0.01 && WellIndexCalculator::GeometryFunctions::movement_cost(coords,moved_coords) < cost){
            // If several moves of two points work, save the one with lovest movement cost
            std::cout<<"does this ever happen" << std::endl;
            cost = WellIndexCalculator::GeometryFunctions::movement_cost(coords,moved_coords);
            solution_coords = moved_coords;
        }
    }
    // If there were any succesful configurations, return the best one.
    if (cost < INFINITY){
        std::cout <<"Found 3-point solution" << std::endl;
        return solution_coords;}

    // If moving fewer than four points doesn't work we are only left with moving four points
    std::cout <<"No 3 point solution. Move 4 points" << std::endl;
    solution_coords = WellConstraintProjections::interwell_projection_4p(coords,d);

    return solution_coords;
}

QList<QVector3D> WellConstraintProjections::interwell_constraint_projection_2nd(QList<QVector3D> coords, double d)
{
    /* If the two line segments already satisfy
     * the interwell distance constraint,
     * simply return the same coordinates
     */
    if( WellConstraintProjections::shortest_distance(coords) >=d){
        std::cout <<"Initial points satisfy constraints" << std::endl;
        return coords;
    }

    QList<QVector3D> solution_coords;
    QList<QVector3D> moved_coords;
    QList<QVector3D> temp_coords;
    /* Iterate through moving points. First try moving 2 points, then 3 points
     * then 4 points. If problem can be solved moving k points, moving k+1 points
     * will be a worse solution. Return the best k point solution.
     */

    double cost = INFINITY;

    // Move 2 points
    std::cout <<"Initial points not feasible. Try moving 2 points" << std::endl;
    int two_point_index[4][2] = { {0, 2} ,
                                  {0, 3} ,
                                  {1, 2} ,
                                  {1, 3}  };
    for (int ii=0; ii<4; ii++){
        moved_coords = coords;
        temp_coords = WellConstraintProjections::well_distance_projection(coords.at(two_point_index[ii][0]),coords.at(two_point_index[ii][1]),INFINITY,d,10e-5);
        moved_coords.replace(two_point_index[ii][0],temp_coords.at(0));
        moved_coords.replace(two_point_index[ii][1],temp_coords.at(1));
        std::cout << "shortest distance - d = " << shortest_distance(moved_coords)-d << std::endl;
        if(WellConstraintProjections::shortest_distance(moved_coords) >=d && WellIndexCalculator::GeometryFunctions::movement_cost(coords,moved_coords) < cost){
            // If several moves of two points work, save the one with lovest movement cost
            cost = WellIndexCalculator::GeometryFunctions::movement_cost(coords,moved_coords);
            solution_coords = moved_coords;
        }
    }
    // If there were any succesful configurations, return the best one.
    if (cost < INFINITY){
        std::cout <<"Found 2-point solution" << std::endl;
        return solution_coords;
    }
    // ################## 3 POINT PART ############################
    // If no 2 point movements were succesful, try moving 3 points.
    std::cout <<"No 2 point solution. Try moving 3 points" << std::endl;
    int three_point_index[4][3] = { {2, 0, 1} ,
                                    {3, 0, 1} ,
                                    {0, 2, 3} ,
                                    {1, 2, 3}  };
    for (int ii=0; ii<4; ii++){
        // Reset moved coords to initial state
        moved_coords = coords;

        // Choose which 3 points to move. (order is important, second and third entry should belong to same line segment)
        QList<QVector3D> input_cords_3p;
        for (int jj=0; jj<3; jj++){
            input_cords_3p.append(coords.at(three_point_index[ii][jj]));
        }
        arma::mat temp_A = WellConstraintProjections::build_A(input_cords_3p);
        arma::mat temp_b = WellConstraintProjections::build_b(input_cords_3p,d);

        QList<QVector3D> solution_candidates = WellConstraintProjections::kkt_eq_solutions(temp_A,temp_b);
        std::cout << "there are " << solution_candidates.length() << " solution candidates" << std::endl;

        for(int sol_num = 0; sol_num < solution_candidates.length(); sol_num++){

            // Solution of three point problem
            temp_coords = WellConstraintProjections::move_points_3p(input_cords_3p,d,solution_candidates.at(sol_num));
            if(temp_coords.length()<1){temp_coords = input_cords_3p;}

            for (int jj=0; jj<3; jj++){
                moved_coords.replace(three_point_index[ii][jj],temp_coords.at(jj));
            }

            std::cout << "shortest distance unmoved 3p = " << shortest_distance_3p(input_cords_3p) << std::endl;
            std::cout << "shortest distance 3p = " << shortest_distance_3p(temp_coords) << std::endl;
            std::cout << "shortest distance 4p = " << shortest_distance(moved_coords) << std::endl;

            if(WellConstraintProjections::shortest_distance(moved_coords) >=d-0.001 && WellIndexCalculator::GeometryFunctions::movement_cost(coords,moved_coords) < cost){
                // If several moves of two points work, save the one with lovest movement cost
                cost = WellIndexCalculator::GeometryFunctions::movement_cost(coords,moved_coords);
                solution_coords = moved_coords;
            }
        }

    }
    // If there were any succesful configurations, return the best one.
    if (cost < INFINITY){
        std::cout <<"Found 3-point solution" << std::endl;
        return solution_coords;}
    // ################## END 3 POINT PART ########################



    // ################## 4 POINT PART ############################
    std::cout <<"Found no 3-point solution. Try 4 points" << std::endl;

    // Get all candidates for vector s
    arma::mat temp_A = WellConstraintProjections::build_A(coords);
    arma::mat temp_b = WellConstraintProjections::build_b(coords,d);
    QList<QVector3D> solution_candidates = WellConstraintProjections::kkt_eq_solutions(temp_A,temp_b);

    // Go through candidates s and pick the best one
    for(int sol_num = 0; sol_num < solution_candidates.length(); sol_num++){

        moved_coords = WellConstraintProjections::move_points_4p(coords,d,solution_candidates.at(sol_num));
        if(WellConstraintProjections::shortest_distance(moved_coords) >=d-0.001 && WellIndexCalculator::GeometryFunctions::movement_cost(coords,moved_coords) < cost){
            // If several candidates for s work, save the one with lovest movement cost
            cost = WellIndexCalculator::GeometryFunctions::movement_cost(coords,moved_coords);
            solution_coords = moved_coords;
        }
    }

    if(solution_coords.length()>0){std::cout <<"Found 4-point solution" << std::endl;}
    else std::cout <<"Found no solution to problem" << std::endl;
    return solution_coords;
}

QList<Eigen::Vector3d> WellConstraintProjections::interwell_constraint_projection_eigen(QList<Eigen::Vector3d> coords, double d)
{
    /* If the two line segments already satisfy
     * the interwell distance constraint,
     * simply return the same coordinates
     */
    if( WellConstraintProjections::shortest_distance_eigen(coords) >=d){
        std::cout <<"Initial points satisfy constraints" << std::endl;
        return coords;
    }

    QList<Eigen::Vector3d> solution_coords;
    QList<Eigen::Vector3d> moved_coords;
    QList<Eigen::Vector3d> temp_coords;
    /* Iterate through moving points. First try moving 2 points, then 3 points
     * then 4 points. If problem can be solved moving k points, moving k+1 points
     * will be a worse solution. Return the best k point solution.
     */

    double cost = INFINITY;

    // Move 2 points
    std::cout <<"Initial points not feasible. Try moving 2 points" << std::endl;
    int two_point_index[4][2] = { {0, 2} ,
                                  {0, 3} ,
                                  {1, 2} ,
                                  {1, 3}  };

    for (int ii=0; ii<4; ii++){
        moved_coords = coords;
        temp_coords = WellConstraintProjections::well_length_projection_eigen(coords.at(two_point_index[ii][0]),coords.at(two_point_index[ii][1]),INFINITY,d,10e-5);
        moved_coords.replace(two_point_index[ii][0],temp_coords.at(0));
        moved_coords.replace(two_point_index[ii][1],temp_coords.at(1));
        if(WellConstraintProjections::shortest_distance_eigen(moved_coords) >=d && WellConstraintProjections::movement_cost_eig(coords,moved_coords) < cost){
            // If several moves of two points work, save the one with lovest movement cost
            cost = WellConstraintProjections::movement_cost_eig(coords,moved_coords);
            solution_coords = moved_coords;
        }
    }
    // If there were any succesful configurations, return the best one.
    if (cost < INFINITY){
        std::cout <<"Found 2-point solution" << std::endl;
        return solution_coords;
    }

    // ################## 3 POINT PART ############################
    // If no 2 point movements were succesful, try moving 3 points.
    std::cout <<"No 2 point solution. Try moving 3 points" << std::endl;
    int three_point_index[4][3] = { {2, 0, 1} ,
                                    {3, 0, 1} ,
                                    {0, 2, 3} ,
                                    {1, 2, 3}  };
    for (int ii=0; ii<4; ii++){
        // Reset moved coords to initial state
        moved_coords = coords;

        // Choose which 3 points to move. (order is important, second and third entry should belong to same line segment)
        QList<Eigen::Vector3d> input_cords_3p;
        for (int jj=0; jj<3; jj++){
            input_cords_3p.append(coords.at(three_point_index[ii][jj]));
        }
        Eigen::Matrix3d temp_A = WellConstraintProjections::build_A_3p_eigen(input_cords_3p);
        Eigen::Vector3d temp_b = WellConstraintProjections::build_b_3p_eigen(input_cords_3p,d);

        /* The kkt_eg_solutions solver handles some numerical issues
         * like A having some values close to machine epsilon and
         * eigenvalues being close to 0. Just assume that any solution
         * must be among the ones given in solution candidates. we check
         * all of them.
         */
        QList<Eigen::Vector3d> solution_candidates = WellConstraintProjections::kkt_eq_solutions_eigen(temp_A,temp_b);
        //std::cout << "there are " << solution_candidates.length() << " solution candidates" << std::endl;

        for(int sol_num = 0; sol_num < solution_candidates.length(); sol_num++){
            // Solution of three point problem
            temp_coords = WellConstraintProjections::move_points_3p_eigen(input_cords_3p,d,solution_candidates.at(sol_num));
            if(temp_coords.length()<1){temp_coords = input_cords_3p;}

            for (int jj=0; jj<3; jj++){
                moved_coords.replace(three_point_index[ii][jj],temp_coords.at(jj));
            }

            /*std::cout << "shortest distance unmoved 3p = " << shortest_distance_3p_eigen(input_cords_3p) << std::endl;
            std::cout << "shortest distance 3p = " << shortest_distance_3p_eigen(temp_coords) << std::endl;
            std::cout << "shortest distance 4p = " << shortest_distance_eigen(moved_coords) << std::endl;
            std::cout << "movement cost = " << WellConstraintProjections::movement_cost_eig(coords,moved_coords) << std::endl;*/

            if(WellConstraintProjections::shortest_distance_eigen(moved_coords) >=d-0.001 &&
                    WellConstraintProjections::movement_cost_eig(coords,moved_coords) < cost){
                // If several moves of two points work, save the one with lovest movement cost
                cost = WellConstraintProjections::movement_cost_eig(coords,moved_coords);
                solution_coords = moved_coords;
            }
        }

    }
    // If there were any succesful configurations, return the best one.
    if (cost < INFINITY){
        std::cout <<"Found 3-point solution" << std::endl;
        return solution_coords;}
    // ################## END 3 POINT PART ########################



    // ################## 4 POINT PART ############################
    std::cout <<"Found no 3-point solution. Try 4 points" << std::endl;

    // Get all candidates for vector s
    /* The kkt_eg_solutions solver handles some numerical issues
     * like A having some values close to machine epsilon and
     * eigenvalues being close to 0. Just assume that any solution
     * must be among the ones given in solution candidates. we check
     * all of them.
     */
    Eigen::Matrix3d temp_A = WellConstraintProjections::build_A_4p_eigen(coords);
    Eigen::Vector3d temp_b = WellConstraintProjections::build_b_4p_eigen(coords,d);
    QList<Eigen::Vector3d> solution_candidates = WellConstraintProjections::kkt_eq_solutions_eigen(temp_A,temp_b);

    // Go through candidates s and pick the best one
    for(int sol_num = 0; sol_num < solution_candidates.length(); sol_num++){

        moved_coords = WellConstraintProjections::move_points_4p_eigen(coords,d,solution_candidates.at(sol_num));
        if(WellConstraintProjections::shortest_distance_eigen(moved_coords) >=d-0.001 && WellConstraintProjections::movement_cost_eig(coords,moved_coords) < cost){
            // If several candidates for s work, save the one with lovest movement cost
            cost = WellConstraintProjections::movement_cost_eig(coords,moved_coords);
            solution_coords = moved_coords;
        }
    }

    if(solution_coords.length()>0){std::cout <<"Found 4-point solution" << std::endl;}
    else std::cout <<"Found no solution to problem" << std::endl;

    return solution_coords;
}

double WellConstraintProjections::shortest_distance_n_wells(QList<QList<Eigen::Vector3d>> coords, int n)
{
    double shortest_distance = INFINITY;

    // for all pairs of wells (i,j) i != j
    for (int i=0; i<n; i++){
        for (int j=i+1; j<n; j++){

            // Create QList with current pair of wells
            QList<Eigen::Vector3d> current_pair;
            current_pair.append(coords.at(i).at(0));
            current_pair.append(coords.at(i).at(1));
            current_pair.append(coords.at(j).at(0));
            current_pair.append(coords.at(j).at(1));

            if(WellConstraintProjections::shortest_distance_eigen(current_pair)<shortest_distance){
                shortest_distance = WellConstraintProjections::shortest_distance_eigen(current_pair);
            }
        }
    }

    return shortest_distance;
}

QList<QList<Eigen::Vector3d>> WellConstraintProjections::interwell_constraint_multiple_wells(QList<QList<Eigen::Vector3d>> coords, double d, double tol)
{
    double shortest_distance = 0;
    double n = coords.length();

    /* loop through all wells as
     * long as some pair of wells
     * violate inter-well distance
     * constraint. Tolerance tol
     * added for quicker convergence.
     */
    int max_iter =10000;
    int iter = 0;
    while(shortest_distance<d-tol &&iter < max_iter){
        // for all pairs of wells (i,j) i != j
        for (int i=0; i<n; i++){
            for (int j=i+1; j<n; j++){

                // Create QList with current pair of wells
                QList<Eigen::Vector3d> current_pair;
                current_pair.append(coords.at(i).at(0));
                current_pair.append(coords.at(i).at(1));
                current_pair.append(coords.at(j).at(0));
                current_pair.append(coords.at(j).at(1));

                // Project pair of wells
                current_pair = WellConstraintProjections::interwell_constraint_projection_eigen(current_pair,d);

                // Replace initial well pair with projected pair.
                coords[i].replace(0,current_pair.at(0));
                coords[i].replace(1,current_pair.at(1));
                coords[j].replace(0,current_pair.at(2));
                coords[j].replace(1,current_pair.at(3));

            }
        }

        shortest_distance = WellConstraintProjections::shortest_distance_n_wells(coords,n);
        std::cout << "current shortest distance = " <<shortest_distance << std::endl;
        iter+=1;
        //sleep(0.001);
    }
    if (iter < max_iter){std::cout << "converged in " << iter << " steps!" << std::endl;}
    else std::cout << "No convergence. Max iterations " << iter << " reached" << std::endl;



    return coords;
}

void WellConstraintProjections::write_eigen_to_tikz(QList<QList<Eigen::Vector3d> > all_wells, std::string name)
{

    std::ofstream myfile;
    myfile.open (name);

    double n = all_wells.length();
    myfile << "\\begin{axis}[grid=major," << std::endl;
    myfile << "xmin=-10, xmax=10," << std::endl;
    myfile << "ymin=-10, ymax=10," << std::endl;
    myfile << "zmin=-10, zmax=10]" << std::endl;
    for (int i=0; i<n; i++){

        myfile << "\\addplot3 coordinates { (" << all_wells.at(i).at(0)(0) <<"," << all_wells.at(i).at(0)(1) <<"," << all_wells.at(i).at(0)(2) <<
                ") (" << all_wells.at(i).at(1)(0) <<"," << all_wells.at(i).at(1)(1) <<"," << all_wells.at(i).at(1)(2) << ") };" << std::endl;
        myfile << "\\addlegendentry{$\\text{Well}_" << i+1 << "$};" << std::endl;

    }
    myfile << "\\end{axis}" << std::endl;

    myfile.close();
}

QList<QList<Eigen::Vector3d> > WellConstraintProjections::well_length_constraint_multiple_wells(QList<QList<Eigen::Vector3d> > wells, double max, double min, double epsilon)
{
    QList<QList<Eigen::Vector3d>> projected_wells;
    int n = wells.length();

    // for all wells
    for (int i=0; i<n; i++){

        // Create QList with current pair of wells
        Eigen::Vector3d current_heel = wells.at(i).at(0);
        Eigen::Vector3d current_toe = wells.at(i).at(1);

        /* Project current well to feasible length
         * and add to list of projected wells
         */
        projected_wells.append(WellConstraintProjections::well_length_projection_eigen(current_heel, current_toe, max, min, epsilon));
    }

    return projected_wells;
}

bool WellConstraintProjections::feasible_well_length(QList<QList<Eigen::Vector3d> > coords, double max, double min, double tol)
{
    // Number of wells
    int n = coords.length();
    bool is_feasible = true;

    // loop through all wells
    for (int i=0; i<n; i++){

        //Find length of current well (vector between endpoints)
        double current_length;
        current_length = (coords.at(i).at(0) - coords.at(i).at(1)).norm();

        // If smaller than min or larger than max (with tolerance tol). not feasible
        if( current_length < min - tol || current_length > max + tol ){ is_feasible = false;}

    }

    return is_feasible;
}

bool WellConstraintProjections::feasible_interwell_distance(QList<QList<Eigen::Vector3d> > coords, double d, double tol)
{
    // Number of wells
    int n = coords.length();
    bool is_feasible = true;
    if(WellConstraintProjections::shortest_distance_n_wells(coords, n) < d-tol){ is_feasible = false;}

    return is_feasible;
}

QList<QList<Eigen::Vector3d> > WellConstraintProjections::both_constraints_multiple_wells(QList<QList<Eigen::Vector3d> > coords, double d, double tol, double max, double min, double epsilon)
{
    int iter = 0;

    // While at least one of the constraints is violated, continue projecting
    while(!WellConstraintProjections::feasible_interwell_distance(coords, d, 3*tol) ||
          !WellConstraintProjections::feasible_well_length(coords, max, min, tol)){

        if(!WellConstraintProjections::feasible_interwell_distance(coords, d, tol)){std::cout << "interwell distance not feasible" << std::endl;}
        if(!WellConstraintProjections::feasible_well_length(coords, max, min, tol)){std::cout << "well length not feasible" << std::endl;}

        coords = WellConstraintProjections::well_length_constraint_multiple_wells(coords, max, min, epsilon);
        coords = WellConstraintProjections::interwell_constraint_multiple_wells(coords, d, tol);

        iter+=1;
        if(iter > 100){std::cout <<"above max number of iterations" << std::endl; return coords;}
    }

    std::cout << iter << " iterations" << std::endl;
    return coords;
}

double WellConstraintProjections::shortest_distance_eigen(QList<Eigen::Vector3d> coords)
{
    /* Function runs through all possible combinations of
     * where the two closest points could be located. Return
     * when a solution is found. This function is a slightly
     * editet version of the one from:
     * http://www.geometrictools.com/GTEngine/Include/Mathematics/GteDistSegmentSegmentExact.h
     */

    // David Eberly, Geometric Tools, Redmond WA 98052
    // Copyright (c) 1998-2016
    // Distributed under the Boost Software License, Version 1.0.
    // http://www.boost.org/LICENSE_1_0.txt
    // http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
    // File Version: 2.1.0 (2016/01/25)d

    Eigen::Vector3d P0 = coords.at(0);
    Eigen::Vector3d P1 = coords.at(1);
    Eigen::Vector3d Q0 = coords.at(2);
    Eigen::Vector3d Q1 = coords.at(3);

    Eigen::Vector3d P1mP0 = P1 - P0;
    Eigen::Vector3d Q1mQ0 = Q1 - Q0;
    Eigen::Vector3d P0mQ0 = P0 - Q0;

    double a = P1mP0.transpose()*P1mP0;
    double b = P1mP0.transpose()*Q1mQ0;
    double c = Q1mQ0.transpose()*Q1mQ0;
    double d = P1mP0.transpose()*P0mQ0;
    double e = Q1mQ0.transpose()*P0mQ0;
    double const zero = 0;
    double const one  = 1;
    double det = a * c - b * b;
    double s, t, nd, bmd, bte, ctd, bpe, ate, btd;

    if (det > zero)
    {
        bte = b * e;
        ctd = c * d;
        if (bte <= ctd)  // s <= 0
        {
            s = zero;
            if (e <= zero)  // t <= 0
            {
                // region 6
                t = zero;
                nd = -d;
                if (nd >= a)
                {
                    s = one;
                }
                else if (nd > zero)
                {
                    s = nd / a;
                }
                // else: s is already zero
            }
            else if (e < c)  // 0 < t < 1
            {
                // region 5
                t = e / c;
            }
            else  // t >= 1
            {
                // region 4
                t = one;
                bmd = b - d;
                if (bmd >= a)
                {
                    s = one;
                }
                else if (bmd > zero)
                {
                    s = bmd / a;
                }
                // else:  s is already zero
            }
        }
        else  // s > 0
        {
            s = bte - ctd;
            if (s >= det)  // s >= 1
            {
                // s = 1
                s = one;
                bpe = b + e;
                if (bpe <= zero)  // t <= 0
                {
                    // region 8
                    t = zero;
                    nd = -d;
                    if (nd <= zero)
                    {
                        s = zero;
                    }
                    else if (nd < a)
                    {
                        s = nd / a;
                    }
                    // else: s is already one
                }
                else if (bpe < c)  // 0 < t < 1
                {
                    // region 1
                    t = bpe / c;
                }
                else  // t >= 1
                {
                    // region 2
                    t = one;
                    bmd = b - d;
                    if (bmd <= zero)
                    {
                        s = zero;
                    }
                    else if (bmd < a)
                    {
                        s = bmd / a;
                    }
                    // else:  s is already one
                }
            }
            else  // 0 < s < 1
            {
                ate = a * e;
                btd = b * d;
                if (ate <= btd)  // t <= 0
                {
                    // region 7
                    t = zero;
                    nd = -d;
                    if (nd <= zero)
                    {
                        s = zero;
                    }
                    else if (nd >= a)
                    {
                        s = one;
                    }
                    else
                    {
                        s = nd / a;
                    }
                }
                else  // t > 0
                {
                    t = ate - btd;
                    if (t >= det)  // t >= 1
                    {
                        // region 3
                        t = one;
                        bmd = b - d;
                        if (bmd <= zero)
                        {
                            s = zero;
                        }
                        else if (bmd >= a)
                        {
                            s = one;
                        }
                        else
                        {
                            s = bmd / a;
                        }
                    }
                    else  // 0 < t < 1
                    {
                        // region 0
                        s /= det;
                        t /= det;
                    }
                }
            }
        }
    }
    else
    {
        // The segments are parallel.  The quadratic factors to R(s,t) =
        // a*(s-(b/a)*t)^2 + 2*d*(s - (b/a)*t) + f, where a*c = b^2,
        // e = b*d/a, f = |P0-Q0|^2, and b is not zero.  R is constant along
        // lines of the form s-(b/a)*t = k, and the minimum of R occurs on the
        // line a*s - b*t + d = 0.  This line must intersect both the s-axis
        // and the t-axis because 'a' and 'b' are not zero.  Because of
        // parallelism, the line is also represented by -b*s + c*t - e = 0.
        //
        // The code determines an edge of the domain [0,1]^2 that intersects
        // the minimum line, or if none of the edges intersect, it determines
        // the closest corner to the minimum line.  The conditionals are
        // designed to test first for intersection with the t-axis (s = 0)
        // using -b*s + c*t - e = 0 and then with the s-axis (t = 0) using
        // a*s - b*t + d = 0.

        // When s = 0, solve c*t - e = 0 (t = e/c).
        if (e <= zero)  // t <= 0
        {
            // Now solve a*s - b*t + d = 0 for t = 0 (s = -d/a).
            t = zero;
            nd = -d;
            if (nd <= zero)  // s <= 0
            {
                // region 6
                s = zero;
            }
            else if (nd >= a)  // s >= 1
            {
                // region 8
                s = one;
            }
            else  // 0 < s < 1
            {
                // region 7
                s = nd / a;
            }
        }
        else if (e >= c)  // t >= 1
        {
            // Now solve a*s - b*t + d = 0 for t = 1 (s = (b-d)/a).
            t = one;
            bmd = b - d;
            if (bmd <= zero)  // s <= 0
            {
                // region 4
                s = zero;
            }
            else if (bmd >= a)  // s >= 1
            {
                // region 2
                s = one;
            }
            else  // 0 < s < 1
            {
                // region 3
                s = bmd / a;
            }
        }
        else  // 0 < t < 1
        {
            // The point (0,e/c) is on the line and domain, so we have one
            // point at which R is a minimum.
            s = zero;
            t = e / c;
        }
    }

    /*result.parameter[0] = s;
    result.parameter[1] = t;*/
    Eigen::Vector3d closest_P;
    Eigen::Vector3d closest_Q;
    closest_P = P0 + s*P1mP0;
    closest_Q = Q0 + t*Q1mQ0;
    /*result.closest[0] = P0 + s * P1mP0;
    result.closest[1] = Q0 + t * Q1mQ0;*/
    Eigen::Vector3d closest_distance_vec = closest_Q - closest_P;
    double distance = sqrt(closest_distance_vec.transpose()*closest_distance_vec);
    return distance;
}

double WellConstraintProjections::shortest_distance_3p_eigen(QList<Eigen::Vector3d> coords)
{
    QList<Eigen::Vector3d> temp_coords;
    temp_coords.append(coords.at(0));
    temp_coords.append(coords.at(0));
    temp_coords.append(coords.at(1));
    temp_coords.append(coords.at(2));
    return shortest_distance_eigen(temp_coords);
}

QList<Eigen::Vector3d> WellConstraintProjections::well_length_projection_eigen(Eigen::Vector3d heel, Eigen::Vector3d toe, double max, double min, double epsilon)
{
    QList<Eigen::Vector3d> projected_points;
    Eigen::Vector3d moved_heel;
    Eigen::Vector3d moved_toe;

    // Need the vector going from heel to toe to project points
    Eigen::Vector3d heel_to_toe_vec = toe-heel;
    // Distance between heel and toe.
    double d = heel_to_toe_vec.norm();

    // heel and toe same point.
    // All directions equally good.
    if(d==0){
        Eigen::Vector3d unit_vector;
        unit_vector << 1,0,0;
        moved_heel = heel + (min/2)*unit_vector;
        moved_toe  = heel - (min/2)*unit_vector;
        projected_points.append(moved_heel);
        projected_points.append(moved_toe);
        return projected_points;
    }

    // Normalize vector to get correct distance
    heel_to_toe_vec.normalize();

    // Trivial case
    if(d<=max && d>=min){
        projected_points.append(heel);
        projected_points.append(toe);
    }

    // Distance too long
    else if(d>max){
        double move_distance = 0.5*(d-max+(epsilon/2));
        moved_heel = heel + move_distance*heel_to_toe_vec;
        moved_toe =  toe  - move_distance*heel_to_toe_vec;
        projected_points.append(moved_heel);
        projected_points.append(moved_toe);
    }

    // Distance too short
    else{
        double move_distance = 0.5*(d-min-(epsilon/2));
        moved_heel = heel + move_distance*heel_to_toe_vec;
        moved_toe =  toe  - move_distance*heel_to_toe_vec;
        projected_points.append(moved_heel);
        projected_points.append(moved_toe);
    }

    return projected_points;
}

double WellConstraintProjections::shortest_distance(QList<QVector3D> coords)
{
    /* Function runs through all possible combinations of
     * where the two closest points could be located. Return
     * when a solution is found. This function is a slightly
     * editet version of the one from:
     * http://www.geometrictools.com/GTEngine/Include/Mathematics/GteDistSegmentSegmentExact.h
     */

    // David Eberly, Geometric Tools, Redmond WA 98052
    // Copyright (c) 1998-2016
    // Distributed under the Boost Software License, Version 1.0.
    // http://www.boost.org/LICENSE_1_0.txt
    // http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
    // File Version: 2.1.0 (2016/01/25)d

    QVector3D P0 = QVector3D(coords.at(0));
    QVector3D P1 = QVector3D(coords.at(1));
    QVector3D Q0 = QVector3D(coords.at(2));
    QVector3D Q1 = QVector3D(coords.at(3));

    QVector3D P1mP0 = P1 - P0;
    QVector3D Q1mQ0 = Q1 - Q0;
    QVector3D P0mQ0 = P0 - Q0;
    double a = QVector3D::dotProduct(P1mP0, P1mP0);
    double b = QVector3D::dotProduct(P1mP0, Q1mQ0);
    double c = QVector3D::dotProduct(Q1mQ0, Q1mQ0);
    double d = QVector3D::dotProduct(P1mP0, P0mQ0);
    double e = QVector3D::dotProduct(Q1mQ0, P0mQ0);
    double const zero = 0;
    double const one  = 1;
    double det = a * c - b * b;
    double s, t, nd, bmd, bte, ctd, bpe, ate, btd;

    if (det > zero)
    {
        bte = b * e;
        ctd = c * d;
        if (bte <= ctd)  // s <= 0
        {
            s = zero;
            if (e <= zero)  // t <= 0
            {
                // region 6
                t = zero;
                nd = -d;
                if (nd >= a)
                {
                    s = one;
                }
                else if (nd > zero)
                {
                    s = nd / a;
                }
                // else: s is already zero
            }
            else if (e < c)  // 0 < t < 1
            {
                // region 5
                t = e / c;
            }
            else  // t >= 1
            {
                // region 4
                t = one;
                bmd = b - d;
                if (bmd >= a)
                {
                    s = one;
                }
                else if (bmd > zero)
                {
                    s = bmd / a;
                }
                // else:  s is already zero
            }
        }
        else  // s > 0
        {
            s = bte - ctd;
            if (s >= det)  // s >= 1
            {
                // s = 1
                s = one;
                bpe = b + e;
                if (bpe <= zero)  // t <= 0
                {
                    // region 8
                    t = zero;
                    nd = -d;
                    if (nd <= zero)
                    {
                        s = zero;
                    }
                    else if (nd < a)
                    {
                        s = nd / a;
                    }
                    // else: s is already one
                }
                else if (bpe < c)  // 0 < t < 1
                {
                    // region 1
                    t = bpe / c;
                }
                else  // t >= 1
                {
                    // region 2
                    t = one;
                    bmd = b - d;
                    if (bmd <= zero)
                    {
                        s = zero;
                    }
                    else if (bmd < a)
                    {
                        s = bmd / a;
                    }
                    // else:  s is already one
                }
            }
            else  // 0 < s < 1
            {
                ate = a * e;
                btd = b * d;
                if (ate <= btd)  // t <= 0
                {
                    // region 7
                    t = zero;
                    nd = -d;
                    if (nd <= zero)
                    {
                        s = zero;
                    }
                    else if (nd >= a)
                    {
                        s = one;
                    }
                    else
                    {
                        s = nd / a;
                    }
                }
                else  // t > 0
                {
                    t = ate - btd;
                    if (t >= det)  // t >= 1
                    {
                        // region 3
                        t = one;
                        bmd = b - d;
                        if (bmd <= zero)
                        {
                            s = zero;
                        }
                        else if (bmd >= a)
                        {
                            s = one;
                        }
                        else
                        {
                            s = bmd / a;
                        }
                    }
                    else  // 0 < t < 1
                    {
                        // region 0
                        s /= det;
                        t /= det;
                    }
                }
            }
        }
    }
    else
    {
        // The segments are parallel.  The quadratic factors to R(s,t) =
        // a*(s-(b/a)*t)^2 + 2*d*(s - (b/a)*t) + f, where a*c = b^2,
        // e = b*d/a, f = |P0-Q0|^2, and b is not zero.  R is constant along
        // lines of the form s-(b/a)*t = k, and the minimum of R occurs on the
        // line a*s - b*t + d = 0.  This line must intersect both the s-axis
        // and the t-axis because 'a' and 'b' are not zero.  Because of
        // parallelism, the line is also represented by -b*s + c*t - e = 0.
        //
        // The code determines an edge of the domain [0,1]^2 that intersects
        // the minimum line, or if none of the edges intersect, it determines
        // the closest corner to the minimum line.  The conditionals are
        // designed to test first for intersection with the t-axis (s = 0)
        // using -b*s + c*t - e = 0 and then with the s-axis (t = 0) using
        // a*s - b*t + d = 0.

        // When s = 0, solve c*t - e = 0 (t = e/c).
        if (e <= zero)  // t <= 0
        {
            // Now solve a*s - b*t + d = 0 for t = 0 (s = -d/a).
            t = zero;
            nd = -d;
            if (nd <= zero)  // s <= 0
            {
                // region 6
                s = zero;
            }
            else if (nd >= a)  // s >= 1
            {
                // region 8
                s = one;
            }
            else  // 0 < s < 1
            {
                // region 7
                s = nd / a;
            }
        }
        else if (e >= c)  // t >= 1
        {
            // Now solve a*s - b*t + d = 0 for t = 1 (s = (b-d)/a).
            t = one;
            bmd = b - d;
            if (bmd <= zero)  // s <= 0
            {
                // region 4
                s = zero;
            }
            else if (bmd >= a)  // s >= 1
            {
                // region 2
                s = one;
            }
            else  // 0 < s < 1
            {
                // region 3
                s = bmd / a;
            }
        }
        else  // 0 < t < 1
        {
            // The point (0,e/c) is on the line and domain, so we have one
            // point at which R is a minimum.
            s = zero;
            t = e / c;
        }
    }

    /*result.parameter[0] = s;
    result.parameter[1] = t;*/
    QVector3D closest_P;
    QVector3D closest_Q;
    closest_P = P0 + s*P1mP0;
    closest_Q = Q0 + t*Q1mQ0;
    /*result.closest[0] = P0 + s * P1mP0;
    result.closest[1] = Q0 + t * Q1mQ0;*/
    QVector3D closest_distance_vec = closest_Q - closest_P;
    double distance = closest_distance_vec.length();
    return distance;
}

QList<Eigen::Vector3d> WellConstraintProjections::non_inv_solution(Eigen::Matrix3d A, Eigen::Vector3d b)
{
    QList<Eigen::Vector3d> solution_vectors;
    // Compute full pivotal LU decomposition of A
    Eigen::FullPivLU<Eigen::Matrix3d> lu(A);
    Eigen::Vector3d x = A.fullPivLu().solve(b);

    Eigen::MatrixXd nu = lu.kernel();
    Eigen::Vector3d null_space;
    if(nu.cols()>1){
        null_space << nu(0,0), nu(1,0), nu(2,0);
        std::cout << "Null space/kernel of (A-mu I) has more than 1 vector. " << std::endl;
    }
    else null_space = nu;

    Eigen::VectorXd real_roots;
    Eigen::VectorXd complex_roots;
    rpoly_plus_plus::FindPolynomialRootsJenkinsTraub(WellConstraintProjections::non_inv_quad_coeffs(x,null_space),&real_roots,&complex_roots);

    //std::cout << "here are poly roots " << std::endl << real_roots << std::endl << "+ i " << complex_roots << std::endl;


    if(complex_roots(0)==0){
        Eigen::Vector3d s0 = x + real_roots(0)*null_space;
        solution_vectors.append(s0);
    }
    if(complex_roots(1)==0){
        Eigen::Vector3d s1 = x + real_roots(1)*null_space;
        solution_vectors.append(s1);
    }

    return solution_vectors;
}

bool WellConstraintProjections::solution_existence(Eigen::Matrix3d A, Eigen::Vector3d b)
{
    Eigen::Vector3d x = A.fullPivLu().solve(b);
    return ((A*x).isApprox(b));

}



QList<QVector3D> WellConstraintProjections::compute_interwell_vector_4d(QList<Model::Reservoir::Grid::XYZCoordinate> coords, double d)
{
    // First sets up matrices A and b
    arma::mat A = WellConstraintProjections::build_A_4d(coords);
    arma::vec b = WellConstraintProjections::build_b_4d(coords,d);

    // Compute eigenvalues and eigenvectors of A
    arma::mat eigvec;
    arma::vec eigval;
    arma::eig_sym(eigval,eigvec,A);
    arma::mat eigvec_trans = arma::trans(eigvec);

    // TEST PRINT
    std::cout << A(0,0) << " | " << A(0,1) << " | " << A(0,2) << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << A(1,0) << " | " << A(1,1) << " | " << A(1,2) << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << A(2,0) << " | " << A(2,1) << " | " << A(2,2) << std::endl;
    std::cout <<"b = (" << b(0) << ", " << b(1) << ", " << b(2) << ")" << std::endl;
    std::cout << "eigvalues = (" << eigval(0) << ", " << eigval(1) << ", " << eigval(2) << ")" << std::endl;
    // END TEST PRINT


    // Compute coefficients of 6th degree polynomial
    Eigen::VectorXd coeffs = WellConstraintProjections::coeff_vector(eigval,eigvec_trans,b);

    // Compute roots of polynomial
    Eigen::VectorXd realroots(6);
    Eigen::VectorXd comproots(6);
    rpoly_plus_plus::FindPolynomialRootsJenkinsTraub(coeffs,&realroots,&comproots);

    for(int ii=0;ii<6;ii++){
    std::cout <<"root " << ii << " = " << realroots[ii] << " + " << comproots[ii] <<"i" << std::endl;
    }

    for (int ii=0;ii<6;ii++){
        std::cout <<"pol(root i) = " << coeffs[0]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]
                                        + coeffs[1]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]
                                        + coeffs[2]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]
                                        + coeffs[3]*realroots[ii]*realroots[ii]*realroots[ii]
                                        + coeffs[4]*realroots[ii]*realroots[ii]
                                        + coeffs[5]*realroots[ii]
                                        + coeffs[6] << std::endl;
    }

    arma::mat invmatr(3,3);
    invmatr.zeros();

    QList<QVector3D> solution_vectors;

    for (int ii=0;ii<6;ii++){
        if(comproots[ii]==0){
            double cur_root = realroots[ii];
            invmatr(0,0) = 1.00/(eigval(0)-cur_root);
            invmatr(1,1) = 1.00/(eigval(1)-cur_root);
            invmatr(2,2) = 1.00/(eigval(2)-cur_root);
            arma::vec s = eigvec*invmatr*eigvec_trans*b;
            double tolerance = 0.001;
            if(sqrt(s(0)*s(0) + s(1)*s(1) +s(2)*s(2)) < 1+tolerance && sqrt(s(0)*s(0) + s(1)*s(1) +s(2)*s(2))>1-tolerance){
                solution_vectors.append(QVector3D(s(0),s(1),s(2)));
                std::cout <<"(s1,s2,s3) = (" << s(0) << ", " << s(1) << ", " << s(2) << ") length = " << sqrt(s(0)*s(0) + s(1)*s(1) +s(2)*s(2)) << std::endl;
            }
        }
    }
    return solution_vectors;
}

QList<QVector3D> WellConstraintProjections::interwell_projection_4p(QList<QVector3D> coords, double d)
{
    // Return initial points if they already satisfy inter-well constraint
    if(shortest_distance(coords)>=d){return coords;}

    // First sets up matrices A and b
    arma::mat A = WellConstraintProjections::build_A_4p_qvec(coords);
    arma::vec b = WellConstraintProjections::build_b_4p_qvec(coords,d);

    // Compute eigenvalues and eigenvectors of A
    arma::mat eigvec;
    arma::vec eigval;
    arma::eig_sym(eigval,eigvec,A);
    arma::mat eigvec_trans = arma::trans(eigvec);

    // TEST PRINT
    /*std::cout << A(0,0) << " | " << A(0,1) << " | " << A(0,2) << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << A(1,0) << " | " << A(1,1) << " | " << A(1,2) << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << A(2,0) << " | " << A(2,1) << " | " << A(2,2) << std::endl;
    std::cout <<"b = (" << b(0) << ", " << b(1) << ", " << b(2) << ")" << std::endl;
    std::cout << "eigvalues = (" << eigval(0) << ", " << eigval(1) << ", " << eigval(2) << ")" << std::endl;*/
    // END TEST PRINT


    // Compute coefficients of 6th degree polynomial
    Eigen::VectorXd coeffs = WellConstraintProjections::coeff_vector(eigval,eigvec_trans,b);

    // Compute roots of polynomial
    Eigen::VectorXd realroots(6);
    Eigen::VectorXd comproots(6);
    rpoly_plus_plus::FindPolynomialRootsJenkinsTraub(coeffs,&realroots,&comproots);

    /*for(int ii=0;ii<6;ii++){
    std::cout <<"root " << ii << " = " << realroots[ii] << " + " << comproots[ii] <<"i" << std::endl;
    }

    for (int ii=0;ii<6;ii++){
        std::cout <<"pol(root i) = " << coeffs[0]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]
                                        + coeffs[1]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]
                                        + coeffs[2]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]
                                        + coeffs[3]*realroots[ii]*realroots[ii]*realroots[ii]
                                        + coeffs[4]*realroots[ii]*realroots[ii]
                                        + coeffs[5]*realroots[ii]
                                        + coeffs[6] << std::endl;
    }*/

    arma::mat invmatr(3,3);
    invmatr.zeros();

    QList<QVector3D> solution_moved_points;
    QVector3D current_vector;
    double cost = INFINITY;

    for (int ii=0;ii<6;ii++){
        if(comproots[ii]==0){
            double cur_root = realroots[ii];
            invmatr(0,0) = 1.00/(eigval(0)-cur_root);
            invmatr(1,1) = 1.00/(eigval(1)-cur_root);
            invmatr(2,2) = 1.00/(eigval(2)-cur_root);
            arma::vec s = eigvec*invmatr*eigvec_trans*b;
            current_vector = QVector3D(s(0),s(1),s(2));
            double tolerance = 0.001;
            // Check if current vector has length 1 and is better than previous choices
            if(     sqrt(s(0)*s(0) + s(1)*s(1) +s(2)*s(2)) < 1 + tolerance &&
                    sqrt(s(0)*s(0) + s(1)*s(1) +s(2)*s(2)) > 1 - tolerance &&
                    WellIndexCalculator::GeometryFunctions::movement_cost(coords,move_points_4p(coords,d,current_vector))<cost){
                solution_moved_points = WellConstraintProjections::move_points_4p(coords,d,current_vector);
                cost = WellIndexCalculator::GeometryFunctions::movement_cost(coords,move_points_4p(coords,d,current_vector));
            }
        }
    }

    // THE ABOVE WILL NOT WORK IF mu IS AN EIGENVALUE OF A. DO THIS ALSO

    for(int eig_num=0; eig_num<3; eig_num++){
        Eigen::Matrix3d A_eig;
        A_eig << A(0,0)-eigval(eig_num) ,A(0,1),A(0,2),
                A(1,0),A(1,1)-eigval(eig_num) ,A(1,2),
                A(2,0),A(2,1),A(2,2) -eigval(eig_num);
        Eigen::Vector3d b_eig;
        b_eig << b(0), b(1), b(2);

        QList<Eigen::Vector3d> s_list = WellConstraintProjections::non_inv_solution(A_eig,b_eig);

        for (int i=0; i<s_list.length(); i++){
            QVector3D current_vector = QVector3D(s_list.at(i)(0),s_list.at(i)(1),s_list.at(i)(2));
            if( WellIndexCalculator::GeometryFunctions::movement_cost(coords,move_points_4p(coords,d,current_vector))<cost){
                solution_moved_points = WellConstraintProjections::move_points_4p(coords,d,current_vector);
                cost = WellIndexCalculator::GeometryFunctions::movement_cost(coords,move_points_4p(coords,d,current_vector));
            }
        }
    }

    if(cost<INFINITY){std::cout << "Coords have been moved" << std::endl;}


    return solution_moved_points;
}

QList<QVector3D> WellConstraintProjections::compute_interwell_vector_3d(QList<Model::Reservoir::Grid::XYZCoordinate> coords, double d)
{
    // First sets up matrices A and b
    arma::mat A = WellConstraintProjections::build_A_3d(coords);
    arma::vec b = WellConstraintProjections::build_b_3d(coords,d);

    // Compute eigenvalues and eigenvectors of A
    arma::mat eigvec;
    arma::vec eigval;
    arma::eig_sym(eigval,eigvec,A);
    arma::mat eigvec_trans = arma::trans(eigvec);

    // TEST PRINT
    /*
    std::cout << A(0,0) << " | " << A(0,1) << " | " << A(0,2) << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << A(1,0) << " | " << A(1,1) << " | " << A(1,2) << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << A(2,0) << " | " << A(2,1) << " | " << A(2,2) << std::endl;
    std::cout <<"b = (" << b(0) << ", " << b(1) << ", " << b(2) << ")" << std::endl;
    std::cout << "eigvalues = (" << eigval(0) << ", " << eigval(1) << ", " << eigval(2) << ")" << std::endl;
    */
    // END TEST PRINT


    // Compute coefficients of 6th degree polynomial
    Eigen::VectorXd coeffs = WellConstraintProjections::coeff_vector(eigval,eigvec_trans,b);

    // Compute roots of polynomial
    Eigen::VectorXd realroots(6);
    Eigen::VectorXd comproots(6);
    rpoly_plus_plus::FindPolynomialRootsJenkinsTraub(coeffs,&realroots,&comproots);

    for(int ii=0;ii<6;ii++){
    std::cout <<"root " << ii << " = " << realroots[ii] << " + " << comproots[ii] <<"i" << std::endl;
    }

    for (int ii=0;ii<6;ii++){
        std::cout <<"pol(root i) = " << coeffs[0]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]
                                        + coeffs[1]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]
                                        + coeffs[2]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]
                                        + coeffs[3]*realroots[ii]*realroots[ii]*realroots[ii]
                                        + coeffs[4]*realroots[ii]*realroots[ii]
                                        + coeffs[5]*realroots[ii]
                                        + coeffs[6] << std::endl;
    }

    arma::mat invmatr(3,3);
    invmatr.zeros();

    QList<QVector3D> solution_vectors;

    for (int ii=0;ii<6;ii++){
        if(comproots[ii]==0){
            double cur_root = realroots[ii];
            invmatr(0,0) = 1.00/(eigval(0)-cur_root);
            invmatr(1,1) = 1.00/(eigval(1)-cur_root);
            invmatr(2,2) = 1.00/(eigval(2)-cur_root);
            arma::vec s = eigvec*invmatr*eigvec_trans*b;
            if(sqrt(s(0)*s(0) + s(1)*s(1) +s(2)*s(2))<1.001 && sqrt(s(0)*s(0) + s(1)*s(1) +s(2)*s(2))>0.999){
                solution_vectors.append(QVector3D(s(0),s(1),s(2)));
                std::cout <<"(s1,s2,s3) = (" << s(0) << ", " << s(1) << ", " << s(2) << ") length = " << sqrt(s(0)*s(0) + s(1)*s(1) +s(2)*s(2)) << std::endl;
            }
        }
    }
    return solution_vectors;
}

QList<QVector3D> WellConstraintProjections::interwell_projection_3p(QList<QVector3D> coords, double d)
{
    // Return initial points if they already satisfy inter-well constraint
    if(shortest_distance_3p(coords)>=d){return coords;}

    // First sets up matrices A and b
    arma::mat A = WellConstraintProjections::build_A_3p_qvec(coords);
    arma::vec b = WellConstraintProjections::build_b_3p_qvec(coords,d);

    // Compute eigenvalues and eigenvectors of A
    arma::mat eigvec;
    arma::vec eigval;
    arma::eig_sym(eigval,eigvec,A);
    arma::mat eigvec_trans = arma::trans(eigvec);

    // Compute coefficients of 6th degree polynomial
    Eigen::VectorXd coeffs = WellConstraintProjections::coeff_vector(eigval,eigvec_trans,b);

    // Compute roots of polynomial
    Eigen::VectorXd realroots(6);
    Eigen::VectorXd comproots(6);
    rpoly_plus_plus::FindPolynomialRootsJenkinsTraub(coeffs,&realroots,&comproots);

    for(int ii=0;ii<6;ii++){
    std::cout <<"root " << ii << " = " << realroots[ii] << " + " << comproots[ii] <<"i" << std::endl;
    }

    for (int ii=0;ii<6;ii++){
        std::cout <<"pol(root i) = " << coeffs[0]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]
                                        + coeffs[1]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]
                                        + coeffs[2]*realroots[ii]*realroots[ii]*realroots[ii]*realroots[ii]
                                        + coeffs[3]*realroots[ii]*realroots[ii]*realroots[ii]
                                        + coeffs[4]*realroots[ii]*realroots[ii]
                                        + coeffs[5]*realroots[ii]
                                        + coeffs[6] << std::endl;
    }

    arma::mat invmatr(3,3);
    invmatr.zeros();

    QList<QVector3D> solution_moved_points;
    QVector3D current_vector;
    double cost = INFINITY;

    for (int ii=0;ii<6;ii++){
        if(comproots[ii]==0){
            double cur_root = realroots[ii];
            invmatr(0,0) = 1.00/(eigval(0)-cur_root);
            invmatr(1,1) = 1.00/(eigval(1)-cur_root);
            invmatr(2,2) = 1.00/(eigval(2)-cur_root);
            arma::vec s = eigvec*invmatr*eigvec_trans*b;
            current_vector = QVector3D(s(0),s(1),s(2));
            double tolerance = 0.001;
            // Check if current vector has length 1 and is better than previous choices
            if(     sqrt(s(0)*s(0) + s(1)*s(1) +s(2)*s(2)) < 1 + tolerance &&
                    sqrt(s(0)*s(0) + s(1)*s(1) +s(2)*s(2)) > 1 - tolerance &&
                    WellIndexCalculator::GeometryFunctions::movement_cost(coords,move_points_3p(coords,d,current_vector))<cost){
                solution_moved_points = WellConstraintProjections::move_points_3p(coords,d,current_vector);
                cost = WellIndexCalculator::GeometryFunctions::movement_cost(coords,move_points_3p(coords,d,current_vector));
            }
        }
    }
    if(solution_moved_points.length()==0){return coords;}
    return solution_moved_points;
}

QList<QVector3D> WellConstraintProjections::interwell_projection_3p_eigen(QList<QVector3D> coords, double d)
{
    QList<QVector3D> return_list;
    QList<QVector3D> solution_moved_points;
    // Return initial points if they already satisfy inter-well constraint
    if(shortest_distance_3p(coords)>=d){return coords;}

    // First sets up matrices A and b
    arma::mat A_temp = WellConstraintProjections::build_A_3p_qvec(coords);
    arma::vec b_temp = WellConstraintProjections::build_b_3p_qvec(coords,d);

    Eigen::Matrix3d A;
    A << A_temp(0,0),A_temp(0,1),A_temp(0,2),
         A_temp(1,0),A_temp(1,1),A_temp(1,2),
         A_temp(2,0),A_temp(2,1),A_temp(2,2);
    Eigen::Vector3d b;
    b << b_temp(0), b_temp(1), b_temp(2);


    if(WellConstraintProjections::solution_existence(A,b)){
        QList<Eigen::Vector3d> s_list = WellConstraintProjections::non_inv_solution(A,b);
        double movement_cost = INFINITY;
        for (int i=0; i<s_list.length(); i++){
            QVector3D current_vector = QVector3D(s_list.at(i)(0),s_list.at(i)(1),s_list.at(i)(2));
            if( WellIndexCalculator::GeometryFunctions::movement_cost(coords,move_points_3p(coords,d,current_vector))<movement_cost){
                solution_moved_points = WellConstraintProjections::move_points_3p(coords,d,current_vector);
                movement_cost = WellIndexCalculator::GeometryFunctions::movement_cost(coords,move_points_3p(coords,d,current_vector));
            }
        }
    }
    else solution_moved_points = coords;

    return solution_moved_points;
}

QList<QVector3D> WellConstraintProjections::well_distance_projection(QVector3D heel, QVector3D toe, double max, double min, double epsilon)
{
    QList<QVector3D> projected_points;
    QVector3D moved_heel;
    QVector3D moved_toe;
    // Need the vector going from heel to toe to project points
    QVector3D heel_to_toe_vec = toe - heel;
    // Normalize vector to get correct distance
    heel_to_toe_vec.normalize();

    // Distance between heel and toe.
    double d = heel.distanceToPoint(toe);

    // Trivial case
    if(d<=max && d>=min){
        projected_points.append(heel);
        projected_points.append(toe);
    }

    // Distance too long
    else if(d>max){
        double move_distance = 0.5*(d-max+(epsilon/2));
        moved_heel = heel + move_distance*heel_to_toe_vec;
        moved_toe =  toe  - move_distance*heel_to_toe_vec;
        projected_points.append(QVector3D(moved_heel));
        projected_points.append(QVector3D(moved_toe));
    }

    // Distance too short
    else{
        double move_distance = 0.5*(d-min-(epsilon/2));
        moved_heel = heel + move_distance*heel_to_toe_vec;
        moved_toe =  toe  - move_distance*heel_to_toe_vec;
        projected_points.append(QVector3D(moved_heel));
        projected_points.append(QVector3D(moved_toe));
    }

    return projected_points;
}


/* PUTTING ALL REWORKED EIGEN FUNCTIONS BELOW HERE*/

Eigen::Matrix3d WellConstraintProjections::build_A_4p_eigen(QList<Eigen::Vector3d> coords)
{
    Eigen::Vector3d vec1 = coords.at(0);
    Eigen::Vector3d vec2 = coords.at(1);
    Eigen::Vector3d vec3 = coords.at(2);
    Eigen::Vector3d vec4 = coords.at(3);
    Eigen::Vector3d avg_vec = 0.25*(vec1+vec2+vec3+vec4);
    vec1 = vec1 - avg_vec;
    vec2 = vec2 - avg_vec;
    vec3 = vec3 - avg_vec;
    vec4 = vec4 - avg_vec;

    return vec1*vec1.transpose() + vec2*vec2.transpose() + vec3*vec3.transpose() + vec4*vec4.transpose();
}

Eigen::Vector3d WellConstraintProjections::build_b_4p_eigen(QList<Eigen::Vector3d> coords, double d)
{
    Eigen::Vector3d vec1 = coords.at(0);
    Eigen::Vector3d vec2 = coords.at(1);
    Eigen::Vector3d vec3 = coords.at(2);
    Eigen::Vector3d vec4 = coords.at(3);
    Eigen::Vector3d avg_vec = 0.25*(vec1+vec2+vec3+vec4);
    vec1 = vec1 - avg_vec;
    vec2 = vec2 - avg_vec;
    vec3 = vec3 - avg_vec;
    vec4 = vec4 - avg_vec;

    return 0.5*d*(vec1 + vec2 - vec3 - vec4);
}

Eigen::Matrix3d WellConstraintProjections::build_A_3p_eigen(QList<Eigen::Vector3d> coords)
{
    Eigen::Vector3d vec1 = coords.at(0);
    Eigen::Vector3d vec2 = coords.at(1);
    Eigen::Vector3d vec3 = coords.at(2);
    Eigen::Vector3d avg_vec = (1.0/3)*(vec1+vec2+vec3);

    vec1 = vec1 - avg_vec;
    vec2 = vec2 - avg_vec;
    vec3 = vec3 - avg_vec;
    return vec1*vec1.transpose() + vec2*vec2.transpose() + vec3*vec3.transpose();
}

Eigen::Vector3d WellConstraintProjections::build_b_3p_eigen(QList<Eigen::Vector3d> coords, double d)
{
    Eigen::Vector3d vec1 = coords.at(0);
    Eigen::Vector3d vec2 = coords.at(1);
    Eigen::Vector3d vec3 = coords.at(2);
    Eigen::Vector3d avg_vec = (1.0/3)*(vec1+vec2+vec3);
    vec1 = vec1 - avg_vec;
    vec2 = vec2 - avg_vec;
    vec3 = vec3 - avg_vec;

    return (2.0/3)*d*(vec1) -(1.0/3)*d*(vec2 + vec3);
}

Eigen::VectorXd WellConstraintProjections::coeff_vector_eigen(Eigen::Vector3d D, Eigen::Matrix3d Qinv, Eigen::Vector3d b)
{
    double D1 = D(0);
    double D2 = D(1);
    double D3 = D(2);
    double sum_i = WellConstraintProjections::sum_i(D1,D2,D3);
    double sum_ij = WellConstraintProjections::sum_ij(D1,D2,D3);
    double prod_i = WellConstraintProjections::prod_i(D1,D2,D3);
    double Qtb_1 = Qinv.row(0)*b*(Qinv.row(0)*b);
    double Qtb_2 = Qinv.row(1)*b*(Qinv.row(1)*b);
    double Qtb_3 = Qinv.row(2)*b*(Qinv.row(2)*b);

    Eigen::VectorXd lambda(7);
    lambda(0) = 1;
    lambda(1) = -2*sum_i;
    lambda(2) = 2*sum_ij + sum_i*sum_i - (Qtb_1+Qtb_2+Qtb_3);
    lambda(3) = -2*prod_i - 2*sum_i*sum_ij - Qtb_1*(-2*D2 -2*D3)
                                           - Qtb_2*(-2*D3 -2*D1)
                                           - Qtb_3*(-2*D1 -2*D2);
    lambda(4) = 2*sum_i*prod_i + sum_ij*sum_ij - Qtb_1*(D2*D2 +D3*D3 + 4*D2*D3)
                                               - Qtb_2*(D3*D3 +D1*D1 + 4*D3*D1)
                                               - Qtb_3*(D1*D1 +D2*D2 + 4*D1*D2);
    lambda(5) = -2*sum_ij*prod_i - Qtb_1*(-2*D2*D3*D3 -2*D3*D2*D2)
                                 - Qtb_2*(-2*D3*D1*D1 -2*D1*D3*D3)
                                 - Qtb_3*(-2*D1*D2*D2 -2*D2*D1*D1);
    lambda(6) = prod_i*prod_i - Qtb_1*(D2*D2*D3*D3)
                              - Qtb_2*(D3*D3*D1*D1)
                              - Qtb_3*(D1*D1*D2*D2);

    return lambda;
}

double WellConstraintProjections::movement_cost_eig(QList<Eigen::Vector3d> old_coords, QList<Eigen::Vector3d> new_coords)
{
    double n_of_points = old_coords.length();
    if(new_coords.length()!=n_of_points){throw geometryfunctions::MovementCost_VectorsNotSameLength("Lists of points are not the same length");}
    double cost_squares;
    for (int ii=0; ii<n_of_points; ii++){
        cost_squares += (old_coords.at(ii)-new_coords.at(ii)).squaredNorm();
    }

    return cost_squares;
}

QList<Eigen::Vector3d> WellConstraintProjections::move_points_4p_eigen(QList<Eigen::Vector3d> coords, double d, Eigen::Vector3d s)
{
    // Normalize s in case it is not of unit length
    s.normalize();
    Eigen::Vector3d avg_point = 0.25*(coords.at(0) + coords.at(1) + coords.at(2) + coords.at(3));
    Eigen::Vector3d top_plane_point = avg_point + (d/2)*(s);
    Eigen::Vector3d bot_plane_point = avg_point - (d/2)*(s);

    Eigen::Vector3d x0moved = WellConstraintProjections::project_point_to_plane_eigen(coords.at(0),s,top_plane_point);
    Eigen::Vector3d x1moved = WellConstraintProjections::project_point_to_plane_eigen(coords.at(1),s,top_plane_point);
    Eigen::Vector3d x2moved = WellConstraintProjections::project_point_to_plane_eigen(coords.at(2),s,bot_plane_point);
    Eigen::Vector3d x3moved = WellConstraintProjections::project_point_to_plane_eigen(coords.at(3),s,bot_plane_point);

    QList<Eigen::Vector3d> moved_coords;
    moved_coords.append(x0moved);
    moved_coords.append(x1moved);
    moved_coords.append(x2moved);
    moved_coords.append(x3moved);
    return moved_coords;
}

QList<Eigen::Vector3d> WellConstraintProjections::move_points_3p_eigen(QList<Eigen::Vector3d> coords, double d, Eigen::Vector3d s)
{
    // Normalize s in case it is not of unit length
    s.normalize();
    Eigen::Vector3d avg_point = (1.0/3)*(coords.at(0) + coords.at(1) + coords.at(2));
    Eigen::Vector3d top_plane_point = avg_point + (2.0*d/3)*(s);
    Eigen::Vector3d bot_plane_point = avg_point - (1.0*d/3)*(s);

    Eigen::Vector3d x0moved = WellConstraintProjections::project_point_to_plane_eigen(coords.at(0),s,top_plane_point);
    Eigen::Vector3d x1moved = WellConstraintProjections::project_point_to_plane_eigen(coords.at(1),s,bot_plane_point);
    Eigen::Vector3d x2moved = WellConstraintProjections::project_point_to_plane_eigen(coords.at(2),s,bot_plane_point);


    QList<Eigen::Vector3d> moved_coords;
    moved_coords.append(x0moved);
    moved_coords.append(x1moved);
    moved_coords.append(x2moved);
    return moved_coords;
}

Eigen::Vector3d WellConstraintProjections::project_point_to_plane_eigen(Eigen::Vector3d point, Eigen::Vector3d normal_vector, Eigen::Vector3d plane_point)
{
    Eigen::Vector3d proj_point = point - normal_vector*( (point-plane_point).transpose()*normal_vector );//QVector3D::dotProduct(*point-*plane_point,*normal_vector));
    return proj_point;

}

QList<Eigen::Vector3d> WellConstraintProjections::kkt_eq_solutions_eigen(Eigen::Matrix3d A, Eigen::Vector3d b)
{

    QList<Eigen::Vector3d> candidate_solutions;

    /* First assume that A-\mu I has an inverse.
     * We can find the inverse of it and solve
     * a sixth degree equation for \mu.
     */
    A = WellIndexCalculator::WellConstraintProjections::rm_entries_eps_matrix(A,10e-12);
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> A_es(A);

    // Need to remove eigenvalues which are approx 0
    Eigen::Vector3d eigenvalues = WellConstraintProjections::rm_entries_eps(A_es.eigenvalues(),10e-12);
    /*std::cout << "eigvalues" << std::endl << A_es.eigenvalues() << std::endl;
    std::cout << "eigvalues small removed" << std::endl << eigenvalues << std::endl;
    std::cout << "qinvb" << std::endl << A_es.eigenvectors().inverse()*b << std::endl;*/
    // Compute coefficients of 6th degree polynomial
    Eigen::VectorXd coeffs = WellConstraintProjections::coeff_vector_eigen(eigenvalues, A_es.eigenvectors().inverse(), b);

    /* There is an issue where coefficients should be zero but are not
     * but because of numerical issues these need to be handled manually.
     * Simply set all whose fabs(x)<10-e12 to zero.
     */
    coeffs = WellConstraintProjections::rm_entries_eps_coeffs(coeffs,10e-12);


    // Compute roots of polynomial
    Eigen::VectorXd realroots(6);
    Eigen::VectorXd comproots(6);
    rpoly_plus_plus::FindPolynomialRootsJenkinsTraub(coeffs,&realroots,&comproots);

    //std::cout << "polynomial coeffs = " << std::endl << coeffs << std::endl;

    //Eigen::Matrix3d invmatr = Eigen::Matrix3d::Zero();

    for (int ii=0;ii<6;ii++){

        // Root may not be complex or an eigenvalue of A
        if(comproots[ii]==0 && eigenvalues[0]!=realroots[ii] &&
                eigenvalues[1]!=realroots[ii] && eigenvalues[2]!=realroots[ii]){

            // We have found a valid root. Get vector s.
            double cur_root = realroots[ii];
            Eigen::Vector3d cur_root_vec;
            cur_root_vec << cur_root, cur_root, cur_root;
            Eigen::Matrix3d invmatr = (eigenvalues-cur_root_vec).asDiagonal();

            //invmatr(0,0) = 1.00/(A_es.eigenvalues()[0]-cur_root);
            //invmatr(1,1) = 1.00/(A_es.eigenvalues()[1]-cur_root);
            //invmatr(2,2) = 1.00/(A_es.eigenvalues()[2]-cur_root);
            Eigen::Vector3d s = A_es.eigenvectors()*invmatr.inverse()*A_es.eigenvectors().inverse()*b;
            //QVector3D* current_s = new QVector3D(s(0),s(1),s(2));

            // No need to check that current vector has length 1 +- tolerance
            // if () current_s->length() < 1 + tolerance && current_s->length() > 1 - tolerance){
            candidate_solutions.append(s);
            //std::cout << candidate_solutions.length() <<" solution found. mu not eigenvalue of A. s= " << std::endl << s << std::endl;

        }
    }

    /* Now for the second part assume that A-\mu I is not
     * invertible, i.e. \mu is an eigenvalue of A. Then
     * we either have an infinite amount of solutions of
     * (A-\mu I)s = b. Require s have length 1 to find
     * at most two solutions as long as all points are
     * not on the same line.
     */

    // Loop through all 3 eigenvalues of A
    for(int i=0; i<3; i++){

        QList<Eigen::Vector3d> eigenvalue_solutions;

        // Create linear system (A-\my I)s = b
        Eigen::Matrix3d A_eig = A- eigenvalues[i]*Eigen::Matrix3d::Identity();

        /*
        A_eig << A(0,0)-eigval(i), A(0,1)          , A(0,2),
                 A(1,0)          , A(1,1)-eigval(i), A(1,2),
                 A(2,0)          , A(2,1)           ,A(2,2)-eigval(i);
        */
        Eigen::Vector3d b_eig = b;
        // Check for existence of solution
        //std::cout << "eigenvalue number "<< i << " = " << eigenvalues[i] << std::endl;
        if(WellConstraintProjections::solution_existence(A_eig,b_eig)){
            //std::cout << "Indeed solvable" << std::endl;
            eigenvalue_solutions = WellConstraintProjections::non_inv_solution(A_eig, b_eig);
        }

        // If any solutions, add them to solution_vectors
        for(int jj = 0; jj < eigenvalue_solutions.length(); jj++){
            candidate_solutions.append(eigenvalue_solutions.at(jj));
            //std::cout << candidate_solutions.length() <<" solution found. mu eigenvalue of A. solution is" << std::endl << eigenvalue_solutions.at(jj) << std::endl;
        }
    }

    return candidate_solutions;
}



}
