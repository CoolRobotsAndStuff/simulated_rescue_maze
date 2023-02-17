#include <string>
#include <limits>

#include "generic_data_structures.hpp"

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

  bool finishedRotating();

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

  Angle m_errorMargin = Angle(2, Angle::DEGREES);

  Wheel m_rightWheel;
  Wheel m_leftWheel;

  Direction getDirection(Angle t_angle, Direction t_criterion = CLOSEST);

};
}

/*
class CoordinatesMover{
    public:
        Vector2D<double> current_position;

        double min_velocity;
        double max_velocity;

        double min_velocity_cap;
        double max_velocity_cap;

        double error_margin;

        CoordinatesMover();
        CoordinatesMover(double error_margin, double min_velocity, double max_velocity, double min_velocity_cap = 0, double max_velocity_cap = numeric_limits<double>::infinity());
        
        DifferentialVelocities move_to_position(Vector3D<float> position, AngleRotator angle_rotator);
        void init(double error_margin, double min_velocity, double max_velocity, double min_velocity_cap = 0, double max_velocity_cap = numeric_limits<double>::infinity());
        void set_current_position(Vector3D<double> position);

};
}

*/