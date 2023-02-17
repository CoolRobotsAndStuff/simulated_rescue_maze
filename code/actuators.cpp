#include "actuators.hpp"

#include <webots/Motor.hpp>


namespace simulated_rescue_maze{

void Wheel::initializeValues(){
  m_device->setPosition(INFINITY);
};

void Wheel::setVelocity(float t_velocity) {
  m_device->setVelocity(t_velocity * 6.28);
  m_velocity = t_velocity;
}

float Wheel::getVelocity() {return m_velocity;}

}
