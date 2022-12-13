#include <string>

using namespace std;

class Angle{
    public:
        Angle(double init_angle, string init_unit);

        double d;
        double r;

        void set_d(double input_degrees);
        void set_r(double input_radians);

        double rads2degs(double rads);
        double degs2rads(double degs);
};