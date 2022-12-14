#include <webots/GPS.hpp>
#include <webots/Gyro.hpp>
#include "generic_data_structures.hpp"

namespace sensors{
    class GPS{
        public:
            double time_step_s;

            webots::GPS *device;

            DoubleVector3D position;
            DoubleVector3D previous_position;
            DoubleVector3D velocity;
            DoubleVector3D previous_velocity;
            DoubleVector3D acceleration;

            GPS(webots::GPS *gps_device, int time_step);

            void update();
            void print_values();
    };

    class Gyroscope{
        public:
            double time_step_s;

            webots::Gyro *device;

            DoubleVector3D orientation_rads;
            DoubleVector3D orientation;
            DoubleVector3D previous_angular_velocity_rads;
            DoubleVector3D angular_velocity_rads;
            DoubleVector3D angular_velocity;
            DoubleVector3D angular_acceleration_rads;
            DoubleVector3D angular_acceleration;
        
            Gyroscope(webots::Gyro *gyro_device, int time_step);

            void update();
            void print_values(bool convert_to_degs);
    };

    
}
