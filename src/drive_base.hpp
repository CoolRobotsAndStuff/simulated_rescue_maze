#include "actuators.hpp"
#include "corrector.hpp"

namespace simulated_rescue_maze{

class DriveBase{
  public:
    DriveBase(){}
    DriveBase(Wheel t_rightWheel, Wheel t_leftWheel){
      setWheels(t_rightWheel, t_leftWheel);
    }

    void setWheels(Wheel t_rightWheel, Wheel t_leftWheel){
      m_rotationManager.setWheels(t_rightWheel, t_leftWheel);
      m_movementManager.setWheels(t_rightWheel, t_leftWheel);
    }

    void setRotationToDegreesManager(RotationToAngleManager t_rotationManager){
      m_rotationManager = t_rotationManager;
    }

    void setMovementToCoordinatesManager(MovementToCoordinatesManager t_movementManager){
      m_movementManager = t_movementManager;
    }

    void setCurrentCoordinates(Vector2D<double> t_currentCoordinates){
      m_movementManager.setCurrentCoordinates(t_currentCoordinates);
    }

    void setCurrentAngle(Angle t_currentAngle){
      m_rotationManager.setCurrentAngle(t_currentAngle);
      m_movementManager.setCurrentAngle(t_currentAngle);
    }

    void moveToCoordinates(Vector2D<double> t_coordinates){
      m_movementManager.moveToCoordinates(t_coordinates);
    }

    void rotateToDegrees(Angle t_angle, RotationToAngleManager::Direction t_direction){
      m_rotationManager.rotateToAngle(t_angle, t_direction);
    };

  private:
    RotationToAngleManager m_rotationManager = RotationToAngleManager();
    MovementToCoordinatesManager m_movementManager = MovementToCoordinatesManager();
};



}