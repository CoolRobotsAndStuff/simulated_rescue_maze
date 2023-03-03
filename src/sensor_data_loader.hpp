#include "sensors.hpp"
#include "data_structures/environment_model.hpp"

namespace simulated_rescue_maze{
class SensorDataLoader{
 public:
  void setSensorManager(SensorManager t_sensorManager);

  void updateModel(environment_model::Robot *t_model);

 private:
  SensorManager m_sensorManager;
};
}