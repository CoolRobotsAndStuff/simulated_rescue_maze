#pragma once

#include <string.h>

#include <cmath>

#include <webots/GPS.hpp>
#include <webots/Gyro.hpp>
#include <webots/Robot.hpp>

#include "device.hpp"
#include "generic_data_structures.hpp"

namespace simulated_rescue_maze{

class GPS : public Device<webots::GPS>{
 public:
  void update();
  void initializeValues();
  void printValues();
  

  Vector3D<double> getPosition();
  Vector3D<double> getVelocity();
  Vector3D<double> getAcceleration();

  Angle getOrientation();

  bool isAbleToCalculateOrientation();

  virtual void enableDevice();
  virtual void disableDevice();

  Vector3D<double> m_position;
  Vector3D<double> m_previousPosition;
  Vector3D<double> m_velocity;
  Vector3D<double> m_previousVelocity;
  Vector3D<double> m_acceleration;
  Angle m_orientationOffset = Angle(M_PI, Angle::RADIANS);
  Angle m_orientation;
  bool m_isAbleToCalculateOrientation;
};

class Gyroscope : public Device<webots::Gyro>{
 public:
  Vector3D<Angle> getOrientation();
  Vector3D<Angle> getAngularVelocity();
  Vector3D<Angle> getAngularAcceleration();

  void setOrientation(Vector3D<Angle> t_orientation);

  virtual void enableDevice();
  virtual void disableDevice();

  void update();
  void initializeValues();
  void printValues();

 private:
  Vector3D<Angle> m_orientation;
  Vector3D<Angle> m_previousAngularVelocity;
  Vector3D<Angle> m_angularVelocity;
  Vector3D<Angle> m_angularAcceleration;
};

class SensorManager {
 public:
  GPS getGps();
  Gyroscope getGyroscope();
  
  void updateSensors();

  void initializeSensors(webots::Robot *t_robot, int t_timeStepMilliseconds);

 private:
  GPS m_gps;
  Gyroscope m_gyroscope;


};
}