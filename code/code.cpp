#include <iostream>
#include <string.h>
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include "sensors.h"

using namespace sensors;

webots::Robot *robot = new webots::Robot();

int const time_step = 32;

int main(){
    //Inside main:
    webots::Motor *wheel_left = robot->getMotor("wheel1 motor");    //Step 1
    webots::Motor *wheel_right = robot->getMotor("wheel2 motor");

    wheel_left->setPosition(INFINITY);   //Step 2
    wheel_right->setPosition(INFINITY);

    Gyroscope my_gyro(robot->getGyro("gyro"), 32);
    GPS my_gps(robot->getGPS("gps"), 32);

    while (robot->step(time_step) != -1) {
        my_gps.update();
        my_gps.print_values();
        my_gyro.update();
        my_gyro.print_values(true);
        wheel_left->setVelocity(-1.0);    //Step 3
        wheel_right->setVelocity(1.0);

    };
    
}