#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/Camera.hpp>
#include <webots/Emitter.hpp>
#include <webots/GPS.hpp>
#include <opencv2/opencv.hpp>
#include <Python.h>
#include "numpy/arrayobject.h" // Include any other Numpy headers, UFuncs for example.
#include <vector>

using namespace webots;
using namespace cv;
using namespace std;

// ROBOT INITIALIZATION
Robot *robot = new Robot();

// UTILITIES
int timeStep = (int)robot->getBasicTimeStep();      // Set the time step for the simulation
float max_velocity = 6.27;                          // Set a maximum velocity time constant

// MOTORS AND SENSORS INITIALIZATIONS
Motor *wheel_left = robot->getMotor("wheel1 motor");     // Create an object to control the left wheel
Motor *wheel_right = robot->getMotor("wheel2 motor");   // Create an object to control the right wheel

DistanceSensor *leftDist, *frontDist, *rightDist; // Objects for left, front, and right distance sensor

Camera *cam = robot->getCamera("camera1"); // Create an object to control the camera
Camera *colorSensor = robot->getCamera("color_sensor"); // Color sensor is a 1 pixel camera

Emitter *emitter; // Used to send messages to supervisor (report victims/hazards)
GPS *gps;

// NUMPY INITILIZATION
import_array();
if (PyErr_Occurred()) {
    std::cerr << "Failed to import numpy Python module(s)." << std::endl;
    return NULL; // Or some suitable return value to indicate failure.
}


// [left wheel speed, right wheel speed]
float speeds[2] = { max_velocity, max_velocity };

void turn_right() {
	// set left wheel speed
	speeds[0] = 0.6 * max_velocity;
	// set right wheel speed
	speeds[1] = -0.2 * max_velocity;
}

void turn_left() {
	// set left wheel speed
	speeds[0] = -0.2 * max_velocity;
	// set right wheel speed
	speeds[1] = 0.6 * max_velocity;
}

void spin() {
	// set left wheel speed
	speeds[0] = 0.6 * max_velocity;
	// set right wheel speed
	speeds[1] = -0.6 * max_velocity;
}

void delay(int ms) {
	float initTime = robot->getTime();	// Store starting time (in seconds)
	while (robot->step(timeStep) != -1) {
		if ((robot->getTime() - initTime) * 1000.0 > ms) { // If time elapsed (converted into ms) is greater than value passed in
			return;
		}
	}
}

int getColor() {
	const unsigned char* image = colorSensor->getImage();	// Grab color sensor camera's image view
	return colorSensor->imageGetGray(image, colorSensor->getWidth(), 0, 0);		// Return grayness of the only pixel (0-255)
}

bool checkVic(void *img) {
    Rect boundRect;
    float contArea, ratio;
    vector<vector<Point>> contours;
    Mat frame(cam->getHeight(), cam->getWidth(), CV_8UC4, img); // Create frame using camera image

    cvtColor(frame, frame, COLOR_BGR2GRAY); // Grayscale image
    threshold(frame, frame, 80, 255, THRESH_BINARY_INV); // Inverse threshold image (0-80 -> white; 80-255 -> black)
    findContours(frame, contours, RETR_TREE, CHAIN_APPROX_SIMPLE); // Find all shapes within thresholded image
    for (int i = 0; i < contours.size(); i++) {
        boundRect = boundingRect(contours[i]); // Draw a rectnagle around shape for width to height ratio
        contArea = fabs(contourArea(Mat(contours[i]))); // Area covered by the shape
        ratio = (float)boundRect.width / boundRect.height; // Calculate width to height ratio
        //if the contour area and width to height ratio are within certain ranges
        if (contArea > 300 && contArea < 1000 && ratio > 0.65 && ratio < 0.95)
            return true;
    }
    return false;
}

void report(char victimType) {
    // Character array to be sent to the supervisor to report victim/hazard
    // First four bytes store robot's x coordinate
    // Second four bytes store robot's z coordinate
    // Last byte stores type of victim
    //     Victims: H, S, U, T
    //     Hazards: F, P, C, O
    wheel_left->setVelocity(0);     // Stop for 1 second
	wheel_right->setVelocity(0);
    delay(1300);
    char message[9];
    int posX = gps->getValues()[0] * 100, posZ = gps->getValues()[2] * 100;
    memcpy(&message[0], &posX, 4);
    memcpy(&message[4], &posZ, 4);
    message[8] = victimType;
    emitter->send(message, 9);
    robot->step(timeStep);
}

