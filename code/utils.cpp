#include "utils.hpp"
#include <cmath>

namespace simulated_rescue_maze{

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


}