#include "utils.h"
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
