#include "actuators.hpp"
#include <webots/Motor.hpp>

using namespace actuators;

Motor::Motor(webots::Motor *motor_device, int time_step){
    double time_step_s = time_step * 0.001;
    device = motor_device;
    device->setPosition(INFINITY);
    

}

void Motor::set_velocity(float input_velocity){
    device->setVelocity(input_velocity * 10);
    velocity = input_velocity * 10;
}