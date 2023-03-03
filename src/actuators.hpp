#pragma once

#include <webots/Motor.hpp>

#include "device.hpp"

namespace simulated_rescue_maze{
class Wheel : public Device<webots::Motor>{
 public:

  void setVelocity(float t_velocity);
  float getVelocity();

  void initializeValues();

 private:
  float m_velocity;
};

}