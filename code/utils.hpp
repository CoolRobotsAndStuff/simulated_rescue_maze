#pragma once

#include <array>
#include "generic_data_structures.hpp"

namespace simulated_rescue_maze{

double rads2degs(double rads);
double degs2rads(double degs);
double normalize_degs(double degs);
double normalize_rads(double degs);

double changeValueRange(double t_value, double t_min, double t_max, double t_new_min, double t_new_max);


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

}