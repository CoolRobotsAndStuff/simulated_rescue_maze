#pragma once

#include <iostream>
#include <array>
#include <cmath>

namespace simulated_rescue_maze{
class Angle {
public:
    // Supported units
    enum Unit { RADIANS, DEGREES };

    // Constructors
    Angle();
    Angle(double value, Unit unit = RADIANS);

    // Setters
    void setRadians(double value);
    void setDegrees(double value);
    // Getters
    double getRadians();
    double getDegrees();

    void normalize();
    
    void print();

    // Unary operators
    Angle operator+() const {
      return Angle(+value);
    }
    Angle operator-() const {
      return Angle(-value);
    }

    // Binary arithmetic operators
    Angle operator+(const Angle& other) const {
      return Angle(value + other.value);
    }
    Angle operator-(const Angle& other) const {
      return Angle(value - other.value);
    }
    Angle operator*(const Angle& other) const {
      return Angle(value * other.value);
    }
    Angle operator/(const Angle& other) const {
      return Angle(value / other.value);
    }
    Angle operator%(const Angle& other) const {
      return Angle(std::fmod(value, other.value));
    }

    // Compound assignment operators
    Angle& operator+=(const Angle& other) {
      value += other.value;
      return *this;
    }
    Angle& operator-=(const Angle& other) {
      value -= other.value;
      return *this;
    }
    Angle& operator*=(const Angle& other) {
      value *= other.value;
      return *this;
    }
    Angle& operator/=(const Angle& other) {
      value /= other.value;
      return *this;
    }
    Angle& operator%=(const Angle& other) {
      value = std::fmod(value, other.value);
      return *this;
    }

    // Comparison operators
    bool operator==(const Angle& other) const {
      return value == other.value;
    }
    bool operator!=(const Angle& other) const {
      return value != other.value;
    }
    bool operator<(const Angle& other) const {
      return value < other.value;
    }
    bool operator>(const Angle& other) const {
      return value > other.value;
    }
    bool operator<=(const Angle& other) const {
      return value <= other.value;
    }
    bool operator>=(const Angle& other) const {
      return value >= other.value;
    }

private:
    double value;
    // Normalization
    
};

class DifferentialVelocities{
 public:
  float left;
  float right;

  DifferentialVelocities();
  DifferentialVelocities(float left, float right);
  std::array<float, 2> get_array();
  void set_array(std::array<float, 2> input_array);
  void set_velocities(float left, float right);
};

template <class Number>
class Vector3D{
 public:
  Number x;
  Number y;
  Number z;
  void print(){
    std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
  }

};

template <class Number>
class Vector2D{
 public:
  Number x;
  Number y;
  void print(){
    std::cout << "x: " << x << " y: " << y << std::endl;
  };
};

}