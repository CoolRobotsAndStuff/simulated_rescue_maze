#include <iostream>
#include "sensors.h"
#include <cmath>
#include "utils.h"

using namespace std;
using namespace sensors;

GPS::GPS(webots::GPS *gps_device, int time_step){
    time_step_s = time_step * 0.001;
    device = gps_device;
    device->enable(time_step);
    position.x = device->getValues()[0];
    position.y = device->getValues()[1];
    position.z = device->getValues()[2];

    velocity.x = 0; velocity.y = 0; velocity.z = 0;

        
    }

void GPS::print_values(){
    cout << "position    | x: " << position.x << " y: " << position.y << " z: " << position.z << endl; // Print out the values of the sensor
    cout << "velocity    | x: " << velocity.x << " y: " << velocity.y << " z: " << velocity.z << endl;
    cout << "acceleration| x: " << acceleration.x << " y: " << acceleration.y << " z: " << acceleration.z << endl;
    
    }

void GPS::update(){
    previous_position.x = position.x;
    previous_position.y = position.y;
    previous_position.z = position.z;

    position.x = device->getValues()[0];
    position.y = device->getValues()[1];
    position.z = device->getValues()[2];

    previous_velocity.x = velocity.x;
    previous_velocity.y = velocity.y;
    previous_velocity.z = velocity.z;

    velocity.x = (position.x - previous_position.x) / time_step_s;
    velocity.y = (position.y - previous_position.y) / time_step_s;
    velocity.z = (position.z - previous_position.z) / time_step_s;

    acceleration.x = velocity.x - previous_velocity.x;
    acceleration.y = velocity.y - previous_velocity.y;
    acceleration.z = velocity.z - previous_velocity.z;
}


Gyroscope::Gyroscope(webots::Gyro *gyro_device, int time_step){
    time_step_s = time_step * 0.001;
    device = gyro_device;
    device->enable(time_step);


    angular_velocity_rads.x = device->getValues()[0];
    angular_velocity_rads.y = device->getValues()[1];
    angular_velocity_rads.z = device->getValues()[2];

    }

void Gyroscope::print_values(bool convert_to_degs=false){
    if (convert_to_degs){
        cout << "orientation         | x: " << orientation.x << " y: " << orientation.y << " z: " << orientation.z << endl; // Print out the values of the sensor
        cout << "angular_velocity    | x: " << angular_velocity.x << " y: " << angular_velocity.y << " z: " << angular_velocity.z << endl;
        cout << "angular_acceleration| x: " << angular_acceleration.x << " y: " << angular_acceleration.y << " z: " << angular_acceleration.z << endl;

    }else{
        cout << "orientation         | x: " << orientation.x << " y: " << orientation.y << " z: " << orientation.z << endl; // Print out the values of the sensor
        cout << "angular_velocity    | x: " << angular_velocity.x << " y: " << angular_velocity.y << " z: " << angular_velocity.z << endl;
        cout << "angular_acceleration| x: " << angular_acceleration.x << " y: " << angular_acceleration.y << " z: " << angular_acceleration.z << endl;
    }
}

void Gyroscope::update(){
    previous_angular_velocity_rads.x = angular_velocity_rads.x;
    previous_angular_velocity_rads.y = angular_velocity_rads.y;
    previous_angular_velocity_rads.z = angular_velocity_rads.z;

    angular_velocity_rads.x = device->getValues()[0];
    angular_velocity_rads.y = device->getValues()[1];
    angular_velocity_rads.z = device->getValues()[2];

    angular_velocity.x = rads2degs(device->getValues()[0]);
    angular_velocity.y = rads2degs(device->getValues()[1]);
    angular_velocity.z = rads2degs(device->getValues()[2]);

    orientation_rads.x = normalize_rads((orientation_rads.x + angular_velocity_rads.x * time_step_s));
    orientation_rads.y = normalize_rads((orientation_rads.y + angular_velocity_rads.y * time_step_s));
    orientation_rads.z = normalize_rads((orientation_rads.z + angular_velocity_rads.z * time_step_s));

    orientation.x = rads2degs(orientation_rads.x);
    orientation.y = rads2degs(orientation_rads.y);
    orientation.z = rads2degs(orientation_rads.z);

    angular_acceleration_rads.x = angular_velocity_rads.x - previous_angular_velocity_rads.x;
    angular_acceleration_rads.y = angular_velocity_rads.y - previous_angular_velocity_rads.y;
    angular_acceleration_rads.z = angular_velocity_rads.z - previous_angular_velocity_rads.z;

    angular_acceleration.x = rads2degs(angular_acceleration_rads.x);
    angular_acceleration.y = rads2degs(angular_acceleration_rads.y);
    angular_acceleration.z = rads2degs(angular_acceleration_rads.z);
}