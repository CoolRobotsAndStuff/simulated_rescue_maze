#include "actuators.hpp"

#include <webots/Motor.hpp>

using namespace actuators;

Motor::Motor(webots::Motor *motor_device, int time_step) {
  m_timeStepSeconds = time_step * 0.001;
  m_device = motor_device;
  m_device->setPosition(INFINITY);
}

void Motor::setVelocity(float t_velocity) {
  m_device->setVelocity(t_velocity * 6.28);
  m_velocity = t_velocity;
}

float Motor::getVelocity() {return m_velocity;}