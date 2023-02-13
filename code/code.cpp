#include <iostream>

#include <string.h>

#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include "sensors.hpp"
#include "actuators.hpp"

#include "environment_model.hpp"
#include "sensor_data_loader.hpp"
#include "corrector.hpp"

using namespace sensors;
using namespace actuators;

webots::Robot *robot = new webots::Robot();

int const time_step = 32;

Motor left_wheel(robot->getMotor("wheel1 motor"), time_step);    //Step 1
Motor right_wheel(robot->getMotor("wheel2 motor"), time_step);

DifferentialVelocities wheel_velocities;

SensorManager my_sensor_manager(robot, time_step);

env_model::Robot my_robot_model;

SensorDataLoader my_data_loader;

// error_magin, min_velocity, max_velocity, min_velocity_cap, max_velocity_cap
AngleRotator my_angle_rotator(2, 0.2, 1., 0., 1.);

CoordinatesMover my_coordinates_mover(0.005, 0., 1.);

int main(){
    while (robot->step(time_step) != -1) {
        my_sensor_manager.update();

        my_robot_model = my_data_loader.load_sensor_data(my_robot_model, my_sensor_manager);

        std::cout << "Orientation | " << my_robot_model.orientation << std::endl;
        my_robot_model.position.print();

        my_angle_rotator.set_current_angle(my_robot_model.orientation);
        my_coordinates_mover.set_current_position(my_robot_model.position);

        //DifferentialVelocities wheel_velocities = my_angle_rotator.rotate_to_angle(180, "farthest");
        FloatVector3D target_position;
        target_position.x = -0.18;
        target_position.y = -0.3;

        wheel_velocities = my_coordinates_mover.move_to_position(target_position, my_angle_rotator);

        right_wheel.setVelocity(wheel_velocities.right);
        left_wheel.setVelocity(wheel_velocities.left);

        if (wheel_velocities.left == 0. and wheel_velocities.right == 0.){
            break;
        }

    };

    while (robot->step(time_step) != -1) {
        my_sensor_manager.update();

        my_robot_model = my_data_loader.load_sensor_data(my_robot_model, my_sensor_manager);

        std::cout << "Orientation | " << my_robot_model.orientation << std::endl;
        my_robot_model.position.print();

        my_angle_rotator.set_current_angle(my_robot_model.orientation);
        my_coordinates_mover.set_current_position(my_robot_model.position);

        //DifferentialVelocities wheel_velocities = my_angle_rotator.rotate_to_angle(180, "farthest");
        FloatVector3D target_position;
        target_position.x = -0.08;
        target_position.y = -0.3;

        wheel_velocities = my_coordinates_mover.move_to_position(target_position, my_angle_rotator);

        right_wheel.setVelocity(wheel_velocities.right);
        left_wheel.setVelocity(wheel_velocities.left);

    };
}

/*
void move_to_coordinates(FloatVector2D coordinates){
    while (robot->step(time_step) != -1) {
        on_loop_start();
        FloatVector3D target_position;
        target_position.x = coordinates.x;
        target_position.y = coordinates.y;
        wheel_velocities = my_coordinates_mover.move_to_position(target_position, my_angle_rotator);
        on_loop_end();
        if (wheel_velocities.left == 0. and wheel_velocities.right == 0.){
            break;
        }
    }
}

void delay(float miliseconds){
    on_loop_start();
    pass;
    on_loop_end();
}

void on_loop_start(){
    my_sensor_manager.update();

    my_robot_model = my_data_loader.load_sensor_data(my_robot_model, my_sensor_manager);

    std::cout << "Orientation | " << my_robot_model.orientation << std::endl;
    my_robot_model.position.print();

    my_angle_rotator.set_current_angle(my_robot_model.orientation);
    my_coordinates_mover.set_current_position(my_robot_model.position);
}

void on_loop_end(){
    right_wheel.setVelocity(wheel_velocities.right);
    left_wheel.setVelocity(wheel_velocities.left);
}
*/