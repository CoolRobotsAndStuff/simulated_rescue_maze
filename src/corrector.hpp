#pragma once

#include <string>
#include <limits>

#include "data_structures/generic_data_structures.hpp"

#include "actuators.hpp"

namespace simulated_rescue_maze{

class RotationToAngleManager{
 public:
  enum Direction {RIGHT, LEFT, CLOSEST, FARTHEST};

  RotationToAngleManager();
  RotationToAngleManager(
    Angle t_errorMargin, 
    double t_minVelocity,
    double t_maxVelocity,
    double t_minVelocityCap = 0,
    double t_maxVelocityCap = 1
    );
  
  // Getters and Setters
  Angle getCurrentAngle();
  void setCurrentAngle(Angle t_angle);

  Angle getMinVelocity();
  void setMinVelocity(double t_minVelocity);

  Angle getMaxVelocity();
  void setMaxVelocity(double t_maxVelocity);

  Angle getMinVelocityCap();
  void setMinVelocityCap(double t_minVelocityCap);

  Angle getMaxVelocityCap();
  void setMaxVelocityCap(double t_maxVelocityCap);

  Angle getErrorMargin();
  void setErrorMargin(Angle t_errorMargin);

  void setWheels(Wheel t_rightWheel, Wheel t_leftWheel);

  // Has the robot finished the rotation
  bool finishedRotating();

  bool isAtAngle(Angle t_angle);

  // Rotate to an alngle in the specified direction
  void rotateToAngle(Angle t_angle, Direction t_direction);

 private:
  bool m_finishedRotating;

  bool m_isFirstTime = true;

  Angle m_startAngle;
  Angle m_currentAngle;

  double m_minVelocity = 0;
  double m_maxVelocity = 0.8;

  double m_minVelocityCap = 0;
  double m_maxVelocityCap = 1;

  Angle m_errorMargin = Angle(3, Angle::DEGREES);

  Wheel m_rightWheel;
  Wheel m_leftWheel;

  Direction getDirection(Angle t_angle, Direction t_criterion = CLOSEST);

};


class MovementToCoordinatesManager {
 public:
  // Constructor
  MovementToCoordinatesManager();

  // Move to the specified coordinates
  void moveToCoordinates(Vector2D<double> t_coordinates);

  bool finishedMoving();

  void setCurrentAngle(Angle t_angle);

  Vector2D<double> getCurrentCoordinates();
  void setCurrentCoordinates(Vector2D<double> t_currentCoordinates);

  double getMinVelocity();
  void setMinVelocity(double t_minVelocity);

  double getMaxVelocity();
  void setMaxVelocity(double t_maxVelocity);

  double getMinVelocityCap();
  void setMinVelocityCap(double t_minVelocityCap);

  double getMaxVelocityCap();
  void setMaxVelocityCap(double t_maxVelocityCap);

  double getErrorMargin();
  void setErrorMargin(double t_errorMargin);

  void setRotationToAngleManager(RotationToAngleManager t_rotationManager);

  void setWheels(Wheel t_rightWheel, Wheel t_leftWheel);

 private:
  Wheel m_rightWheel;
  Wheel m_leftWheel;
  
  Vector2D<double> m_currentCoordinates;
  double m_minVelocity = 0;
  double m_maxVelocity = 1;
  double m_minVelocityCap = 0;
  double m_maxVelocityCap = 1;
  double m_errorMargin = 0.001;

  bool m_finishedMoving;

  RotationToAngleManager m_rotationManager = RotationToAngleManager();
};

}