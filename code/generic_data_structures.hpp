#pragma once
#include <array>

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
  void print();
};

template <class Number>
class Vector2D{
 public:
  Number x;
  Number y;
  void print();
};

template <class ConversionAngle>
class AngleDegrees : public Vector3D<double> {
 public:
  virtual ConversionAngle convertToRadians() = 0;
};

template <class ConversionAngle>
class AngleRadians : public Vector3D<double> {
 public:
  virtual ConversionAngle convertToDegrees() = 0;
};


class AngleDegrees3D : AngleDegrees<AngleRadians3D>{
 public:
  AngleRadians3D convertToRadians();
};

class AngleRadians3D : AngleRadians<AngleDegrees3D>{
 public:
  AngleDegrees3D convertToDegrees();
};


class AngleDegrees2D : AngleDegrees<AngleRadians2D>{
 public:
  AngleRadians2D convertToRadians();
};

class AngleRadians2D : AngleRadians<AngleDegrees2D>{
 public:
  AngleDegrees2D convertToDegrees();
};