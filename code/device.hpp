#pragma once

#include <webots/GPS.hpp>
#include <webots/Gyro.hpp>
#include <webots/Camera.hpp>
#include <webots/Accelerometer.hpp>
#include <webots/Emitter.hpp>
#include <webots/Receiver.hpp>
#include <webots/Lidar.hpp>
#include <webots/Motor.hpp>

namespace simulated_rescue_maze {

template <class WebotsDevice>
class Device{
 public:
  virtual void update();
  
  virtual void printValues();

  virtual void setTimeStep(int t_timeStepMilliseconds);
  
  virtual void setDevice(WebotsDevice *t_device);

  virtual void enableDevice(int t_timeStepMilliseconds);

  virtual void disableDevice();

  virtual void initializeValues();

 protected:
  WebotsDevice *m_device;
  int t_StepMilliseconds;

};

}
