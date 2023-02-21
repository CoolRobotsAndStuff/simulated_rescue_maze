#include <iostream>
#include <webots/Robot.hpp>
#include <opencv2/opencv.hpp>
#include <webots/Camera.hpp>

using namespace webots;
using namespace cv;
using namespace std;

int main(int argc, char **argv) {

  Class Camara {

  public:
    void get_image() {
      Mat frame(cam->getHeight(), cam->getWidth(), cv_8uc4, (void*)cam->getImage());
      imshow("Frame", frame);
    }
    void RGB_scale() {
      cvtColor(frame, frame, COLOR_BGR2GRAY);
      imshow("greyScale", frame);

    void threshold() {
      threshold(frame, frame, 80, )
    }
    }
  }
  
  Robot *robot = new Robot();

  Camera *cam = robot->getCamera("camera1");

  int timeStep = (int)robot->getBasicTimeStep();

  cam->enable(timeStep);
 
  while (robot->step(timeStep) != -1) {

    Mat frame(cam->getHeight(), cam->getWidth(), CV_8UC4, (void*)cam->getImage());
    
    imshow("frame", frame);
    
    cvtColor(frame,frame,COLOR_BGR2GRAY); // grayscale
    imshow("grayScale", frame);
    
    threshold(frame,frame,80,255,THRESH_BINARY); // threshold
    imshow("thresh", frame);
    
    waitKey(1); // Render imshows on screen
  };

  delete robot;
  return 0;
}