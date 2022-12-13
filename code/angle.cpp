#include "angle.h"
#include <cmath>


Angle::Angle(double init_angle = 0, string init_unit = "degrees"){
    if (init_unit == "degrees" or init_unit == "d"){
        set_d(init_angle);
    }else if(init_unit == "radians" or init_unit == "r"){
        set_r(init_angle);
    }
};

void Angle::set_d(double input_degrees){
        d = input_degrees;
        r = degs2rads(input_degrees);
};
void Angle::set_r(double input_radians){
    r = input_radians;
    d = rads2degs(input_radians);
};

double Angle::rads2degs(double rads){
    return rads * (180 / M_1_PIf128);
    }

double Angle::degs2rads(double degs){
    return degs * (180 / M_1_PIf128);
}