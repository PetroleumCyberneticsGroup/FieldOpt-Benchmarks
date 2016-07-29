#include "geometryfunctions.h"
#include "geometryfunctions_exceptions.h"
#include <cmath>

namespace WellIndexCalculator {

double GeometryFunctions::distance_coordinates(Model::Reservoir::Grid::XYZCoordinate start_point, Model::Reservoir::Grid::XYZCoordinate end_point)
{
    // Calculates the euclidian distance (in 3 dimensions) between two points (XYZCoordinates).
    double distance;
    distance = sqrt(   (end_point.x()-start_point.x())*(end_point.x()-start_point.x())
                 + (end_point.y()-start_point.y())*(end_point.y()-start_point.y())
                 + (end_point.z()-start_point.z())*(end_point.z()-start_point.z())  );

    return distance;
}
Model::Reservoir::Grid::XYZCoordinate GeometryFunctions::move3dpoint(Model::Reservoir::Grid::XYZCoordinate input_point)
{
    Model::Reservoir::Grid::XYZCoordinate movedPoint = Model::Reservoir::Grid::XYZCoordinate(input_point.x()+1,input_point.y()+1,input_point.z()+1);
    return movedPoint;
}


Model::Reservoir::Grid::XYZCoordinate GeometryFunctions::line_intersects_plane(GeometryClasses::SquarePlane plane, GeometryClasses::Line line)
{
    // Assumes that the 4 points of Plane all lie in the same (2 dimensional) plane
    // Determine the normal vector of Plane by computing two vectors spanning it.

    Model::Reservoir::Grid::XYZCoordinate spanning_vec1 = Model::Reservoir::Grid::XYZCoordinate(plane.c2().x() - plane.c1().x(),plane.c2().y() - plane.c1().y(),plane.c2().z() - plane.c1().z() );
    Model::Reservoir::Grid::XYZCoordinate spanning_vec2 = Model::Reservoir::Grid::XYZCoordinate(plane.c3().x() - plane.c1().x(),plane.c3().y() - plane.c1().y(),plane.c3().z() - plane.c1().z() );

    // The cross product of the two spanning vectors is orthogonal to the plane.
    Model::Reservoir::Grid::XYZCoordinate normal_vector =  Model::Reservoir::Grid::XYZCoordinate(
                (spanning_vec1.y())*(spanning_vec2.z()) - (spanning_vec1.z())*(spanning_vec2.y())   ,
                (spanning_vec1.z())*(spanning_vec2.x()) - (spanning_vec1.x())*(spanning_vec2.z())   ,
                (spanning_vec1.x())*(spanning_vec2.y()) - (spanning_vec1.y())*(spanning_vec2.x())   );

    Model::Reservoir::Grid::XYZCoordinate line_vector = Model::Reservoir::Grid::XYZCoordinate(line.p1().x() - line.p0().x(), line.p1().y() - line.p0().y(), line.p1().z() - line.p0().z());

    // Check if line segment is parallell to plane. If true, sdhould throw exception.
    if( (line_vector.x())*(normal_vector.x()) + (line_vector.y())*(normal_vector.y()) + (line_vector.z())*(normal_vector.z()) == 0  ){
        throw geometryfunctions::LineIntersectsPlane_ParallelException("Plane and line are parallell");
    };


    Model::Reservoir::Grid::XYZCoordinate line_plane_vector = Model::Reservoir::Grid::XYZCoordinate(plane.c1().x() - line.p0().x(), plane.c1().y() - line.p0().y(), plane.c1().z() - line.p0().z());
    double s, denom, numer;

    numer = (normal_vector.x())*(line_plane_vector.x()) + (normal_vector.y())*(line_plane_vector.y()) + (normal_vector.z())*(line_plane_vector.z());
    denom = (normal_vector.x())*(line_vector.x()) + (normal_vector.y())*(line_vector.y()) + (normal_vector.z())*(line_vector.z());
    s = numer/denom; // Only Inf if line is parallel to plane which we checked further up

    // Check if point of intersection is inside the two points of the line segment.
    if (s<0 || s>1) throw geometryfunctions::LineIntersectsPlane_OutsideLineSegmentException("Point of intersection on line but outside line segment");


    Model::Reservoir::Grid::XYZCoordinate intersecting_point = Model::Reservoir::Grid::XYZCoordinate(line.p0().x()+ s*(line_vector.x()), line.p0().y() + s*(line_vector.y()), line.p0().z()+ s*(line_vector.z()));
    return intersecting_point;
}

Model::Reservoir::Grid::XYZCoordinate GeometryFunctions::line_intersects_plane_vectorized(GeometryClasses::SquarePlane plane, GeometryClasses::Line line){

    // Assumes that the 4 points of Plane all lie in the same (2 dimensional) plane
    // Determine the normal vector of Plane by computing two vectors spanning it.

    QVector3D span_vector0 = QVector3D(plane.c2().x() - plane.c1().x(),plane.c2().y() - plane.c1().y(),plane.c2().z() - plane.c1().z());
    QVector3D span_vector1 = QVector3D(plane.c3().x() - plane.c1().x(),plane.c3().y() - plane.c1().y(),plane.c3().z() - plane.c1().z());
    QVector3D normal_vec = QVector3D(QVector3D::crossProduct(span_vector0,span_vector1));

    QVector3D line_vec = QVector3D(line.p1().x() - line.p0().x(), line.p1().y() - line.p0().y(), line.p1().z() - line.p0().z());

    // Throw exception if line segment is parallell to plane. (i.e. no single point of intersection)
    if(QVector3D::dotProduct(normal_vec,line_vec)==0){
        throw geometryfunctions::LineIntersectsPlane_ParallelException("Plane and line are parallell");
    }

    QVector3D line_plane_vector = QVector3D(plane.c1().x() - line.p0().x(), plane.c1().y() - line.p0().y(), plane.c1().z() - line.p0().z());

    /* s is a variable for the parametrized line defined by the 2 points in line.
     * Inputting a s such that s>=0 or s<=1 will give a point on the line between the 2 points in line.*/
    double s;
    s =( QVector3D::dotProduct(normal_vec,line_plane_vector) ) / ( QVector3D::dotProduct(normal_vec,line_vec) );

    // Check if point of intersection is between (and not outside) the two points of the line segment.
    if (s<0 || s>1) throw geometryfunctions::LineIntersectsPlane_OutsideLineSegmentException("Point of intersection on line but outside line segment");

    // Use the found s in parametrizaton to return intersection point.
    Model::Reservoir::Grid::XYZCoordinate intersection_point = Model::Reservoir::Grid::XYZCoordinate(line.p0().x()+ s*(line_vec.x()), line.p0().y() + s*(line_vec.y()), line.p0().z()+ s*(line_vec.z()));

    return intersection_point;
}

QVector3D GeometryFunctions::line_plane_intersection(QVector3D p0, QVector3D p1, QVector3D normal_vector, QVector3D point_in_plane){

    QVector3D line_vector = QVector3D(p1.x() - p0.x(), p1.y() - p0.y(), p1.z() - p0.z());

    /* Some numerical issues when the line_vector (vector between p0 and p1)
     * is much longer (or shorter) than the normal vector. Normalize both
     * to fix the issue. Resultins parameter s further down should now
     * be more numerically stable.
     */
    line_vector.normalize();
    normal_vector.normalize();

    QVector3D w = QVector3D(p0.x() - point_in_plane.x(), p0.y() - point_in_plane.y(),p0.z() - point_in_plane.z());

    /* s is a variable for the parametrized line defined by the 2 points in line.
     *Inputting a s such that s>=0 or s<=1 will give a point on the line between the 2 points in line.
     */
    double s;
    s =( QVector3D::dotProduct(normal_vector,-w) ) / ( QVector3D::dotProduct(normal_vector,line_vector) );

    // Use the found s in parametrizaton to return intersection point.
    QVector3D intersection_point = QVector3D(p0.x() + s*(line_vector.x()), p0.y() + s*(line_vector.y()), p0.z() + s*(line_vector.z()));

    return intersection_point;
}

QVector3D GeometryFunctions::normal_vector_XYZ(Model::Reservoir::Grid::XYZCoordinate p0, Model::Reservoir::Grid::XYZCoordinate p1, Model::Reservoir::Grid::XYZCoordinate p2)
{
    QVector3D p0vec = GeometryFunctions::XYZ_to_qvec(p0);
    QVector3D p1vec = GeometryFunctions::XYZ_to_qvec(p1);
    QVector3D p2vec = GeometryFunctions::XYZ_to_qvec(p2);
    // Take the cross product of the two vectors as spanned by the three input points
    QVector3D normal_vector = QVector3D::crossProduct(p2vec - p0vec, p1vec - p0vec);
    // We leave the vector not normalized
    return normal_vector;
}

QVector3D GeometryFunctions::normal_vector(QVector3D p0, QVector3D p1, QVector3D p2)
{
    QVector3D normal_vector = QVector3D::crossProduct(p2 - p0,p1 - p0);
    QVector3D normal_vector_ptr = QVector3D(normal_vector.x(),normal_vector.y(),normal_vector.z());
    normal_vector_ptr.normalize();
    return normal_vector_ptr;
}

bool GeometryFunctions::point_on_same_side(QVector3D point, QVector3D plane_point, QVector3D normal_vector, double slack)
{
    /* The dot product helps us determine if the angle between the two
     * vectors is below (positive answer), at (zero answer) or above
     * (negative answer) 90 degrees. Essentially telling us which side
     * of a plane the point is
     */
    double dot_product = QVector3D::dotProduct(point-plane_point,normal_vector);
    if(dot_product<0.0-slack){return false;}
    else{return true;}
}

QPair<QList<int>, QList<QVector3D > > GeometryFunctions::cells_intersected(QVector3D start_point, QVector3D end_point, Model::Reservoir::Grid::Grid *grid)
{
    // Lists which will contain intersected block indeces and intersection points.
    QList<int> cell_global_index;
    QList<QVector3D> entry_points;

    /* Find first and last cell blocks intersected and their indeces.
     * Add first cell and first point to lists.
     */
    Model::Reservoir::Grid::Cell last_cell = GeometryFunctions::get_cell_enveloping_point(grid,end_point);
    Model::Reservoir::Grid::Cell first_cell = GeometryFunctions::get_cell_enveloping_point(grid,start_point);

    int last_cell_index  = last_cell.global_index();
    int first_cell_index = first_cell.global_index();
    cell_global_index.append(first_cell_index);
    entry_points.append(start_point);

    /* If first and last block are the same then this block is
     * the only one intercepted. Return current cell and start point + end point.
     */
    if( last_cell_index == first_cell_index){
        entry_points.append(end_point);
        QPair<QList<int>,QList<QVector3D>> early_pair;
        early_pair.first = cell_global_index;
        early_pair.second = entry_points;
        return early_pair;
    }


    QVector3D exit_point = find_exit_point(first_cell,start_point,end_point,start_point);
    // Make sure we follow line in the correct direction. (i.e. dot product positive)
    if( QVector3D::dotProduct(end_point - start_point, exit_point - start_point) <= 0 ){
        std::cout << "wrong direction, try other" << std::endl;
        std::cout << "exit_point = " << exit_point.x() << " " << exit_point.y() << " " << exit_point.z() << std::endl;
        exit_point = find_exit_point(first_cell, start_point, end_point, exit_point);
    }
    double epsilon = 0.01/(exit_point.distanceToPoint(end_point));
    QVector3D move_exit_epsilon = QVector3D(exit_point*(1-epsilon) + end_point * epsilon);

    Model::Reservoir::Grid::Cell current_cell = GeometryFunctions::get_cell_enveloping_point(grid,move_exit_epsilon);
    double epsilon_temp = epsilon;
    while(current_cell.global_index() == first_cell_index){
        epsilon_temp = 10*epsilon_temp;
        QVector3D move_exit_epsilon = QVector3D(exit_point * (1 - epsilon_temp) + end_point * epsilon_temp);
        current_cell = GeometryFunctions::get_cell_enveloping_point(grid,move_exit_epsilon);
    }

     while(current_cell.global_index() != last_cell_index){

         // Add current cell and previous exit point to lists
         cell_global_index.append(current_cell.global_index());
         entry_points.append(exit_point);

         // Find other exit point.
         exit_point = GeometryFunctions::find_exit_point(current_cell,exit_point,end_point,exit_point);

         // DO SOME CHECK IF EXIT POINT IS THE SAME AS END_POINT: UNLIKELY IN PRACTICE
         if(exit_point == end_point){
             current_cell = last_cell;
         }
         // Move slightly along line to enter the new cell and find cell by using GetCellEnvelopingPoint function.
         else{
             double epsilon = 0.01 / (exit_point.distanceToPoint(end_point));
             QVector3D move_exit_epsilon = QVector3D(exit_point * (1-epsilon) + end_point * epsilon);
             current_cell = GeometryFunctions::get_cell_enveloping_point(grid, move_exit_epsilon);
         }

    }
    cell_global_index.append(last_cell_index);
    entry_points.append(exit_point);
    entry_points.append(end_point);

    /* Collect global indeces of intersected cells and the
     * endpoints of the line segment inside each cell in a
     * QPair type to return them both
     */
    QPair<QList<int>,QList<QVector3D>> pair;
    pair.first = cell_global_index;
    pair.second = entry_points;
    return pair;

}

QList<QList<QVector3D>> GeometryFunctions::cell_planes_coords(QList<Model::Reservoir::Grid::XYZCoordinate> corners)
{
    QList<QList<int>> points;
    QList<int> p0;
    QList<int> p1;
    QList<int> p2;
    QList<int> p3;
    QList<int> p4;
    QList<int> p5;
    //First face

    p0.append(0);
    p0.append(2);
    p0.append(1);
    points.append(p0);
    //Second face
    p1.append(4);
    p1.append(5);
    p1.append(6);
    points.append(p1);
    //third face
    p2.append(0);
    p2.append(4);
    p2.append(2);
    points.append(p2);
    //fourth face
    p3.append(1);
    p3.append(3);
    p3.append(5);
    points.append(p3);
    //fifth face
    p4.append(0);
    p4.append(1);
    p4.append(4);
    points.append(p4);
    //Sixth face
    p5.append(2);
    p5.append(6);
    p5.append(3);
    points.append(p5);

    /* Fill 2D QList array with 3 corner coordinates for each of the 6 faces
     * Corners have been chosen in such a way that normal_vector() function
     * returns a vector that points in towards the centre of the block.
     */
    QList<QList<QVector3D>> face_corner_coords;
    for(int ii=0; ii<6; ii++){
        QList<QVector3D> currentSideCorners;
        currentSideCorners.append( GeometryFunctions::XYZ_to_qvec( corners.at(points.at(ii).at(0)) ) );
        currentSideCorners.append( GeometryFunctions::XYZ_to_qvec( corners.at(points.at(ii).at(1)) ) );
        currentSideCorners.append( GeometryFunctions::XYZ_to_qvec( corners.at(points.at(ii).at(2)) ) );
        face_corner_coords.append(currentSideCorners);

    }

    return face_corner_coords;
}

QVector3D GeometryFunctions::find_exit_point(Model::Reservoir::Grid::Cell cell, QVector3D entry_point, QVector3D end_point, QVector3D exception_point)
{
    /* takes an entry point as input and an end_point
     * which just defines the line of the well. Find
     * the two points which intersect the block faces
     * and choose the one of them which is not the entry
     * point. This will be the exit point.
     */

    QVector3D line = QVector3D(end_point - entry_point);

    // First find normal vectors of all faces of block/cell.
    QList<QList<QVector3D>> face_corner_coords = GeometryFunctions::cell_planes_coords(cell.corners());
    QList<QVector3D> normal_vectors;
    for( int ii=0; ii<6; ii++){

        QVector3D cur_normal_vector = GeometryFunctions::normal_vector(face_corner_coords.at(ii).at(0),
                                                                        face_corner_coords.at(ii).at(1),
                                                                        face_corner_coords.at(ii).at(2));
        normal_vectors.append(cur_normal_vector);
    }

    /* For loop through all faces untill we find a face that
     * intersects with line on face of the block and not just
     * the extension of the face to a plane
     */
    for(int face_number = 0; face_number<6; face_number++){
        // Normal vector
        QVector3D cur_normal_vector = normal_vectors[face_number];
        QVector3D cur_face_point = face_corner_coords.at(face_number).at(0);
        /* If the dot product of the line vector and the face normal vector is
         * zero then the line is paralell to the face and won't intersect it
         * unless it lies in the same plane, which in any case won't be the
         * exit point.
         */
        //std::cout << "face number " << face_number << std::endl;

        if(!(QVector3D::dotProduct(cur_normal_vector, line)==0)) {
            //std::cout << "not parallel to face " << face_number << std::endl;
            // Finds the intersection point of line and the current face
            QVector3D intersect_point = GeometryFunctions::line_plane_intersection(entry_point,end_point,cur_normal_vector,cur_face_point);
            //std::cout << "current intesect_point = " << intersect_point->x() << "," << intersect_point->y() << "," << intersect_point->z() << std::endl;


            /* Loop through all faces and check that intersection point is on the correct side of all of them.
             * i.e. the same direction as the normal vector of each face
             */
            bool feasible_point = true;
            for( int ii=0; ii<6; ii++){
                if(! GeometryFunctions::point_on_same_side(intersect_point, face_corner_coords.at(ii).at(0), normal_vectors[ii],10e-6) ){
                    feasible_point = false;
                }
            }

            // If point is feasible(i.e. on/inside cell), not identical to given entry point, and going in correct direction
            if (feasible_point && intersect_point.distanceToPoint(exception_point) > 10-10
                    && QVector3D::dotProduct(end_point - entry_point, end_point - intersect_point) >= 0){
                return intersect_point;
            }

        }

    }
    // If all fails, the line intersects the cell in a single point(corner or edge) -> return entry_point
    return entry_point;
}


// Orthogonal projection of line (i.e. 2 points) onto a plane.
GeometryClasses::Line GeometryFunctions::project_line_to_plane(GeometryClasses::Line line, GeometryClasses::SquarePlane plane)
{

    /* Convert needed points to QVector3D. Endpoints of line segment q0,q1,
     * and one (doesnt matter which one) point, p, from plane */
    QVector3D q0 = QVector3D(line.p0().x(),line.p0().y(),line.p0().z());
    QVector3D q1 = QVector3D(line.p1().x(),line.p1().y(),line.p1().z());
    QVector3D p  = QVector3D(plane.c1().x(),plane.c1().y(),plane.c1().z());


    /* Assumes that the 4 points of plane all lie in the same (2 dimensional) plane
       Determine the normal vector of plane by computing cross product of two vectors spanning it. */
    QVector3D span_vector0 = QVector3D(plane.c2().x() - plane.c1().x(),plane.c2().y() - plane.c1().y(),plane.c2().z() - plane.c1().z());
    QVector3D span_vector1 = QVector3D(plane.c3().x() - plane.c1().x(),plane.c3().y() - plane.c1().y(),plane.c3().z() - plane.c1().z());
    QVector3D orth_vec = QVector3D(QVector3D::crossProduct(span_vector0, span_vector1));

    // Normalize the orthogonal vector.
    orth_vec.normalize();

    /* Project point down on plane as given by:
     * http://stackoverflow.com/questions/8942950/how-do-i-find-the-orthogonal-projection-of-a-point-onto-a-plane */
    QVector3D proj_p0 = q0 - QVector3D::dotProduct(q0 - p, orth_vec) * (orth_vec);
    QVector3D proj_p1 = q1 - QVector3D::dotProduct(q1 - p, orth_vec) * (orth_vec);

    // Convert projected points back to XYZCoordinates and then return them as Line
    Model::Reservoir::Grid::XYZCoordinate returnpoint0 = Model::Reservoir::Grid::XYZCoordinate(proj_p0.x(),proj_p0.y(),proj_p0.z());
    Model::Reservoir::Grid::XYZCoordinate returnpoint1 = Model::Reservoir::Grid::XYZCoordinate(proj_p1.x(),proj_p1.y(),proj_p1.z());
    GeometryClasses::Line returnline = GeometryClasses::Line(returnpoint0,returnpoint1);


    return returnline;
}

QVector3D GeometryFunctions::project_point_to_plane(QVector3D point, QVector3D normal_vector, QVector3D plane_point)
{
    QVector3D proj_point = point - normal_vector * (QVector3D::dotProduct(point-plane_point, normal_vector));
    QVector3D ptr_proj_point = QVector3D(proj_point);
    return ptr_proj_point;
}

QVector3D GeometryFunctions::project_v1_on_v2(QVector3D v1, QVector3D v2)
{
    QVector3D proj_v = v2 * (QVector3D::dotProduct(v2, v1)/(QVector3D::dotProduct(v2, v2)) );
    QVector3D ptr_proj_v = QVector3D(proj_v);
    return ptr_proj_v;
}

QVector3D GeometryFunctions::XYZ_to_qvec(Model::Reservoir::Grid::XYZCoordinate coor)
{
    QVector3D vec = QVector3D(coor.x(), coor.y(), coor.z());
    return vec;
}

Model::Reservoir::Grid::XYZCoordinate GeometryFunctions::qvec_to_XYZ(QVector3D vec)
{
    QVector3D vector = vec;
    Model::Reservoir::Grid::XYZCoordinate xyz = Model::Reservoir::Grid::XYZCoordinate(vector.x(),vector.y(),vector.z());
    return xyz;
}

QVector3D GeometryFunctions::XYZpoints_to_qvector(Model::Reservoir::Grid::XYZCoordinate p1, Model::Reservoir::Grid::XYZCoordinate p2)
{
    QVector3D vector = QVector3D((p2.x() ) -( p1.x()), (p2.y() ) - (p1.y()), (p2.z()) - (p1.z()));
    return vector;
}

double GeometryFunctions::vertical_well_index_cell(Model::Reservoir::Grid::Cell cell, double kx, double ky, double wellbore_radius)
{
    /* corner points of Cell(s) are always listen in the same order and orientation. (see
     * Model::Reservoir::Grid::Cell for illustration as it is included in the code.
     */

    /* Assumption: The block is fairly regular, i.e. corners are right angles.
     Determine the 3(orthogonal, or very close to orth.) vectors to project line onto.

     Corners 4&5, 4&6 and 4&0 span the cell from the front bottom left corner. */

    QList<Model::Reservoir::Grid::XYZCoordinate> corners = cell.corners();
    QVector3D xvec = WellIndexCalculator::GeometryFunctions::XYZpoints_to_qvector(corners[4],corners[5]);
    QVector3D yvec = WellIndexCalculator::GeometryFunctions::XYZpoints_to_qvector(corners[4],corners[6]);
    QVector3D zvec = WellIndexCalculator::GeometryFunctions::XYZpoints_to_qvector(corners[4],corners[0]);

    // Finds the dimensional sizes (i.e. length in each direction) of the cell block
    double dx = xvec.length();
    double dy = yvec.length();
    double dz = zvec.length();

    double well_index_z = (GeometryFunctions::dir_well_index(dz,dx,dy,kx,ky,wellbore_radius));
    return well_index_z;
}

double GeometryFunctions::well_index_cell(QList<GeometryClasses::Line> lines, Model::Reservoir::Grid::Cell cell, double wellbore_radius)
{
    /* corner points of Cell(s) are always listen in the same order and orientation. (see
     * Model::Reservoir::Grid::Cell for illustration as it is included in the code.
     */

    /* Assumption: The block is fairly regular, i.e. corners are right angles.
     Determine the 3(orthogonal, or very close to orth.) vectors to project line onto.

     Corners 4&5, 4&6 and 4&0 span the cell from the front bottom left corner. */

    QList<Model::Reservoir::Grid::XYZCoordinate> corners = cell.corners();

    QVector3D xvec = WellIndexCalculator::GeometryFunctions::XYZpoints_to_qvector(corners[4],corners[5]);
    QVector3D yvec = WellIndexCalculator::GeometryFunctions::XYZpoints_to_qvector(corners[4],corners[6]);
    QVector3D zvec = WellIndexCalculator::GeometryFunctions::XYZpoints_to_qvector(corners[4],corners[0]);

    // Finds the dimensional sizes (i.e. length in each direction) of the cell block
    double dx = xvec.length();
    double dy = yvec.length();
    double dz = zvec.length();
    // Get directional permeabilities
    double kx = cell.permx();
    double ky = cell.permy();
    double kz = cell.permz();

    double Lx=0;
    double Ly=0;
    double Lz=0;
    // Need to add projections of all segments, each line is one segment.
    for (int i = 0; i < lines.size(); ++i) {
        // Current segment
        GeometryClasses::Line line = lines.at(i);
        // Compute vector from segment
        QVector3D vec = GeometryFunctions::XYZpoints_to_qvector(line.p0(),line.p1());
        /* Proejcts segment vector to directional spanning vectors and determines the length.
         * of the projections. Note that we only only care about the length of the projection,
         * not the spatial position. Also adds the lengths of previous segments in case there
         * is more than one segment within the well.
         */
        Lx = Lx + GeometryFunctions::project_v1_on_v2(vec,xvec).length();
        Ly = Ly + GeometryFunctions::project_v1_on_v2(vec,yvec).length();
        Lz = Lz + GeometryFunctions::project_v1_on_v2(vec,zvec).length();
    }

    // Compute Well Index from formula provided by Shu
    double well_index_x = (GeometryFunctions::dir_well_index(Lx,dy,dz,ky,kz,wellbore_radius));
    double well_index_y = (GeometryFunctions::dir_well_index(Ly,dx,dz,kx,kz,wellbore_radius));
    double well_index_z = (GeometryFunctions::dir_well_index(Lz,dx,dy,kx,ky,wellbore_radius));
    return sqrt(well_index_x*well_index_x + well_index_y*well_index_y + well_index_z*well_index_z);
}

double GeometryFunctions::well_index_cell_qvector(Model::Reservoir::Grid::Cell cell, QList<QVector3D> start_points, QList<QVector3D> end_points, double wellbore_radius)
{
    /* corner points of Cell(s) are always listen in the same order and orientation. (see
     * Model::Reservoir::Grid::Cell for illustration as it is included in the code.
     */

    /* Assumption: The block is fairly regular, i.e. corners are right angles.
     Determine the 3(orthogonal, or very close to orth.) vectors to project line onto.

     Corners 4&5, 4&6 and 4&0 span the cell from the front bottom left corner. */

    QList<Model::Reservoir::Grid::XYZCoordinate > corners = cell.corners();

    QVector3D xvec = WellIndexCalculator::GeometryFunctions::XYZpoints_to_qvector(corners[4],corners[5]);
    QVector3D yvec = WellIndexCalculator::GeometryFunctions::XYZpoints_to_qvector(corners[4],corners[6]);
    QVector3D zvec = WellIndexCalculator::GeometryFunctions::XYZpoints_to_qvector(corners[4],corners[0]);

    // Finds the dimensional sizes (i.e. length in each direction) of the cell block
    double dx = xvec.length();
    double dy = yvec.length();
    double dz = zvec.length();
    // Get directional permeabilities
    double kx = cell.permx();
    double ky = cell.permy();
    double kz = cell.permz();

    double Lx=0;
    double Ly=0;
    double Lz=0;

    // Need to add projections of all segments, each line is one segment.
    for (int ii = 0; ii < start_points.length(); ++ii) {
        // Current segment ii
        // Compute vector from segment
        QVector3D current_vec = QVector3D(end_points.at(ii) - start_points.at(ii));
                //GeometryFunctions::XYZpoints_to_qvector(line->p0(),line->p1());
        /* Proejcts segment vector to directional spanning vectors and determines the length.
         * of the projections. Note that we only only care about the length of the projection,
         * not the spatial position. Also adds the lengths of previous segments in case there
         * is more than one segment within the well.
         */
        Lx = Lx + GeometryFunctions::project_v1_on_v2(current_vec,xvec).length();
        Ly = Ly + GeometryFunctions::project_v1_on_v2(current_vec,yvec).length();
        Lz = Lz + GeometryFunctions::project_v1_on_v2(current_vec,zvec).length();
    }

    // Compute Well Index from formula provided by Shu
    double well_index_x = (GeometryFunctions::dir_well_index(Lx,dy,dz,ky,kz,wellbore_radius));
    double well_index_y = (GeometryFunctions::dir_well_index(Ly,dx,dz,kx,kz,wellbore_radius));
    double well_index_z = (GeometryFunctions::dir_well_index(Lz,dx,dy,kx,ky,wellbore_radius));
    return sqrt(well_index_x*well_index_x + well_index_y*well_index_y + well_index_z*well_index_z);
}

double GeometryFunctions::dir_well_index(double Lx, double dy, double dz, double ky, double kz, double wellbore_radius)
{
    // wellbore radius should probably be taken as input. CAREFUL
    //double wellbore_radius = 0.1905;
    double silly_eclipse_factor =0.008527;
    double well_index_i = silly_eclipse_factor*(2*M_PI*sqrt(ky*kz)*Lx)/(log(GeometryFunctions::dir_wellblock_radius(dy,dz,ky,kz)/wellbore_radius));
    return well_index_i;
}

double GeometryFunctions::dir_wellblock_radius(double dx, double dy, double kx, double ky)
{
    double r = 0.28*sqrt( (dx*dx)*sqrt(ky/kx) + (dy*dy)*sqrt(kx/ky) )/ ( sqrt(sqrt(kx/ky)) + sqrt(sqrt(ky/kx))  );
    return r;
}

// STILL NOT FINISHED: CONSIDER FIRST IF GRID IS REGULAR
QPair<QList<int>, QList<QVector3D>> GeometryFunctions::find_traversed_blocks(Model::Reservoir::Grid::Grid *grid, QVector3D start_point, QVector3D end_point)
{
    // Create return lists
    QPair<QList<int>,QList<QVector3D>> pair;
    QList<int> cells_traversed;
    QList<QVector3D> intersection_points;

    // Get dimensions of grid and number of cells
    int nx = grid->Dimensions().nx;
    int ny = grid->Dimensions().ny;
    int nz = grid->Dimensions().nz;
    int n_cells = nx*ny*nz;

    /* First compute which cell the points start
     * and end are in by brute force.
     * For every cell in reservoir,
     * check if point is inside cell.
     */
    int first = -1;
    int last  = -1;
    int count =  0;
    while (((first == -1) ||(last == -1)) && count < n_cells){
        if( GeometryFunctions::is_point_inside_cell(grid->GetCell(count),start_point)){first = count;}
        if( GeometryFunctions::is_point_inside_cell(grid->GetCell(count),end_point  )){last  = count;}
    }

    // If either start point or end point is outside grid, throw exception
    if( (first == -1)||(last == -1) ){
        // NEED TO THROW EXCEPTION. POINT OUTSIDE GRID
        return pair;
    }

    // Add start point and first cell to lists.
    cells_traversed.append(first);
    intersection_points.append(start_point);

    /* Loop through cells along line segment untill
     * you end up in last cell (current == last)
     * For each cell find which face of the cell
     * the line segments exits through. Faces are
     * numbered 0,1,2,3,4 and 5 respectively.
     * Cells also have (i,j,k) indeces
     * faces 0,1 are -k and +k direction
     * faces 2,3 are -i and +i direction
     * faces 4,5 are -j and +j direction
     * (Note that coordinates in k direction
     * should be negative in a reservoir
     * but are positive in the grid class
     * here. i.e. this grid is upside down
     * compared to the physical grid)
     */
    int current = first;
    while(current!=last){


    }


    /* Collect global indeces of intersected cells and the
     * endpoints of the line segment inside each cell in a
     * QPair type to return them both
     */
    //pair.first = cell_global_index;
    //pair.second = entry_points;
    return pair;
}

bool GeometryFunctions::is_point_inside_cell(Model::Reservoir::Grid::Cell cell, QVector3D point)
{
    // First find normal vectors of all faces of block/cell.
    QList<QList<QVector3D>> face_corner_coords = GeometryFunctions::cell_planes_coords(cell.corners());
    QList<QVector3D> normal_vectors;
    for( int ii=0; ii<6; ii++){

        QVector3D cur_normal_vector = GeometryFunctions::normal_vector(face_corner_coords.at(ii).at(0),
                                                                        face_corner_coords.at(ii).at(1),
                                                                        face_corner_coords.at(ii).at(2));
        normal_vectors.append(cur_normal_vector);
    }

    /* For loop through all faces to check that point
     * is on right side of every face (i.e. in the same
     * direction as the computed normal vector) by
     * taking the dot product of the normal vector with
     * the vector going from one corner of the face to
     * point
     */
    bool point_inside = true;
    for(int face_number = 0; face_number<6; face_number++){
        if( QVector3D::dotProduct(point - face_corner_coords.at(face_number).at(0), normal_vectors.at(face_number)) < 0){
            point_inside = false;
        }
    }

    return point_inside;
}

Model::Reservoir::Grid::Cell GeometryFunctions::get_cell_enveloping_point(Model::Reservoir::Grid::Grid *grid, QVector3D point)
{
    // Get total number of cells
    int total_cells = grid->Dimensions().nx*grid->Dimensions().ny*grid->Dimensions().nz;

    for(int ii=0; ii<total_cells; ii++){
        if( GeometryFunctions::is_point_inside_cell(grid->GetCell(ii),point) ){
            return grid->GetCell(ii);
        }
    }
    throw std::runtime_error("WellIndexCalculator::get_cell_enveloping_point: Cell is outside grid ("
                             + std::to_string(point.x()) + ", "
                             + std::to_string(point.y()) + ", "
                             + std::to_string(point.z()) + ")"
                             );
}

QPair<QList<int>, QList<double> > GeometryFunctions::well_index_of_grid(Model::Reservoir::Grid::Grid *grid, QList<QVector3D> start_points, QList<QVector3D> end_points, double wellbore_radius)
{
    // Find intersected blocks and the points of intersection
    QPair<QList<int>, QList<QVector3D>> temp_pair = GeometryFunctions::cells_intersected(start_points.at(0),end_points.at(0),grid);
    QPair<QList<int>, QList<double>> pair;

    /*for(int ii=0; ii<temp_pair.first.length(); ii++){
        entry_points.append(temp_pair.second.at(ii));
        exit_points.append(temp_pair.second.at(ii+1));
    }*/

    QList<double> well_indeces;
    for(int ii=0; ii<temp_pair.first.length(); ii++){
        QList<QVector3D> entry_points;
        QList<QVector3D> exit_points;
        entry_points.append(temp_pair.second.at(ii));
        exit_points.append(temp_pair.second.at(ii+1));
        well_indeces.append(GeometryFunctions::well_index_cell_qvector(grid->GetCell(temp_pair.first.at(ii)),entry_points, exit_points, wellbore_radius));
    }
    pair.first = temp_pair.first;
    pair.second = well_indeces;
    return pair;
}

double GeometryFunctions::movement_cost(QList<QVector3D> old_coords, QList<QVector3D> new_coords)
{
    double n_of_points = old_coords.length();
    if(new_coords.length()!=n_of_points){throw geometryfunctions::MovementCost_VectorsNotSameLength("Lists of points are not the same length");}
    double cost_squares;
    for (int ii=0; ii<n_of_points; ii++){
        cost_squares += pow(old_coords.at(ii).distanceToPoint(new_coords.at(ii)),2);
    }

    return sqrt(cost_squares);
}

void GeometryFunctions::print_well_index_file(Model::Reservoir::Grid::Grid *grid, QList<QVector3D*> start_points, QList<QVector3D*> end_points, double wellbore_radius, double min_wi, QString filename)
{
    // Find intersected blocks and the points of intersection
    QPair<QList<int>, QList<QVector3D>> temp_pair = GeometryFunctions::cells_intersected(*start_points.at(0),*end_points.at(0),grid);
    QPair<QList<int>, QList<double>> pair;

    QList<double> well_indeces;
    for(int ii=0; ii<temp_pair.first.length(); ii++){
        QList<QVector3D> entry_points;
        QList<QVector3D> exit_points;
        entry_points.append(temp_pair.second.at(ii));
        exit_points.append(temp_pair.second.at(ii+1));
        well_indeces.append(GeometryFunctions::well_index_cell_qvector(grid->GetCell(temp_pair.first.at(ii)),entry_points, exit_points, wellbore_radius));
    }
    pair.first = temp_pair.first;
    pair.second = well_indeces;

    std::ofstream myfile;
    myfile.open (filename.toUtf8().constData());
    myfile <<"-- ==================================================================================================\n";
    myfile <<"-- \n";
    myfile <<"-- Exported from ECL_5SPOT\n";
    myfile <<"-- \n";
    myfile <<"-- Exported by user hilmarm from WellIndexCalculator \n";
    myfile <<"-- \n";
    myfile <<"-- ==================================================================================================\n";
    myfile <<"\n";
    myfile <<"WELSPECS\n";
    myfile <<" 'TW01' 'PRODUC'    1    1  1712.00 'OIL'    0.0 'STD' 'SHUT' 'YES' 0 'SEG' /\n";
    myfile <<"/\n";
    myfile <<" \n";
    myfile <<"\n";
    myfile <<"GRUPTREE\n";
    myfile <<" 'PRODUC' 'FIELD' /\n";
    myfile <<" 'INJECT' 'FIELD' /\n";
    myfile <<"/\n";
    myfile <<"\n";
    myfile <<"COMPDAT\n";
    myfile <<"-- --------------------------------------------------------------------------------------------------\n";
    for( int ii = 0; ii<pair.first.length(); ii++){

        if(pair.second.at(ii)>min_wi){
            myfile << " 'TW01'" ;
            myfile << std::setw(5) << grid->GetCell(pair.first.at(ii)).ijk_index().i()+1;
            myfile << std::setw(5) << grid->GetCell(pair.first.at(ii)).ijk_index().j()+1;
            myfile << std::setw(5) << grid->GetCell(pair.first.at(ii)).ijk_index().k()+1;
            myfile << std::setw(5) << grid->GetCell(pair.first.at(ii)).ijk_index().k()+1;

            myfile << "  'OPEN' 0 " ;
            float temp = pair.second.at(ii);
            myfile << std::setprecision(5) << std::fixed;
            myfile <<std::setw(13) << temp;

            myfile.unsetf(std::ios_base::fixed);
            myfile << std::setw(8)  << wellbore_radius*2 ;

            float temp2 = grid->GetCell(pair.first.at(ii)).permx()*temp_pair.second.at(ii).distanceToPoint(temp_pair.second.at(ii+1));
            myfile << std::setprecision(5) << std::fixed;
            myfile << std::setw(13) << temp2;
            myfile << "    0.00 0.0 'X'    4.75 /\n";
//            myfile << "\n";
//            myfile << "\n";
            myfile.unsetf(std::ios_base::fixed);
        }
    }
    myfile << "-- --------------------------------------------------------------------------------------------------\n";
    myfile << "/";

    myfile.close();
}



}
