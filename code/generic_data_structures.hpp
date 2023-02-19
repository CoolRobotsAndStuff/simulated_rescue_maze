#pragma once

#include <iostream>
#include <array>
#include <cmath>
#include <algorithm>

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
    
    Angle getAbsoluteDistanceTo(Angle t_angle){
      double distance = std::max(this->getRadians(), t_angle.getRadians()) - 
                        std::min(this->getRadians(), t_angle.getRadians());
      return Angle(distance);
    }

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

    Angle operator*(const double& other) const {
      return Angle(value * other);
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
    Angle& operator*=(const double& other) {
      value *= other;
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
};


template <class Number>
class Vector2D {
public:

  Vector2D(){}

  Vector2D(Number t_x, Number t_y){
    x = t_x;
    y = t_y;
  }

  Number x;
  Number y;
  void print() {
    std::cout << "x: " << x << " y: " << y << std::endl;
  }

  Number getDistanceToVector(Vector2D t_otherVector) {
    Vector2D<Number> difference = *this - t_otherVector;
    return sqrt(pow(difference.x, 2) + pow(difference.y, 2));
  }

  Angle getSlopeToVector(Vector2D t_otherVector) {
    Vector2D<Number> difference = *this - t_otherVector;
    Angle slope = Angle(atan2(difference.x, difference.y));
    slope.normalize();
    return slope;
  }

  // Unary operators
  Vector2D operator+() const {
    return Vector2D(+x, +y);
  }
  Vector2D operator-() const {
    return Vector2D(-x, -y);
  }

  // Binary arithmetic operators
  Vector2D operator+(const Vector2D& other) const {
    return Vector2D(x + other.x, y + other.y);
  }
  Vector2D operator-(const Vector2D& other) const {
    return Vector2D(x - other.x, y - other.y);
  }
  Vector2D operator*(const Vector2D& other) const {
    return Vector2D(x * other.x, y * other.y);
  }
  Vector2D operator/(const Vector2D& other) const {
    return Vector2D(x / other.x, y / other.y);
  }
  Vector2D operator%(const Vector2D& other) const {
    return Vector2D(std::fmod(x, other.x), std::fmod(y, other.y));
  }

  // Compound assignment operators
  Vector2D& operator+=(const Vector2D& other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  Vector2D& operator-=(const Vector2D& other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }
  Vector2D& operator*=(const Vector2D& other) {
    x *= other.x;
    y *= other.y;
    return *this;
  }
  Vector2D& operator/=(const Vector2D& other) {
    x /= other.x;
    y /= other.y;
    return *this;
  }
  Vector2D& operator%=(const Vector2D& other) {
    x = std::fmod(x, other.x);
    y = std::fmod(y, other.y);
    return *this;
  }


  // Binary arithmetic operators with numbers
  Vector2D operator+(const Number& other) const {
    return Vector2D(x + other, y + other);
  }
  Vector2D operator-(const Number& other) const {
    return Vector2D(x - other, y - other);
  }
  Vector2D operator*(const Number& other) const {
    return Vector2D(x * other, y * other);
  }
  Vector2D operator/(const Number& other) const {
    return Vector2D(x / other, y / other);
  }
  Vector2D operator%(const Number& other) const {
    return Vector2D(std::fmod(x, other), std::fmod(y, other));
  }

  // Compound assignment operators with numbers
  Vector2D& operator+=(const Number& other) {
    x += other;
    y += other;
    return *this;
  }
  Vector2D& operator-=(const Number& other) {
    x -= other;
    y -= other;
    return *this;
  }
  Vector2D& operator*=(const Number& other) {
    x *= other;
    y *= other;
    return *this;
  }
  Vector2D& operator/=(const Number& other) {
    x /= other;
    y /= other;
    return *this;
  }
  Vector2D& operator%=(const Number& other) {
    x = std::fmod(x, other);
    y = std::fmod(y, other);
    return *this;
  }

};


template <class Number>
class Vector3D {
public:

  Vector3D(){}

  Vector3D(Number t_x, Number t_y, Number t_z){
    x = t_x;
    y = t_y;
    z = t_z;
  }

  Number x;
  Number y;
  Number z;
  void print() {
    std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
  }

  Vector2D<Number> to2D(){
    return Vector2D<Number>(x, y);
  }

  // Unary operators
  Vector3D operator+() const {
    return Vector3D(+x, +y, +z);
  }
  Vector3D operator-() const {
    return Vector3D(-x, -y, -z);
  }

  // Binary arithmetic operators
  Vector3D operator+(const Vector3D& other) const {
    return Vector3D(x + other.x, y + other.y, z + other.z);
  }
  Vector3D operator-(const Vector3D& other) const {
    return Vector3D(x - other.x, y - other.y, z - other.z);
  }
  Vector3D operator*(const Vector3D& other) const {
    return Vector3D(x * other.x, y * other.y, z * other.z);
  }
  Vector3D operator/(const Vector3D& other) const {
    return Vector3D(x / other.x, y / other.y, z / other.z);
  }
  Vector3D operator%(const Vector3D& other) const {
    return Vector3D(std::fmod(x, other.x), std::fmod(y, other.y), std::fmod(z, other.z));
  }

  // Compound assignment operators
  Vector3D& operator+=(const Vector3D& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }
  Vector3D& operator-=(const Vector3D& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }
  Vector3D& operator*=(const Vector3D& other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
  }
  Vector3D& operator/=(const Vector3D& other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
  }
  Vector3D& operator%=(const Vector3D& other) {
    x = std::fmod(x, other.x);
    y = std::fmod(y, other.y);
    z = std::fmod(z, other.z);
    return *this;
  }

  // Binary arithmetic operators with numbers
  Vector3D operator+(const Number& other) const {
    return Vector3D(x + other, y + other, z + other);
  }
  Vector3D operator-(const Number& other) const {
    return Vector3D(x - other, y - other, z - other);
  }
  Vector3D operator*(const Number& other) const {
    return Vector3D(x * other, y * other, z * other);
  }
  Vector3D operator/(const Number& other) const {
    return Vector3D(x / other, y / other, z / other);
  }
  Vector3D operator%(const Number& other) const {
    return Vector3D(std::fmod(x, other), std::fmod(y, other), std::fmod(z, other));
  }

  // Compound assignment operators
  Vector3D& operator+=(const Number& other) {
    x += other;
    y += other;
    z += other;
    return *this;
  }
  Vector3D& operator-=(const Number& other) {
    x -= other;
    y -= other;
    z -= other;
    return *this;
  }
  Vector3D& operator*=(const Number& other) {
    x *= other;
    y *= other;
    z *= other;
    return *this;
  }
  Vector3D& operator/=(const Number& other) {
    x /= other;
    y /= other;
    z /= other;
    return *this;
  }
  Vector3D& operator%=(const Number& other) {
    x = std::fmod(x, other);
    y = std::fmod(y, other);
    z = std::fmod(z, other);
    return *this;
  }

};


template <class Number>
struct Transform2D {
  Transform2D(){};
  Transform2D(Vector2D<Number> t_position, Vector2D<Angle> t_orientation){
    position = t_position;
    orientation = t_orientation;
  };
  Vector2D<Number> position;
  Vector2D<Angle> orientation;
};


template <class Number>
struct Transform3D {
  Transform3D(){};

  Transform2D<Number> to2D() {
    return Transform2D<Number>(position.to2D(), orientation.to2D());
  }
  
  Vector3D<Number> position;
  Vector3D<Number> velocity;
  Vector3D<Number> acceleration;

  Vector3D<Angle> orientation;
  Vector3D<Angle> angularVelocity;
  Vector3D<Angle> angularAcceleration;
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

}