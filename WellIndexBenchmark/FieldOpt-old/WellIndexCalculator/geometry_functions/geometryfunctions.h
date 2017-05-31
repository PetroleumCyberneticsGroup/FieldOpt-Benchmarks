#ifndef GEOMETRYFUNCTIONS_H
#define GEOMETRYFUNCTIONS_H
#include "../FieldOpt-old/Model/reservoir/grid/xyzcoordinate.h"
#include "../FieldOpt-old/Model/reservoir/grid/cell.h"
#include "../FieldOpt-old/Model/reservoir/grid/grid.h"
#include "../FieldOpt-old/Model/reservoir/grid/eclgrid.h"
#include "../FieldOpt-old/Model/reservoir/grid/grid_exceptions.h"
#include "../FieldOpt-old/WellIndexCalculator/geometry_classes/line.h"
#include "../FieldOpt-old/WellIndexCalculator/geometry_classes/squareplane.h"
#include <QList>
#include <QVector3D>
#include <QPair>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

namespace WellIndexCalculator {

/*!
 * \brief WellIndexCalculator is a toolbox for doing geometric calculations on points and lines within a Grid
 *
 * We want to collect all geometric functions necessary to determine which Cells are intercepted by a line
 * and thereafter use this to compute the Well Index for every Cell.
 */

class GeometryFunctions {
private:
    GeometryFunctions();
public:
    //This function is just some test function to check declarations
    static Model::Reservoir::Grid::XYZCoordinate move3dpoint(Model::Reservoir::Grid::XYZCoordinate point);
    // End of test function

    static double distance_coordinates(Model::Reservoir::Grid::XYZCoordinate start_point, Model::Reservoir::Grid::XYZCoordinate end_point);

    /*!
     * \brief line_intersects_plane returns the point of intersection between a  if a Line intersects a plane within the 4 corners of the plane as given by corners. The method used is described here: http://geomalgorithms.com/a05-_intersect-1.html
     * \param SquarePlane object containing points which lie in the same plane
     * \param a line
     * \return the point of intersection between the line and the plane
    */
    static Model::Reservoir::Grid::XYZCoordinate line_intersects_plane(GeometryClasses::SquarePlane Plane , GeometryClasses::Line Line);

    static Model::Reservoir::Grid::XYZCoordinate line_intersects_plane_vectorized(GeometryClasses::SquarePlane plane, GeometryClasses::Line line);

    static QVector3D line_plane_intersection(QVector3D p0, QVector3D p1, QVector3D normal_vector, QVector3D point_in_plane);

    /*!
     * \brief normal_vector returns the cross product of the two vectors (p2 - p0) and (p2 - p0)
     * \param p0
     * \param p1
     * \param p2
     * \return normal_vector spanned by points
    */
    static QVector3D normal_vector_XYZ(Model::Reservoir::Grid::XYZCoordinate p0, Model::Reservoir::Grid::XYZCoordinate p1, Model::Reservoir::Grid::XYZCoordinate p2);

    static QVector3D normal_vector(QVector3D p0, QVector3D p1, QVector3D p2);

    /*!
     * \brief point_on_same_side returns a positive double if point is on the same side of a plane
     * (containing plane_point and with normal_vector as the normal vector) as the normal vector,
     * zero if it is in the plane, and negative if it's on the other side.
     * \param point
     * \param plane_point
     * \param normal_vector
     * \return normal_vector spanned by points
    */
    static bool point_on_same_side(QVector3D point, QVector3D plane_point, QVector3D normal_vector, double slack);

    /*!
     * \brief Given a reservoir with blocks and a line(start_point to end_point), return global index of all blocks interesected
     * by the line and the points of intersection
     * \param start point line
     * \param end point line
     * \param reservoir (containing blocks/cells)
     * \param QList for storing global indeces of intersected blocks
     * \param QList for storing line segments that are inside intersected blocks
     */
    static QPair<QList<int>, QList<QVector3D> > cells_intersected(QVector3D start_point, QVector3D end_point, Model::Reservoir::Grid::Grid *grid);

    static QVector3D findEndpoint(QVector3D start_pt, QVector3D end_point, Model::Reservoir::Grid::Grid *grid);

    /*!
     * \brief Generates a double array with the numbers of 3 corners from each of the 6 faces of a cell that
     * will be used to create a normal vector for each face.
     * \return double list of corner numbers for each face
     */
    static QList<QList<QVector3D > > cell_planes_coords(QList<Model::Reservoir::Grid::XYZCoordinate > corners);

    static QVector3D find_exit_point(Model::Reservoir::Grid::Cell cell, QVector3D start_point, QVector3D end_point, QVector3D exception_point);

    /*!
     * \brief project_line_to_plane is the orthognal projection of two points (and the line segment connecting them) down on a plane
     * \param a line
     * \param SquarePlane object containing points which lie in the same plane
     * \return orthogonal projection of line
    */
    static GeometryClasses::Line project_line_to_plane(GeometryClasses::Line line, GeometryClasses::SquarePlane plane);

    /*!
     * \brief project_line_to_plane is the orthognal projection of two points (and the line segment connecting them) down on a plane
     * \param a line
     * \param SquarePlane object containing points which lie in the same plane
     * \return orthogonal projection of line
    */
    static QVector3D project_point_to_plane(QVector3D point, QVector3D normal_vector, QVector3D plane_point);

