#pragma once

#include <webots/Motor.hpp>

namespace actuators{
class Motor{
 public:
  Motor(webots::Motor *motor_device, int time_step);
  void setVelocity(float input_velocity);
  float getVelocity();

 private:
  double m_timeStepSeconds;
  float m_velocity;
  webots::Motor *m_device;

};

}