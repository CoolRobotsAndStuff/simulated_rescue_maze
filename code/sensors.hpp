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
  void printValues();
  void initializeValues();

  Vector3D<double> getPosition();
  Vector3D<double> getVelocity();
  Vector3D<double> getAcceleration();
  double getOrientationDegrees();
  double getOrientationRadians();

 private:
  Vector3D<double> m_position;
  Vector3D<double> m_previousPosition;
  Vector3D<double> m_velocity;
  Vector3D<double> m_previousVelocity;
  Vector3D<double> m_acceleration;
  double m_orientationOffsetRadians = M_PI;
  double m_orientationDegrees;
  double m_orientationRadians;
};

class Gyroscope : public Device<webots::Gyro>{
 public:
  Vector3D<double> getOrientationDegrees();
  Vector3D<double> getOrientationRadians();
  Vector3D<double> getAngularVelocityDegrees();
  Vector3D<double> getAngularVelocityRadians();
  Vector3D<double> getAngularAccelerationDegrees();
  Vector3D<double> getAngularAccelerationRadians();

  void setOrientationDegrees(Vector3D<double> t_orientationDegrees);
  void setOrientationRadians(Vector3D<double> t_orientationRadians);

  void update();
  void initializeValues();
  void printValues();

 private:
  Vector3D<double> m_orientationRadians;
  Vector3D<double> m_orientationDegrees;
  Vector3D<double> m_previousAngularVelocityRadians;
  Vector3D<double> m_angularVelocityRadians;
  Vector3D<double> m_angularVelocityDegrees;
  Vector3D<double> m_angularAccelerationRadians;
  Vector3D<double> m_angularAccelerationDegrees;
};


class SensorManager{
 public:
  SensorManager(webots::Robot *robot, int timeStepMilliseconds);

  GPS getGps();
  Gyroscope getGyroscope();

  void setTimeStep(int timeStepMilliseconds);
  void setRobot(webots::Robot *robot);
  
  void update();

 private:
  GPS m_gps;
  Gyroscope m_gyroscope;
};
    
}
