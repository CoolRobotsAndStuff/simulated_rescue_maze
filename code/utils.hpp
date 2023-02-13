#include <array>
#include "generic_data_structures.hpp"

double rads2degs(double rads);
double degs2rads(double degs);
double normalize_degs(double degs);
double normalize_rads(double degs);
float change_float_range(float value, float min, float max, float new_min, float new_max);
double change_double_range(double value, double min, double max, double new_min, double new_max);


double get_dist_from_coord_diff(Vector2D<double> coordinate_difference);

double get_rads_from_coord_diff(Vector2D<double> coordinate_difference);
double get_degs_from_coord_diff(Vector2D<double> coordinate_difference);

std::array<double, 2> get_rads_and_dist_form_coord_diff(Vector2D<double> coords);
std::array<double, 2> get_degs_and_dist_form_coord_diff(Vector2D<double> coords);

std::array<double, 2> get_rads_and_dist_from_coords(Vector2D<double> coords1, Vector2D<double> coords2);
std::array<double, 2> get_degs_and_dist_from_coords(Vector2D<double> coords1, Vector2D<double> coords2);

Vector2D<double> get_coords_from_rads_and_dist(double radians, double distance);
Vector2D<double> get_coords_from_degs_and_dist(double degrees, double distance);


double get_shortest_dist_between_degs(double ang1, double ang2);