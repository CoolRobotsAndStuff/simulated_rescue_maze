#pragma once

namespace simulated_rescue_maze {

template <class WebotsDevice>
class Device{
 public:
  virtual void update(){};
  
  virtual void printValues(){};

  virtual void setTimeStep(int t_timeStepMilliseconds){
    m_timeStepMilliseconds = t_timeStepMilliseconds;
    m_timeStepSeconds = double(t_timeStepMilliseconds) / 1000.;
  }
  
  virtual void setDevice(WebotsDevice *t_device){
    m_device = t_device;
  };

  virtual void initializeValues(){};

 protected:
  WebotsDevice *m_device;
  int m_timeStepMilliseconds;
  double m_timeStepSeconds;

};

}
