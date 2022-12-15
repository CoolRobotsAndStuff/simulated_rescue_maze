#include "sensors.hpp"
#include "environment_model.hpp"


class SensorDataLoader{
    public:
        env_model::Robot load_sensor_data(env_model::Robot input_model, sensors::SensorManager sensors);
};