#include "utils.hpp"
#include <cmath>


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

float change_float_range(float value, float min, float max, float new_min, float new_max){
    float old_range = (max - min);
    if (old_range == 0){
        return min;
    }    
    else
    {
        float new_range = (new_max - new_min);
        return (((value - min) * new_range) / old_range) + new_min;
    }
}

double change_double_range(double value, double min, double max, double new_min, double new_max){
    double old_range = (max - min);
    if (old_range == 0){
        return min;
    }    
    else
    {
        double new_range = (new_max - new_min);
        return (((value - min) * new_range) / old_range) + new_min;
}
}