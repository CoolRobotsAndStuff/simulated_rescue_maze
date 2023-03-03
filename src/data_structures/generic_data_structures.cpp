#include <iostream>
#include <algorithm>

#include "generic_data_structures.hpp"
#include "../utils.hpp"


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

// Normalization
void Angle::normalize() {
  value = fmod(value, 2.0 * M_PI);
  if (value < 0.0) {
    value += 2.0 * M_PI;
  }
}

Angle Angle::getAbsoluteDistanceTo(Angle t_angle){
  t_angle.normalize();
  double minAng = std::min(this->getRadians(), t_angle.getRadians());
  double maxAng = std::max(this->getRadians(), t_angle.getRadians());

  double clockwiseDistance = maxAng - minAng;
  double counterClockwiseDistance = (360 + minAng) - maxAng;
  return Angle(std::min(clockwiseDistance, counterClockwiseDistance));
}

void Angle::print() {
  std::cout << this->getDegrees();
}

 // Unary operators
Angle Angle::operator+() const {
  return Angle(+value);
}
Angle Angle::operator-() const {
  return Angle(-value);
}

// Binary arithmetic operators
Angle Angle::operator+(const Angle& other) const {
  return Angle(value + other.value);
}

Angle Angle::operator-(const Angle& other) const {
  return Angle(value - other.value);
}

Angle Angle::operator*(const Angle& other) const {
  return Angle(value * other.value);
}
Angle Angle::operator/(const Angle& other) const {
  return Angle(value / other.value);
}
Angle Angle::operator%(const Angle& other) const {
  return Angle(std::fmod(value, other.value));
}

Angle Angle::operator*(const double& other) const {
  return Angle(value * other);
}

// Compound assignment operators
Angle& Angle::operator+=(const Angle& other) {
  value += other.value;
  return *this;
}
Angle& Angle::operator-=(const Angle& other) {
  value -= other.value;
  return *this;
}
Angle& Angle::operator*=(const double& other) {
  value *= other;
  return *this;
}
Angle& Angle::operator*=(const Angle& other) {
  value *= other.value;
  return *this;
}
Angle& Angle::operator/=(const Angle& other) {
  value /= other.value;
  return *this;
}
Angle& Angle::operator%=(const Angle& other) {
  value = std::fmod(value, other.value);
  return *this;
}

// Comparison operators
bool Angle::operator==(const Angle& other) const {
  return value == other.value;
}
bool Angle::operator!=(const Angle& other) const {
  return value != other.value;
}
bool Angle::operator<(const Angle& other) const {
  return value < other.value;
}
bool Angle::operator>(const Angle& other) const {
  return value > other.value;
}
bool Angle::operator<=(const Angle& other) const {
  return value <= other.value;
}
bool Angle::operator>=(const Angle& other) const {
  return value >= other.value;
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

}