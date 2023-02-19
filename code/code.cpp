#include <iostream>

#include <string.h>

#include <webots/Motor.hpp>
#include <webots/Robot.hpp>

#include "actuators.hpp"

#include "generic_data_structures.hpp"
#include "environment_model.hpp"
#include "sensor_data_loader.hpp"
#include "corrector.hpp"
#include "drive_base.hpp"


webots::Robot *robot = new webots::Robot();

int const timeStepMilliseconds = 32;


simulated_rescue_maze::Wheel leftWheel;
simulated_rescue_maze::Wheel rightWheel;

simulated_rescue_maze::PlacementSensor placementSensor;

simulated_rescue_maze::DriveBase driveBase;

//simulated_rescue_maze::RotationToAngleManager rotationManager;
//simulated_rescue_maze::MovementToCoordinatesManager movementManager;

int main(){
    // Movement
    rightWheel.setDevice(robot->getMotor("wheel1 motor"));
    rightWheel.initializeValues();
    leftWheel.setDevice(robot->getMotor("wheel2 motor"));
    leftWheel.initializeValues();

    driveBase.setWheels(rightWheel, leftWheel);


    //Sensors
    placementSensor.setGpsDevice(robot->getGPS("gps"));
    placementSensor.setGyroscopeDevice(robot->getGyro("gyro"));

    placementSensor.setTimeStep(timeStepMilliseconds);
    placementSensor.enable();
    placementSensor.initializeValues();

    // Main loop
    while (robot->step(timeStepMilliseconds) != -1) {
        // Sensor updates
        placementSensor.update();

        auto robotPlacement = placementSensor.getPlacement();

        // Actuator updates
        driveBase.setCurrentCoordinates(robotPlacement.position.to2D());
        driveBase.setCurrentAngle(robotPlacement.orientation.z);

        // Main code

        //simulated_rescue_maze::Angle targetAngle = simulated_rescue_maze::Angle(270, simulated_rescue_maze::Angle::DEGREES);
        //rotationManager.rotateToAngle(targetAngle, simulated_rescue_maze::RotationToAngleManager::CLOSEST);
        //std::cout << rotationManager.finishedRotating() << std::endl;
        driveBase.moveToCoordinates(simulated_rescue_maze::Vector2D<double>(-0.17, -0.3));

        placementSensor.getGps().printValues();
        //sensorManager.getGyroscope().printValues();
    }

    return 1;
    };