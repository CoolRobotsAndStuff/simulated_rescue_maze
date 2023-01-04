#include <string>
#include <limits>
#include "generic_data_structures.hpp"

using namespace std;


class AngleRotator{
    private:
        string get_direction(double angle, string direction = "closest");

    public:
        bool is_first_time;
        double start_angle;
        double current_angle;

        double min_velocity;
        double max_velocity;

        double min_velocity_cap;
        double max_velocity_cap;

        double error_margin;

    AngleRotator();
    AngleRotator(double error_margin, double min_velocity, double max_velocity, double min_velocity_cap = 0, double max_velocity_cap = numeric_limits<double>::infinity());
    DifferentialVelocities rotate_to_angle(double angle, string direction);
    void init(double error_margin, double min_velocity, double max_velocity, double min_velocity_cap = 0, double max_velocity_cap = numeric_limits<double>::infinity());
    void set_current_angle(double angle);


};