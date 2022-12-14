#include <webots/Motor.hpp>

namespace actuators{
    class Motor{
        public:
            double time_step_s;
            webots::Motor *device;
            float velocity;
            Motor(webots::Motor *motor_device, int time_step);
            void set_velocity(float input_velocity);
    };

}