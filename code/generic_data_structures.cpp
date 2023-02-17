#include <iostream>

#include "generic_data_structures.hpp"
#include "utils.hpp"


namespace simulated_rescue_maze{

// Constructors
Angle::Angle() : value(0.0) {}

Angle::Angle(double value, Unit unit) { 
  if (unit == RADIANS) {
    setRadians(value);
  } else if (unit == DEGREES) {
    setDegrees(value);
  }
}

// Setters
void Angle::setRadians(double value) {
  this->value = value;
}

void Angle::setDegrees(double value) {
  this->value = value * M_PI / 180.0;
}

// Getters
double Angle::getRadians() {
  return value;
}

double Angle::getDegrees() {
  return value * 180.0 / M_PI;
}

void Angle::print() {
  std::cout << this->getDegrees();
}

// Normalization
void Angle::normalize() {
  value = fmod(value, 2.0 * M_PI);
  if (value < 0.0) {
    value += 2.0 * M_PI;
  }
}

DifferentialVelocities::DifferentialVelocities(){}

DifferentialVelocities::DifferentialVelocities(float left, float right){
    set_velocities(left, right);
}

std::array<float, 2> DifferentialVelocities::get_array(){
    return std::array<float, 2>{left, right};
};

void DifferentialVelocities::set_array(std::array<float, 2> input_array){
    left = input_array[0];
    right = input_array[1];
};

void DifferentialVelocities::set_velocities(float left, float right){
    this->left = left;
    this->right = right;
}

/*
template <class Number>
void Vector3D<Number>::print(){
    std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
}


template<class Number> void Vector2D<Number>::print(){
    std::cout << "x: " << x << " y: " << y << std::endl;
}
*/
}