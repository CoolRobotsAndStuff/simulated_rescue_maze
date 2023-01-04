#include <iostream>
#include "corrector.hpp"
#include "utils.hpp"
#include <algorithm>

AngleRotator::AngleRotator(){}
AngleRotator::AngleRotator(double error_margin, double min_velocity, double max_velocity, double min_velocity_cap, double max_velocity_cap){
    init(error_margin, min_velocity, max_velocity, min_velocity_cap, max_velocity_cap);
}

void AngleRotator::init(double error_magin, double min_velocity, double max_velocity, double min_velocity_cap, double max_velocity_cap){
    this->error_margin = error_magin;
    this->min_velocity = min_velocity;
    this->max_velocity = max_velocity;
    this->min_velocity_cap = min_velocity_cap;
    this->max_velocity_cap = max_velocity_cap;
}

void AngleRotator::set_current_angle(double angle){
    current_angle = angle;
}

string AngleRotator::get_direction(double angle, string direction){
    if (direction == "closest"){
        double angle_difference =  current_angle - angle;
        std::cout << "angle_difference=" << angle_difference << std::endl;
        if ((180 > angle_difference and angle_difference > 0) or angle_difference < -180){
            return "right";
        } else{
            return "left";
        }

    } else if (direction == "farthest"){
        double angle_difference =  start_angle - angle;
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
        start_angle = angle;
        is_first_time = false;
    }

    double diff = current_angle - angle;
    double move_diff = max(current_angle, angle) - min(current_angle, angle);

    if (move_diff < error_margin){
        return DifferentialVelocities((float)0, (float)0);
    }

    if (diff > 180 or diff < -180){
        move_diff = 360 - move_diff;
    }
            

    double velocity = change_double_range(move_diff, 0, 90, min_velocity, max_velocity);

    velocity = min(velocity, max_velocity_cap);
    velocity = max(velocity, min_velocity_cap);

    string final_direction = get_direction(angle, direction);

    std::cout << "final_direction = " << final_direction << std::endl;

    if (final_direction == (string)"right"){
        return DifferentialVelocities((float)(velocity * -1), (float)(velocity));
    }else {
        return DifferentialVelocities((float)(velocity), (float)(velocity * -1));
    }


}