    /*!
     * \brief project_v1_onv2 is the orthognal projection of a vector v1 onto the vector v2.
     * \param vector to be projected
     * \param vector onto which projection is done
     * \return orthogonal projection of vector
    */
    static QVector3D project_v1_on_v2(QVector3D v1, QVector3D v2);

    /*!
     * \brief Convert a non-empty XYZCoordinate* type variable to QVector3D* type
     * \param XYZCoordinate*
     * \return QVector3D*
    */
    static QVector3D XYZ_to_qvec(Model::Reservoir::Grid::XYZCoordinate coor);

    /*!
     * \brief Convert a non-empty QVector3D* type variable to XYZCoordinate* type
     * \param QVector3D*
     * \return XYZCoordinate*
    */
    static Model::Reservoir::Grid::XYZCoordinate qvec_to_XYZ(QVector3D xyz);

    /*!
     * \brief Find vector going from p1 to p2 and return it as QVector3D*
     * \param first point
     * \param second point
     * \return vector between input points
    */

    static QVector3D XYZpoints_to_qvector(Model::Reservoir::Grid::XYZCoordinate p1, Model::Reservoir::Grid::XYZCoordinate p2);

    /*!
     * \brief Compute the well index for a single cell/block for a single vertical well through the centre of the block.
     * \param A line that is enclosed by the cell
     * \param cell/block
     * \return Well index for block/cell
    */
    static double vertical_well_index_cell(Model::Reservoir::Grid::Cell block , double kx, double ky, double wellbore_radius);

    /*!
     * \brief Compute the well index for a (one) single cell/block by using the Projection Well Method (Shu 2005).
     * \param A line that is enclosed by the cell
     * \param cell/block
     * \param wellbore radius
     * \return Well index for block/cell
    */
    static double well_index_cell(QList<GeometryClasses::Line> lines, Model::Reservoir::Grid::Cell block , double wellbore_radius);

    /*!
     * \brief Compute the well index for a (one) single cell/block by using the Projection Well Method (Shu 2005).
     * \param cell/block
     * \param start point line segment/well
     * \param end point line segment/well
     * \param wellbore radius
     * \return Well index for block/cell
    */
    static double well_index_cell_qvector(Model::Reservoir::Grid::Cell block, QList<QVector3D> start_points, QList<QVector3D> end_points, double wellbore_radius);

    /*!
     * \brief Auxilary function for well_index_cell function
     * \param lenght of projection in first direction
     * \param size block second direction
     * \param size block third direction
     * \param permeability second direction
     * \param permeability second direction
     * \param wellbore radius
     * \return directional well index
    */
    static double dir_well_index(double Lx, double dy, double dz, double ky, double kz, double wellbore_radius);

    /*!
     * \brief Auxilary function(2) for well_index_cell function
     * \param size block second direction
     * \param size block third direction
     * \param permeability second direction
     * \param permeability second direction
     * \return directional wellblock radius
     */
    static double dir_wellblock_radius(double dx, double dy, double kx, double ky);

    /*!
     * \brief Given a reservoir with blocks and a line segment(well), return all blocks interesected by the line segment and the points of intersection
     * \param reservoir (containing blocks/cells)
     * \param start point line segment
     * \param end point line segment
     * \return List of global indeces of intersected blocks and list of points intersected
     */
    static QPair<QList<int>, QList<QVector3D>> find_traversed_blocks(Model::Reservoir::Grid::Grid *grid, QVector3D start, QVector3D end);

    /*!
     * \brief Given a Model::Reservoir::Grid::Cell cell and a point, return true if the given point is inside the (or on boundary of) cell
     * \param Cell containing coordinates of corners
     * \param point
     * \return true if point is inside cell, false if it is not
     */
    static bool is_point_inside_cell(Model::Reservoir::Grid::Cell cell, QVector3D point);

    /*!
     * \brief Given a Model::Reservoir::Grid::Grid grid and a point, return a cell that envelopes the point
     * \param A grid containing cells
     * \param point
     * \return returns cell enveloping/containing point. return 0 if no cell contains point
     */
    static Model::Reservoir::Grid::Cell get_cell_enveloping_point(Model::Reservoir::Grid::Grid *grid, QVector3D point);

    /*!
     * \brief Given a reservoir and a line segment (start, end) return the calculated well indeces for all cells intersected by the line segment.
     * \param A grid containing cells
     * \param start point line segment/well
     * \param end point line segment/well
     * \return list of cells intersected and their calculated well indeces
     */
    static QPair<QList<int>, QList<double>> well_index_of_grid(Model::Reservoir::Grid::Grid *grid , QList<QVector3D> start_points, QList<QVector3D> end_points, double wellbore_radius);

    /*!
     * \brief Given two lists of QVector3D* points, calculates the L2-norm of the vectors between the points.
     * \param initial points
     * \param moved points
     * \return L2 norm of vectors of how points moved.
     */
    static double movement_cost(QList<QVector3D> old_coords, QList<QVector3D> new_coords);

    static void print_well_index_file(Model::Reservoir::Grid::Grid *grid , QList<QVector3D*> start_point, QList<QVector3D*> end_points, double wellbore_radius, double min_wi, QString filename);
};

}

#endif // GEOMETRYFUNCTIONS_H
