#include <iostream>
#include <opencv2/opencv.hpp> // Include OpenCV library
#include <webots/Robot.hpp>
#include <webots/Camera.hpp>

using namespace webots;
using namespace cv;

int main(int argc, char **argv) {

  Robot *robot = new Robot();

  Camera *cam = robot->getCamera("camera2");

  int timeStep = (int)robot->getBasicTimeStep();
 
  cam->enable(timeStep);
 
  while (robot->step(timeStep) != -1) {

    /*
     * Convert the camera image into an openCV Mat. You must pass in the height
     * and width of the camera in pixels, as well as specify CV_8UC4, meaning that
     * it is in RGBA format.
     */
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