#include "utils.hpp"
#include <cmath>

namespace simulated_rescue_maze{

double changeValueRange(double t_value, double t_min, double t_max, double t_newMin, double t_newMax){
  double oldRange = (t_max - t_min);
  if (oldRange == 0){
    return t_min;
  }    
  else
  {
    double newRange = (t_newMax - t_newMin);
    return (((t_value - t_min) * newRange) / oldRange) + t_newMin;
  }
}

}