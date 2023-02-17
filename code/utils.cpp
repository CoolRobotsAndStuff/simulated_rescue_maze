#include "utils.hpp"
#include <cmath>

namespace simulated_rescue_maze{
double rads2degs(double rads){
  return rads * (double(180) / M_PI);
  }

double degs2rads(double degs){
  return degs * (double(180) / M_PI);
}

double normalize_degs(double degs){
  degs = fmod(degs, double(360));
  if (degs < 0)
      degs += 360;
  return degs;
}


double normalize_rads(double rads){
  rads = fmod(rads, double(2 * M_PI));
  if (rads < 0)
      rads += 2 * M_PI;
  return rads;
}

double changeValueRange(double t_value, double t_min, double t_max, double t_new_min, double t_new_max){
  double old_range = (t_max - t_min);
  if (old_range == 0){
    return t_min;
  }    
  else
  {
    double new_range = (t_new_max - t_new_min);
    return (((t_value - t_min) * new_range) / old_range) + t_new_min;
  }
}

double get_dist_from_coord_diff(Vector2D<double> coordinate_difference){
  return sqrt(pow(coordinate_difference.x, 2) + pow(coordinate_difference.y, 2));
};


double get_rads_from_coord_diff(Vector2D<double> coordinate_difference){
  return normalize_rads(atan2(coordinate_difference.x, coordinate_difference.y));
};
double get_degs_from_coord_diff(Vector2D<double> coordinate_difference){
  return rads2degs(get_rads_from_coord_diff(coordinate_difference));
};


std::array<double, 2> get_rads_and_dist_form_coord_diff(Vector2D<double> coords){
  std::array<double, 2> result;
  result[0] = get_rads_from_coord_diff(coords);
  result[1] = get_dist_from_coord_diff(coords);
  return result;
  }
std::array<double, 2> get_degs_and_dist_form_coord_diff(Vector2D<double> coords){
  std::array<double, 2> result = get_rads_and_dist_form_coord_diff(coords);
  result[0] = rads2degs(result[0]);
  return result;
};


std::array<double, 2> get_rads_and_dist_from_coords(Vector2D<double> coords1, Vector2D<double> coords2){
  Vector2D<double> coord_difference;
  coord_difference.x = coords1.x - coords2.x;
  coord_difference.y = coords1.y - coords2.y;

  return get_rads_and_dist_form_coord_diff(coord_difference);
};
std::array<double, 2> get_degs_and_dist_from_coords(Vector2D<double> coords1, Vector2D<double> coords2){
  Vector2D<double> coord_difference;
  coord_difference.x = coords1.x - coords2.x;
  coord_difference.y = coords1.y - coords2.y;

  return get_degs_and_dist_form_coord_diff(coord_difference);
  
};


Vector2D<double> get_coords_from_rads_and_dist(double radians, double distance){
  Vector2D<double> result;
  result.x = distance * sin(radians);
  result.y = distance * cos(radians);
  return result;
};

Vector2D<double> get_coords_from_degs_and_dist(double degrees, double distance){
  double rads = degs2rads(degrees);
  return get_coords_from_rads_and_dist(rads, distance);
};

double get_shortest_dist_between_degs(double ang1, double ang2){
  double min_ang = std::min(ang1, ang2);
  double max_ang = std::max(ang1, ang2);

  double dist1 = max_ang - min_ang;
  double dist2 = (360 + min_ang) - max_ang;
  return std::min(dist1, dist2);
}

}