#include "device.hpp"


template <class WebotsDevice>
class simulated_rescue_maze::Device{
 public:
  virtual void update(){};
  
  virtual void printValues(){};

  void setTimeStep(int t_timeStepMilliseconds){
    m_timeStepMilliseconds = t_timeStepMilliseconds;
  }
  
  void setDevice(WebotsDevice *t_device){
    m_device = t_device;
  }

  void enableDevice(int t_timeStepMilliseconds){
    m_device->enable(t_timeStepMilliseconds)
  }

  void disableDevice(){
    m_device->disable()
  };

  virtual void initializeValues(){};

};
