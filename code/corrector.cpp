#include <iostream>
#include <algorithm>

#include "corrector.hpp"

#include "utils.hpp"

namespace simulated_rescue_maze {

RotationToAngleManager::RotationToAngleManager(){}

RotationToAngleManager::RotationToAngleManager(
    Angle t_errorMargin, 
    double t_minVelocity,
    double t_maxVelocity,
    double t_minVelocityCap,
    double t_maxVelocityCap){

  setErrorMargin(t_errorMargin);
  setMinVelocity(t_minVelocity);
  setMaxVelocity(t_maxVelocity);
  setMinVelocityCap(t_minVelocityCap);
  setMaxVelocityCap(t_maxVelocityCap);
}

Angle RotationToAngleManager::getCurrentAngle() { return m_currentAngle; }
void RotationToAngleManager::setCurrentAngle(Angle t_angle) { m_currentAngle = t_angle; }

Angle RotationToAngleManager::getMinVelocity() {return m_minVelocity; }
void RotationToAngleManager::setMinVelocity(double t_minVelocity) { m_minVelocity = t_minVelocity; }

Angle RotationToAngleManager::getMaxVelocity() { return m_maxVelocity; }
void RotationToAngleManager::setMaxVelocity(double t_maxVelocity) { m_maxVelocity = t_maxVelocity; }

Angle RotationToAngleManager::getMinVelocityCap() { return m_minVelocityCap; }
void RotationToAngleManager::setMinVelocityCap(double t_minVelocityCap) { m_minVelocityCap = t_minVelocityCap; }

Angle RotationToAngleManager::getMaxVelocityCap() { return m_maxVelocityCap; }
void RotationToAngleManager::setMaxVelocityCap(double t_maxVelocityCap) { m_maxVelocityCap = t_maxVelocityCap; }

Angle RotationToAngleManager::getErrorMargin() { return m_errorMargin; }
void RotationToAngleManager::setErrorMargin(Angle t_errorMargin) { m_errorMargin = t_errorMargin; }

RotationToAngleManager::Direction RotationToAngleManager::getDirection(Angle t_angle,  Direction t_criterion){
  if (t_criterion == CLOSEST){
    Angle angle_difference =  m_currentAngle - t_angle;
    //std::cout << "angle_difference=" << angle_difference << std::endl;
    if ((Angle(180, Angle::DEGREES) > angle_difference and 
        angle_difference > Angle(0, Angle::DEGREES)) or 
        angle_difference < Angle(-180, Angle::DEGREES)){
      return RIGHT;
    } else{
      return LEFT;
    }

  } else if (t_criterion == FARTHEST){
    Angle angle_difference =  m_startAngle - t_angle;
    if ((Angle(180, Angle::DEGREES) > angle_difference and 
        angle_difference > Angle(0, Angle::DEGREES)) or 
        angle_difference < Angle(-180, Angle::DEGREES)){
      return LEFT;
    } 
    else {
      return RIGHT;
    }
  } 
  
  else {return t_criterion;}
}

void RotationToAngleManager::setWheels(Wheel t_rightWheel, Wheel t_leftWheel){
  m_rightWheel = t_rightWheel;
  m_leftWheel = t_leftWheel;
}

bool RotationToAngleManager::finishedRotating(){
  return m_finishedRotating;
}

bool RotationToAngleManager::isAtAngle(Angle t_angle){
  return m_currentAngle.getAbsoluteDistanceTo(t_angle) < m_errorMargin;

}

void RotationToAngleManager::rotateToAngle(Angle t_angle, Direction t_direction){
  t_angle.normalize();

  if (m_isFirstTime){
    m_startAngle = t_angle;
    m_isFirstTime = false;
    m_finishedRotating = false;
  }

  if (isAtAngle(t_angle)){
    m_finishedRotating = true;
    m_leftWheel.setVelocity(0);
    m_rightWheel.setVelocity(0);
  }

  //Angle diff = m_currentAngle - t_angle;
  Angle absoluteDifference = m_currentAngle.getAbsoluteDistanceTo(t_angle);

  if (absoluteDifference.getDegrees() > 180){
    absoluteDifference = Angle(360, Angle::DEGREES) - absoluteDifference;
  }

  double velocity = changeValueRange(absoluteDifference.getDegrees(), 0, 90, m_minVelocity, m_maxVelocity);

  velocity = std::min(velocity, m_maxVelocityCap);
  velocity = std::max(velocity, m_minVelocityCap);

  Direction finalDirection = getDirection(t_angle, t_direction);

  if (finalDirection == RIGHT){
    m_rightWheel.setVelocity(float(velocity) * -1);
    m_leftWheel.setVelocity(float(velocity));
  }else {
    m_rightWheel.setVelocity(float(velocity));
    m_leftWheel.setVelocity(float(velocity) * -1);
  }

}

// Constructor
MovementToCoordinatesManager::MovementToCoordinatesManager() {
    // Default constructor implementation
}

void MovementToCoordinatesManager::setCurrentAngle(Angle t_angle){
  m_rotationManager.setCurrentAngle(t_angle);
}

Vector2D<double> MovementToCoordinatesManager::getCurrentCoordinates() { return m_currentCoordinates; }
void MovementToCoordinatesManager::setCurrentCoordinates(Vector2D<double> t_currentCoordinates) { m_currentCoordinates = t_currentCoordinates; }

double MovementToCoordinatesManager::getMinVelocity() { return m_minVelocity; }
void MovementToCoordinatesManager::setMinVelocity(double t_minVelocity) { m_minVelocity = t_minVelocity; }

double MovementToCoordinatesManager::getMaxVelocity() { return m_maxVelocity; }
void MovementToCoordinatesManager::setMaxVelocity(double t_maxVelocity) { m_maxVelocity = t_maxVelocity; }

double MovementToCoordinatesManager::getMinVelocityCap() { return m_minVelocityCap; }
void MovementToCoordinatesManager::setMinVelocityCap(double t_minVelocityCap) { m_minVelocityCap = t_minVelocityCap; }

double MovementToCoordinatesManager::getMaxVelocityCap() { return m_maxVelocityCap; }
void MovementToCoordinatesManager::setMaxVelocityCap(double t_maxVelocityCap) { m_maxVelocityCap = t_maxVelocityCap; }

double MovementToCoordinatesManager::getErrorMargin() { return m_errorMargin; }
void MovementToCoordinatesManager::setErrorMargin(double t_errorMargin) { m_errorMargin = t_errorMargin; }


void  MovementToCoordinatesManager::setRotationToAngleManager(RotationToAngleManager t_rotationManager){
  m_rotationManager = t_rotationManager;
  //m_rotationManager.setWheels(m_rightWheel, m_leftWheel);
}

void  MovementToCoordinatesManager::setWheels(Wheel t_rightWheel, Wheel t_leftWheel){
  m_rightWheel = t_rightWheel;
  m_leftWheel = t_leftWheel;
  m_rotationManager.setWheels(t_rightWheel, t_leftWheel);
}

// Move to the specified coordinates
void MovementToCoordinatesManager::moveToCoordinates(Vector2D<double> t_coordinates) {
  Angle angleToCoordinates = m_currentCoordinates.getSlopeToVector(t_coordinates);
  angleToCoordinates.normalize();
  //std::cout << "angle to coordinates: ";
  //angleToCoordinates.print();
  //std::cout << std::endl;
  double distanceToCoordinates = m_currentCoordinates.getDistanceToVector(t_coordinates);
  m_finishedMoving = false;
  if (distanceToCoordinates < m_errorMargin){
    m_rightWheel.setVelocity(0);
    m_leftWheel.setVelocity(0);
    m_finishedMoving = true;
  } else if (m_rotationManager.isAtAngle(angleToCoordinates)){
    m_rightWheel.setVelocity(1);
    m_leftWheel.setVelocity(1);
  } else{
    m_rotationManager.rotateToAngle(angleToCoordinates, RotationToAngleManager::CLOSEST);
  }
}

bool MovementToCoordinatesManager::finishedMoving(){
  return m_finishedMoving;
}

}

