#include <webots/GPS.hpp>
#include <webots/Gyro.hpp>


namespace sensors{
    class GPS{
        public:
            double time_step_s;

            webots::GPS *device;

            struct {double x; double y; double z;} position;
            struct {double x; double y; double z;} previous_position;
            struct {double x; double y; double z;} velocity;
            struct {double x; double y; double z;} previous_velocity;
            struct {double x; double y; double z;} acceleration;

            GPS(webots::GPS *gps_device, int time_step);

            void update();
            void print_values();
    };

    class Gyroscope{
        public:
            double time_step_s;

            webots::Gyro *device;

            struct {double x; double y; double z;} orientation_rads;
            struct {double x; double y; double z;} orientation;
            struct {double x; double y; double z;} previous_angular_velocity_rads;
            struct {double x; double y; double z;} angular_velocity_rads;
            struct {double x; double y; double z;} angular_velocity;
            struct {double x; double y; double z;} angular_acceleration_rads;
            struct {double x; double y; double z;} angular_acceleration;
        
            Gyroscope(webots::Gyro *gyro_device, int time_step);

            void update();
            void print_values(bool convert_to_degs);
    };

    
}
