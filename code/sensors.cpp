#include <iostream>

#include "sensors.hpp"
#include "utils.hpp"

namespace simulated_rescue_maze{

// GPS
Vector3D<double> GPS::getPosition() {return m_position;}
Vector3D<double> GPS::getVelocity() {return m_velocity;}
Vector3D<double> GPS::getAcceleration() {return m_acceleration;}
double GPS::getOrientationDegrees() {return m_orientationDegrees;}
double GPS::getOrientationRadians() {return m_orientationRadians;}

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
    std::cout << "est_orientation| " << getOrientationDegrees();
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

    DoubleVector2D coord_diff;
    coord_diff.x = m_position.x - m_previousPosition.x;
    coord_diff.y = m_position.y - m_previousPosition.y;

    auto temp_array = get_rads_and_dist_form_coord_diff(coord_diff);
    if (temp_array[1] > 0.001 or temp_array[1] < -0.001){
        m_orientationRadians = normalize_rads(temp_array[0] + m_orientationOffsetRadians);
        m_orientationDegrees = rads2degs(m_orientationRadians);
    }else {
        m_orientationDegrees = -1.;
        m_orientationRadians = -1.;
    }
}

//Gyro

void Gyroscope::initializeValues(){
    m_angularVelocityRadians.x = m_device->getValues()[0];
    m_angularVelocityRadians.y = m_device->getValues()[2];
    m_angularVelocityRadians.z = m_device->getValues()[1];
}

Vector3D<double> Gyroscope::getOrientationRadians(){return m_orientationRadians;}
Vector3D<double> Gyroscope::getOrientationDegrees(){
    Vector3D<double> orientationDegrees;
    orientationDegrees.x = rads2degs(getOrientationRadians().x);
    orientationDegrees.y = rads2degs(getOrientationRadians().y);
    orientationDegrees.z = rads2degs(getOrientationRadians().z);
    return orientationDegrees;
    }

Vector3D<double> Gyroscope::getAngularVelocityRadians(){return m_angularVelocityRadians;}
Vector3D<double> Gyroscope::getAngularVelocityDegrees(){    
    Vector3D<double> angularVelocityDegrees;
    angularVelocityDegrees.x = rads2degs(getOrientationRadians().x);
    angularVelocityDegrees.y = rads2degs(getOrientationRadians().y);
    angularVelocityDegrees.z = rads2degs(getOrientationRadians().z);
    return angularVelocityDegrees;
    }

Vector3D<double> Gyroscope::getAngularAccelerationDegrees(){return m_angularAccelerationDegrees;}
Vector3D<double> Gyroscope::getAngularAccelerationRadians(){return m_angularAccelerationRadians;}

void Gyroscope::setOrientationDegrees(Vector3D<double> t_orientationDegrees){
    m_orientationRadians.x = degs2rads(t_orientationDegrees.x);
    m_orientationRadians.x = degs2rads(t_orientationDegrees.y);
    m_orientationRadians.x = degs2rads(t_orientationDegrees.z);
}
void Gyroscope::setOrientationRadians(Vector3D<double> t_orientationRadians){
    m_orientationRadians = t_orientationRadians;
}

void Gyroscope::printValues(){
    std::cout << "Orientation:";
    getOrientationDegrees().print();
}

void Gyroscope::update(){
    m_previousAngularVelocityRadians.x = m_angularVelocityRadians.x;
    m_previousAngularVelocityRadians.y = m_angularVelocityRadians.y;
    m_previousAngularVelocityRadians.z = m_angularVelocityRadians.z;

    if (!isnan(m_device->getValues()[0])){
        m_angularVelocityRadians.x = m_device->getValues()[0];
    };
    if (!isnan(m_device->getValues()[2])){
        m_angularVelocityRadians.y = m_device->getValues()[2];
    };
    if (!isnan(m_device->getValues()[1])){
        m_angularVelocityRadians.z = m_device->getValues()[1];
    };

    m_angularVelocityDegrees.x = rads2degs(m_device->getValues()[0]);
    m_angularVelocityDegrees.y = rads2degs(m_device->getValues()[2]);
    m_angularVelocityDegrees.z = rads2degs(m_device->getValues()[1]);

    m_orientationRadians.x = normalize_rads((m_orientationRadians.x + m_angularVelocityRadians.x * m_timeStepSeconds));
    m_orientationRadians.y = normalize_rads((m_orientationRadians.y + m_angularVelocityRadians.y * m_timeStepSeconds));
    m_orientationRadians.z = normalize_rads((m_orientationRadians.z + m_angularVelocityRadians.z * m_timeStepSeconds));

    m_orientationDegrees.x = rads2degs(m_orientationRadians.x);
    m_orientationDegrees.y = rads2degs(m_orientationRadians.y);
    m_orientationDegrees.z = rads2degs(m_orientationRadians.z);

    m_angularAccelerationRadians.x = m_angularVelocityRadians.x -  m_previousAngularVelocityRadians.x;
    m_angularAccelerationRadians.y = m_angularVelocityRadians.y -  m_previousAngularVelocityRadians.y;
    m_angularAccelerationRadians.z = m_angularVelocityRadians.z -  m_previousAngularVelocityRadians.z;

    m_angularAccelerationDegrees.x = rads2degs(m_angularAccelerationRadians.x);
    m_angularAccelerationDegrees.y = rads2degs(m_angularAccelerationRadians.y);
    m_angularAccelerationDegrees.z = rads2degs(m_angularAccelerationRadians.z);
}

//SensorManager

SensorManager::SensorManager(webots::Robot *robot, int time_step){
    gps.init(robot->getGPS("gps"), time_step);
    gyroscope.init(robot->getGyro("gyro"), time_step);
}

void SensorManager::update(){
    gps.update();
    gyroscope.update();
    if (gyroscope.angular_velocity.z < 10 and gyroscope.angular_velocity.z > -10 and gps.m_orientation != -1.){
        std::cout << "USING GPS" << std::endl;
        gyroscope.orientation.z = gps.m_orientation;
        gyroscope.orientation_rads.z = gps.m_orientationRadians;
    }   
}

}