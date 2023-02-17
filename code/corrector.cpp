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

void RotationToAngleManager::rotateToAngle(Angle t_angle, Direction t_direction){
    t_angle.normalize();

    if (m_isFirstTime){
        m_startAngle = t_angle;
        m_isFirstTime = false;
        m_finishedRotating = false;
    }

    /*
    std::cout << "t_angle = ";
    t_angle.print();
    std::cout << std::endl;

    std::cout << "m_startAngle = ";
    m_startAngle.print();
    std::cout << std::endl;
    */


    Angle diff = m_currentAngle - t_angle;

    
    Angle moveDiff;
    moveDiff.setRadians(
      std::max(m_currentAngle.getRadians(), t_angle.getRadians()) - 
      std::min(m_currentAngle.getRadians(), t_angle.getRadians()));
    

    if (moveDiff < m_errorMargin){
        m_finishedRotating = true;
        m_leftWheel.setVelocity(0);
        m_rightWheel.setVelocity(0);
    }

    if (diff.getDegrees() > 180 or diff.getDegrees() < -180){
        moveDiff = Angle(360, Angle::DEGREES) - moveDiff;
    }



    double velocity = changeValueRange(moveDiff.getDegrees(), 0, 90, m_minVelocity, m_maxVelocity);
  
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

}

/*
AngleRotator::AngleRotator(){}
AngleRotator::AngleRotator(double error_margin, double m_minVelocity, double m_maxVelocity, double minVelocityCap, double max_velocity_cap){
    init(error_margin, m_minVelocity, m_maxVelocity, minVelocityCap, max_velocity_cap);
}

void AngleRotator::init(double error_margin, double m_minVelocity, double m_maxVelocity, double minVelocityCap, double max_velocity_cap){
    this->error_margin = error_margin;
    this->m_minVelocity = m_minVelocity;
    this->m_maxVelocity = m_maxVelocity;
    this->minVelocityCap = minVelocityCap;
    this->max_velocity_cap = max_velocity_cap;
}

void AngleRotator::set_current_angle(double angle){
    m_currentAngle = angle;
}

string AngleRotator::get_direction(double angle, string direction){
    if (direction == "closest"){
        double angle_difference =  m_currentAngle - angle;
        //std::cout << "angle_difference=" << angle_difference << std::endl;
        if ((180 > angle_difference and angle_difference > 0) or angle_difference < -180){
            return "right";
        } else{
            return "left";
        }

    } else if (direction == "farthest"){
        double angle_difference =  m_startAngle - angle;
        if ((180 > angle_difference and angle_difference > 0) or angle_difference < -180){
            return "left";
        } 
        else {
            return "right";
        }
    } 

    else if (direction == "clockwise"){return "right";}
    else if (direction == "counterclockwise"){return "left";}
    
    else {return direction;}

}

DifferentialVelocities AngleRotator::rotate_to_angle(double angle, string direction="closest"){
    if (is_first_time){
        m_startAngle = angle;
        is_first_time = false;
    }

    double diff = m_currentAngle - angle;
    double move_diff = max(m_currentAngle, angle) - min(m_currentAngle, angle);

    if (move_diff < error_margin){
        return DifferentialVelocities((float)0, (float)0);
    }

    if (diff > 180 or diff < -180){
        move_diff = 360 - move_diff;
    }
            

    double velocity = change_double_range(move_diff, 0, 90, m_minVelocity, m_maxVelocity);

    velocity = min(velocity, max_velocity_cap);
    velocity = max(velocity, minVelocityCap);

    string final_direction = get_direction(angle, direction);

    //std::cout << "final_direction = " << final_direction << std::endl;

    if (final_direction == (string)"right"){
        return DifferentialVelocities((float)(velocity * -1), (float)(velocity));
    }else {
        return DifferentialVelocities((float)(velocity), (float)(velocity * -1));
    }


}

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