/*
CoordinatesMover::CoordinatesMover(){};
CoordinatesMover::CoordinatesMover(double error_margin, double m_minVelocity, double m_maxVelocity, double minVelocityCap, double max_velocity_cap){
    init(error_margin, m_minVelocity, m_maxVelocity, minVelocityCap, max_velocity_cap);
}

void CoordinatesMover::init(double error_magin, double m_minVelocity, double m_maxVelocity, double minVelocityCap, double max_velocity_cap){
    this->error_margin = error_magin;
    this->m_minVelocity = m_minVelocity;
    this->m_maxVelocity = m_maxVelocity;
    this->minVelocityCap = minVelocityCap;
    this->max_velocity_cap = max_velocity_cap;
}

void CoordinatesMover::set_current_position(Vector3D<double> position){
    current_position.x = position.x;
    current_position.y = position.y;
}

DifferentialVelocities CoordinatesMover::move_to_position(Vector3D<float> position, AngleRotator angle_rotator){
    DifferentialVelocities final_velocities(m_maxVelocity, m_maxVelocity);
    
    Vector2D<double> position_2D;
    position_2D.x = position.x;
    position_2D.y = position.y;
    
    auto degs_and_dist = get_degs_and_dist_from_coords(current_position, position_2D);
    double degs = degs_and_dist[0];
    double dist = degs_and_dist[1];

    if (get_shortest_dist_between_degs(angle_rotator.m_currentAngle, degs) > angle_rotator.error_margin)
    {
        return angle_rotator.rotate_to_angle(degs, "closest");
    } 
    else if (dist < error_margin and dist > error_margin * -1){
        return DifferentialVelocities(0., 0.);
    }
    else{
        return final_velocities;
    }

}

*/