void get_image()
{
    image = camera.getImage()
    image = np.frombuffer(image, np.uint8).reshape((camera.getHeight(), camera.getWidth(), 4))
    frame = cv2.cvtColor(image, cv2.COLOR_BGRA2BGR)
    cv2.imshow("frame", frame)
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY) # Grayscale
    cv2.imshow("grayScale", frame)
    cv2.threshold(frame, 80, 255, cv2.THRESH_BINARY) # Threshold
    cv2.imshow("thresh", frame)
    cv2.waitKey(1) # Render imshows on screen
}

void get_flooor_color()
{
	image = colorSensor.getImage() # Step 4: Retrieve the image frame.
    
    # Get the individual RGB color channels from the pixel (0,0)
    # Note that these functions require you to pass the width of the overall image in pixels.
    # Since this is a 1px by 1px color sensor, the width of the image is just 1. 
    r = colorSensor.imageGetRed(image, 1, 0, 0)
    g = colorSensor.imageGetGreen(image, 1, 0, 0)
    b = colorSensor.imageGetBlue(image, 1, 0, 0)
    
    print("r: " + str(r) + " g: " + str(g) + " b: " + str(b))
}

void flatten_image()
{
	tiles_up = 2
	tiles_down = 0
	tiles_side = 1

	minimum_x = tile_resolution * tiles_side
	maximum_x = tile_resolution * (tiles_side + 1)
	minimum_y = tile_resolution * (tiles_up)
	maximum_y = tile_resolution * (tiles_up + 1) - 40

	img_points = np->array(([4,17],[35,6], [31,3], [8,3], ), dtype=np->float32)
	final_points = np->array(([minimum_x,minimum_y],[maximum_x,minimum_y], [maximum_x,maximum_y], [minimum_x,maximum_y], ), dtype=np->float32)
	
	ipm_matrix = cv->getPerspectiveTransform(img_points, final_points, solveMethod=cv.DECOMP_SVD)
        
    final_x = tile_resolution * ((tiles_side * 2) + 1)
    final_y = tile_resolution * (tiles_up + 1 + tiles_down)
        
    final_y_modiff = round(final_y * 1)#0.95

    ipm = cv.warpPerspective(image, ipm_matrix, (final_x, final_y_modiff), flags=cv.INTER_NEAREST)
    ipm = cv.resize(ipm, (final_x, final_y), interpolation=cv.INTER_CUBIC)
}

int main(){
	leftDist = robot->getDistanceSensor("distance sensor3");    // Grab robot's left distance sensor
	leftDist->enable(timeStep);     // Enable the distance sensor

	frontDist = robot->getDistanceSensor("distance sensor2");
	frontDist->enable(timeStep);

	rightDist = robot->getDistanceSensor("distance sensor1");
	rightDist->enable(timeStep);

	cam = robot->getCamera("camera");
	cam->enable(timeStep);

	colorSensor = robot->getCamera("color");
	colorSensor->enable(timeStep);

	emitter = robot->getEmitter("emitter");     // Emitter doesn't need enable

	gps = robot->getGPS("gps");
	gps->enable(timeStep);

	wheel_left->setPosition(numeric_limits<double>::infinity());
	wheel_right->setPosition(numeric_limits<double>::infinity());

	while (robot->step(timeStep) != -1) {
		speeds[0] = max_velocity;
		speeds[1] = max_velocity;

		// Check left and right sensor to avoid walls
		//for sensor on the left, either
		if (leftDist->getValue() < 0.05)
			spin();     // We see a wall on the left, so turn right away from the wall

		if (rightDist->getValue() < 0.05)		// for sensor on the right too
			spin();

		// for front sensor
		if (frontDist->getValue() < 0.05)
			spin();

		// if on black, turn away
		/*
		if (getColor() < 80) {
			spin();
			wheel_left->setVelocity(speeds[0]);
			wheel_right->setVelocity(speeds[1]);
			delay(600);
		}
		*/
	/*
		// if sees victim, report it
		if (checkVic((void*)cam->getImage()))
			report('T'); // Cannot determine type of victim, so always try 'T' for now
	*/
		wheel_left->setVelocity(speeds[0]);		// Send the speed values we have choosen to the robot
		wheel_right->setVelocity(speeds[1]);
	};
}
