#include <iostream>
#include <string.h>
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include "sensors.hpp"
#include "actuators.hpp"
#include "environment_model.hpp"
#include "sensor_data_loader.hpp"

using namespace sensors;
using namespace actuators;

webots::Robot *robot = new webots::Robot();

int const time_step = 32;

int main(){
    //Inside main:
    Motor left_wheel(robot->getMotor("wheel1 motor"), time_step);    //Step 1
    Motor right_wheel(robot->getMotor("wheel2 motor"), time_step);
    
    SensorManager my_sensor_manager(robot, time_step);

    env_model::Robot my_robot_model;

    SensorDataLoader my_data_loader;

    while (robot->step(time_step) != -1) {
        my_sensor_manager.update();

        my_robot_model = my_data_loader.load_sensor_data(my_robot_model, my_sensor_manager);

        std::cout << "Orientation | " << my_robot_model.orientation << std::endl;
        my_robot_model.position.print();

        right_wheel.set_velocity(0.1);
        left_wheel.set_velocity(-0.1);

    };

    /*
    Gyroscope my_gyro(robot->getGyro("gyro"), 32);
    GPS my_gps(robot->getGPS("gps"), 32);

    while (robot->step(time_step) != -1) {
        my_gps.update();
        my_gps.print_values();
        my_gyro.update();
        my_gyro.print_values(true);
        right_wheel.set_velocity(0.1);
        left_wheel.set_velocity(-0.1);


    };
    */
    
}