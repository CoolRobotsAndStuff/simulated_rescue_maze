#include <iostream>

#include <string.h>

#include <webots/Motor.hpp>
#include <webots/Robot.hpp>

#include "actuators.hpp"

#include "generic_data_structures.hpp"
#include "environment_model.hpp"
#include "sensor_data_loader.hpp"
#include "corrector.hpp"


webots::Robot *robot = new webots::Robot();

int const timeStepMilliseconds = 32;


simulated_rescue_maze::Wheel leftWheel;
simulated_rescue_maze::Wheel rightWheel;

simulated_rescue_maze::SensorManager sensorManager;

simulated_rescue_maze::RotationToAngleManager rotationManager;

int main(){
    rightWheel.setDevice(robot->getMotor("wheel1 motor"));
    rightWheel.initializeValues();

    leftWheel.setDevice(robot->getMotor("wheel2 motor"));
    leftWheel.initializeValues();

    sensorManager.initializeSensors(robot, timeStepMilliseconds);

    rotationManager.setWheels(rightWheel, leftWheel);

    while (robot->step(timeStepMilliseconds) != -1) {

        sensorManager.updateSensors();
        rotationManager.setCurrentAngle(sensorManager.getGyroscope().getOrientation().z);

        simulated_rescue_maze::Angle targetAngle = simulated_rescue_maze::Angle(270, simulated_rescue_maze::Angle::DEGREES);
        rotationManager.rotateToAngle(targetAngle, simulated_rescue_maze::RotationToAngleManager::CLOSEST);
        std::cout << rotationManager.finishedRotating() << std::endl;


        //sensorManager.getGps().printValues();
        sensorManager.getGyroscope().printValues();
    }

    return 1;
    };