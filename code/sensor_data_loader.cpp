#include "sensor_data_loader.hpp"
#include <iostream>

env_model::Robot SensorDataLoader::load_sensor_data(env_model::Robot input_model, sensors::SensorManager sensors){
    input_model.position = sensors.gps.m_position;
    input_model.velocity = sensors.gps.velocity;
    input_model.acceleration = sensors.gps.m_acceleration;

    std::cout << "angular velocity" << sensors.gyroscope.m_angularVelocityDegrees.z << std::endl;

    
    input_model.orientation = sensors.gyroscope.m_orientationDegrees.z;
    input_model.angular_velocity = sensors.gyroscope.m_angularVelocityDegrees.z;
    input_model.angular_acceleration = sensors.gyroscope.m_angularAccelerationDegrees.z;

    return input_model;
};