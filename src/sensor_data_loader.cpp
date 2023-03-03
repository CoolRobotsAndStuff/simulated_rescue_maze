#include "sensor_data_loader.hpp"
#include <iostream>

namespace simulated_rescue_maze{

void SensorDataLoader::setSensorManager(SensorManager t_sensorManager){
  m_sensorManager = t_sensorManager;
}

// Model update
void SensorDataLoader::updateModel(environment_model::Robot *t_model) {
  // TODO: Implement the model update based on the sensor data
}

}