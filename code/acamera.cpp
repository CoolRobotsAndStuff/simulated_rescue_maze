#include <iostream>

#include <webots/Robot.hpp>
#include <webots/Camera.hpp>
#include <opencv2/opencv.hpp>


using namespace webots;
using namespace cv;

int main()
{
    Robot *robot = new Robot();
    int timeStep = (int)robot->getBasicTimeStep();

    Camera *cam = robot->getCamera("camera1");
    cam->enable(timeStep);

    while (robot->step(timeStep) != -1)
    {
        Mat frame(cam->getHeight(), cam->getWidth(), CV_8UC4, (void*)cam->getImage());

        imshow("Frame", frame);

        cvtColor(frame, frame, COLOR_BGR2GRAY);
        imshow("GreyScale", frame);

        threshold(frame,frame,80,255,THRESH_BINARY);
        imshow("Thresh", frame);

        waitKey(1);
    }
}