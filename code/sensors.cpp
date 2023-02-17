#include <iostream>

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
    std::cout << "est_orientation| " << getOrientation().getDegrees() << std::endl;
    std::cout << "timeStep seconds| ";
    std::cout << m_timeStepSeconds << std::endl;
}

void GPS::update(){
    m_previousPosition.x = m_position.x;
    m_previousPosition.y = m_position.y;
    m_previousPosition.z = m_position.z;

    m_position.x = m_device->getValues()[0];
    m_position.y = m_device->getValues()[2];
    m_position.z = m_device->getValues()[1];

    m_previousVelocity.x = m_velocity.x;
    m_previousVelocity.y = m_velocity.y;
    m_previousVelocity.z = m_velocity.z;

    m_velocity.x = (m_position.x - m_previousPosition.x) / m_timeStepSeconds;
    m_velocity.y = (m_position.y - m_previousPosition.y) / m_timeStepSeconds;
    m_velocity.z = (m_position.z - m_previousPosition.z) / m_timeStepSeconds;

    m_acceleration.x = m_velocity.x - m_previousVelocity.x;
    m_acceleration.y = m_velocity.y - m_previousVelocity.y;
    m_acceleration.z = m_velocity.z - m_previousVelocity.z;

    Vector2D<double> coord_diff;
    coord_diff.x = m_position.x - m_previousPosition.x;
    coord_diff.y = m_position.y - m_previousPosition.y;

    auto temp_array = get_rads_and_dist_form_coord_diff(coord_diff);
    if (temp_array[1] > 0.001 or temp_array[1] < -0.001){
        m_isAbleToCalculateOrientation = true;
        m_orientation.setRadians(temp_array[0] + m_orientationOffset.getRadians());
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

    

    m_orientation.x.setRadians(m_orientation.x.getRadians() + m_angularVelocity.x.getRadians() * m_timeStepSeconds);
    m_orientation.y.setRadians(m_orientation.y.getRadians() + m_angularVelocity.y.getRadians() * m_timeStepSeconds);
    m_orientation.z.setRadians(m_orientation.z.getRadians() + m_angularVelocity.z.getRadians() * m_timeStepSeconds);

    m_orientation.x.normalize();
    m_orientation.y.normalize();
    m_orientation.z.normalize();

    m_angularAcceleration.x.setRadians(m_angularVelocity.x.getRadians() -  m_previousAngularVelocity.x.getRadians());
    m_angularAcceleration.y.setRadians(m_angularVelocity.y.getRadians() -  m_previousAngularVelocity.y.getRadians());
    m_angularAcceleration.z.setRadians(m_angularVelocity.z.getRadians() -  m_previousAngularVelocity.z.getRadians());
}


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