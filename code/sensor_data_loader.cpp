#include "sensor_data_loader.hpp"

env_model::Robot SensorDataLoader::load_sensor_data(env_model::Robot input_model, sensors::SensorManager sensors){
    input_model.position = sensors.gps.position;
    input_model.velocity = sensors.gps.velocity;
    input_model.acceleration = sensors.gps.acceleration;

    input_model.orientation = sensors.gyroscope.orientation.y;
    input_model.angular_velocity = sensors.gyroscope.angular_velocity.y;
    input_model.angular_acceleration = sensors.gyroscope.angular_acceleration.y;

    return input_model;
};