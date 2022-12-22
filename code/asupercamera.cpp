#include <iostream>
#include <opencv2/opencv.hpp> // Include OpenCV library
#include <webots/Robot.hpp>
#include <webots/Camera.hpp>

using namespace webots;
using namespace cv;

int main() 
{
  Robot *robot = new Robot();

  Camera *cam = robot->getCamera('theonlycamera');

  int timeStep = (int)robot->getBasicTimeStep();
 
  cam->enable(timeStep);
 
  while (robot->step(timeStep) != -1) 
  {
    Mat frame(cam->getHeight(), cam->getWidth(), CV_8UC4, (void*)cam->getImage());
    
    imshow("frame", frame);
    
    cvtColor(frame,frame,COLOR_BGR2GRAY); // grayscale
    imshow("grayScale", frame);
    
    threshold(frame,frame,80,255,THRESH_BINARY); // threshold
    imshow("thresh", frame);
    
    waitKey(1); // Render imshows on screen
  }
}
