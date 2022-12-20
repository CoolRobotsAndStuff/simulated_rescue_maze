#include <iostream>
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/Camera.hpp>
#include <webots/Emitter.hpp>
#include <webots/GPS.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

using namespace webots;
using namespace cv;
using namespace std;

///////////////////////////////////////////// MAIN /////////////////////////////////////////////
int main(int argc, char **argv) 
{
	Robot *robot = new Robot();

	int timeStep = (int)robot->getBasicTimeStep();

	Camera *colorSensor;
	// Camera* colorSensor = robot->getCamera("color");
	// colorSensor->enable(timeStep);
	
	colorSensor = robot->getCamera("color");
	colorSensor->enable(timeStep);

	while (robot->step(timeStep) != -1) 
	{
		const unsigned char* image = colorSensor->getImage();
		double r;
		double g;
		double b;

		r = colorSensor->imageGetRed(image, 1, 0, 0);
		g = colorSensor->imageGetGreen(image, 1, 0, 0);
		b = colorSensor->imageGetBlue(image, 1, 0, 0);

		cout << "Red: " << r << endl << "Green: " << g << endl << "Blue: " << b << endl;
	}
}