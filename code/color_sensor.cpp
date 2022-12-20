#include <iostream>

#include <webots/Robot.hpp>
#include <webots/Camera.hpp> // Step 1: Include Camera header

using namespace webots;
using namespace std;

int main(int argc, char **argv) {

  Robot *robot = new Robot();
  
  Camera* colorSensor = robot->getCamera("colour_sensor"); // Step 2: Retrieve the sensor, named "colour_sensor", from the robot. Note that the sensor name may differ between robots.

  int timeStep = (int)robot->getBasicTimeStep();
  
  colorSensor->enable(timeStep); // Step 3: Enable the sensor, using the timestep as the update rate

  robot->step(timeStep);
  
  while (robot->step(timeStep) != -1) {
  
    const unsigned char* image = colorSensor->getImage(); // Step 4: Retrieve the image frame.
    
    // Get the individual RGB color channels from the pixel (0,0)
    // Note that these functions require you to pass the width of the overall image in pixels.
    // Since this is a 1px by 1px color sensor, the width of the image is just 1. 
    int r = colorSensor->imageGetRed(image, 1, 0, 0);
    int g = colorSensor->imageGetGreen(image, 1, 0, 0);
    int b = colorSensor->imageGetBlue(image, 1, 0, 0);
    
    cout << "r: " << r << " g: " << g << " b: " << b << endl;
  }
    
  delete robot;
  return 0;
}