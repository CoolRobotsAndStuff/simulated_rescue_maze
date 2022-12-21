#include <iostream>
#include <opencv2/opencv.hpp> // Include OpenCV library
#include <webots/Robot.hpp>
#include <webots/Camera.hpp>

using namespace webots;
using namespace cv;

int main(int argc, char **argv) {

  Robot *robot = new Robot();

  int timeStep = (int)robot->getBasicTimeStep();
 
  Camera *cam = robot->getCamera("camera1");
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