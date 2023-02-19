#include <iostream>
#include <cstdlib>

#include "sensors.hpp"
#include "utils.hpp"

namespace simulated_rescue_maze{

// GPS
Vector3D<double> GPS::getPosition() {return m_position;}
Vector3D<double> GPS::getVelocity() {return m_velocity;}
Vector3D<double> GPS::getAcceleration() {return m_acceleration;}
Angle GPS::getOrientation() {return m_orientation;}
bool GPS::isAbleToCalculateOrientation() {return m_isAbleToCalculateOrientation;}

void GPS::enableDevice(){
  m_device->enable(m_timeStepMilliseconds);
}
void GPS::disableDevice(){
  m_device->disable();
}

void GPS::initializeValues(){
  m_position.x = m_device->getValues()[0];
  m_position.y = m_device->getValues()[2];
  m_position.z = m_device->getValues()[1];

  m_velocity.x = 0; m_velocity.y = 0; m_velocity.z = 0;
}

void GPS::printValues(){
  std::cout << "position    | ";
  m_position.print();
  std::cout << "velocity    | ";
  m_velocity.print();
  std::cout << "acceleration| ";
  m_acceleration.print();
  std::cout << "est. orientation| " << getOrientation().getDegrees() << std::endl;
  std::cout << "able to get orientation| " << m_isAbleToCalculateOrientation << std::endl;//isAbleToCalculateOrientation() << std::endl;


  //std::cout << "timeStep seconds| ";
  //std::cout << m_timeStepSeconds << std::endl;
}

void GPS::update(){
  m_previousPosition = m_position;

  m_position.x = m_device->getValues()[0];
  m_position.y = m_device->getValues()[2];
  m_position.z = m_device->getValues()[1];

  m_previousVelocity = m_velocity;

  m_velocity = (m_position - m_previousPosition) / m_timeStepSeconds;

  m_acceleration = m_velocity - m_previousVelocity;

  Vector2D<double> position2D(m_position.x, m_position.y);
  Vector2D<double> previousPosition2D(m_previousPosition.x, m_previousPosition.y);

  Angle angleToPreviousPosition = position2D.getSlopeToVector(previousPosition2D);
  double distanceToPreviousPosition = position2D.getDistanceToVector(previousPosition2D);

  std::cout << "distance to prev position" << distanceToPreviousPosition << std::endl;

  if (fabs(distanceToPreviousPosition) > 0.0001){
    m_isAbleToCalculateOrientation = true;
    m_orientation = angleToPreviousPosition +  m_orientationOffset;
    m_orientation.normalize();

  }else {
    m_isAbleToCalculateOrientation = false;
  }
}

//Gyro

void Gyroscope::enableDevice(){
  m_device->enable(m_timeStepMilliseconds);
}
void Gyroscope::disableDevice(){
  m_device->disable();
}


void Gyroscope::initializeValues(){
  m_angularVelocity.x.setRadians(m_device->getValues()[0]);
  m_angularVelocity.y.setRadians(m_device->getValues()[2]);
  m_angularVelocity.z.setRadians(m_device->getValues()[1]);
}

Vector3D<Angle> Gyroscope::getOrientation() { return m_orientation; }
Vector3D<Angle> Gyroscope::getAngularVelocity() { return m_angularVelocity; }
Vector3D<Angle> Gyroscope::getAngularAcceleration() { return m_angularAcceleration; }

void Gyroscope::setOrientation(Vector3D<Angle> t_orientation) { m_orientation = t_orientation; }

void Gyroscope::printValues(){
  std::cout << "Orientation: ";
  getOrientation().x.print();
  std::cout << ", ";
  getOrientation().y.print();
  std::cout << ", ";
  getOrientation().z.print();
  std::cout << std::endl;

  std::cout << "Angular Velocity: ";
  getAngularVelocity().x.print();
  std::cout << ", ";
  getAngularVelocity().y.print();
  std::cout << ", ";
  getAngularVelocity().z.print();
  std::cout << std::endl;
  

  std::cout << "Angular Acceleration: ";
  getAngularAcceleration().x.print();
  std::cout << ", ";
  getAngularAcceleration().y.print();
  std::cout << ", ";
  getAngularAcceleration().z.print();
  std::cout << std::endl;

}

void Gyroscope::update(){
  m_previousAngularVelocity = m_angularVelocity;

  if (!std::isnan(m_device->getValues()[0])){
    m_angularVelocity.x.setRadians(m_device->getValues()[0]);
  };
  if (!std::isnan(m_device->getValues()[2])){
    m_angularVelocity.y.setRadians(m_device->getValues()[2]);
  };
  if (!std::isnan(m_device->getValues()[1])){
    m_angularVelocity.z.setRadians(m_device->getValues()[1]);
  };

  m_orientation = m_orientation + m_angularVelocity * m_timeStepSeconds;

  m_orientation.x.normalize();
  m_orientation.y.normalize();
  m_orientation.z.normalize();

  m_angularAcceleration = m_angularVelocity - m_angularAcceleration;
}

// Placement Sensor

PlacementSensor::PlacementSensor(){};

void PlacementSensor::setGpsDevice(webots::GPS *t_gps){ 
  m_gps.setDevice(t_gps); 
}
void PlacementSensor::setGyroscopeDevice(webots::Gyro *t_gyroscope) { 
  m_gyroscope.setDevice(t_gyroscope);
}

GPS PlacementSensor::getGps() { return m_gps; }
Gyroscope PlacementSensor::getGyroscope() { return m_gyroscope; }

Transform3D<double> PlacementSensor::getPlacement() { return m_placement; }
void PlacementSensor::setPlacement(Transform3D<double> t_placement){ m_placement = t_placement; }

void PlacementSensor::setTimeStep(int t_timeStepMilliseconds){
  m_gps.setTimeStep(t_timeStepMilliseconds);
  m_gyroscope.setTimeStep(t_timeStepMilliseconds);
}

void PlacementSensor::enable() {
  m_gps.enableDevice();
  m_gyroscope.enableDevice();
}
void PlacementSensor::disable(){
  m_gps.disableDevice();
  m_gyroscope.disableDevice();
}

void PlacementSensor::initializeValues(){
  m_gps.initializeValues();
  m_gyroscope.initializeValues();
}

void PlacementSensor::update() {
  m_gps.update();
  m_gyroscope.update();

  m_placement.position = m_gps.getPosition();
  m_placement.velocity = m_gps.getVelocity();
  m_placement.acceleration = m_gps.getAcceleration();


  m_placement.orientation = m_gyroscope.getOrientation();
  if (m_gps.isAbleToCalculateOrientation() and isGoingStraight()) {
    m_placement.orientation.z = m_gps.getOrientation();
    m_gyroscope.setOrientation(m_placement.orientation);
  } 

  m_placement.angularVelocity = m_gyroscope.getAngularVelocity();
  m_placement.angularAcceleration = m_gyroscope.getAngularAcceleration();
}

void PlacementSensor::printValues(){
  std::cout << "----------\nPlacement\n";
  m_gps.printValues();
  m_gyroscope.printValues();
}

bool PlacementSensor::isGoingStraight(){
  return (fabs(m_placement.angularVelocity.z.getDegrees()) < 0.1);
}






// Sensor Manager


// Sensor accessors
GPS SensorManager::getGps() { return m_gps; }
Gyroscope SensorManager::getGyroscope() { return m_gyroscope; }

// Sensor initialization
void SensorManager::initializeSensors(webots::Robot *t_robot, int t_timeStepMilliseconds) {
  m_gps.setDevice(t_robot->getGPS("gps"));
  m_gps.setTimeStep(t_timeStepMilliseconds);
  m_gps.enableDevice();
  m_gps.initializeValues();

  m_gyroscope.setDevice(t_robot->getGyro("gyro"));
  m_gyroscope.setTimeStep(t_timeStepMilliseconds);
  m_gyroscope.enableDevice();
  m_gyroscope.initializeValues();
}

// Sensor updates
void SensorManager::updateSensors() {
  m_gps.update();
  m_gyroscope.update();
}

}