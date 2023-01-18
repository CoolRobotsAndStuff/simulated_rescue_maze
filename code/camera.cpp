#include <iostream>
#include <webots/Robot.hpp>
#include <opencv2/opencv.hpp>

using namespace webots;
using namespace cv;
using namespace std;

// INITIALIZATIONS
Robot *robot = new Robot();
int timeStep = (int)robot->getBasicTimeStep();      // Set the time step for the simulation

// Camera Initialization
Camera *cam = robot->getCamera("camera1");
cam->enable(timeStep);


class camera {
    public:
        int image;
    
    void get_image() {
          Mat opencv_image = cam.get_image();
          cv::imshow("CameraView", opencv_image);
      }  
};

int main() {

  while (robot->step(timeStep) != -1) {

  camera myCamera;

  myCamera.get_image();
  }
    
  delete robot;
  return 0;
}