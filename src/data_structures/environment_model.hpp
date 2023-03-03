#pragma once

#include "generic_data_structures.hpp"

namespace simulated_rescue_maze {
namespace environment_model{

struct Camera{
  Vector3D<float> position; 
  Vector3D<float> orientation;
  int resolution[2];
  float h_fov;
  float v_fov;
};

struct Wheel{
  Vector3D<float> position;
  float diameter;
  float velocity;
};

struct Lidar{
  Vector3D<float> position;
  float v_fov;
};

struct Robot{
  //mts
  Vector3D<double> position;
  //mts*s
  Vector3D<double> velocity;
  //mts*s*s
  Vector3D<double> acceleration;

  //degrees
  double orientation;
  //degrees*s
  double angular_velocity;
  //degrees*s*s
  double angular_acceleration;

  //mts
  float diameter;

  float wheel_diameter;

  //mts * s
  Wheel left_wheel;
  Wheel right_wheel;

  Camera cameras[3];
};


struct Fixture {
  enum Letter {UNKNOWN, H, S, U, O, P, F};
  Letter letter = UNKNOWN;
  bool reported = false;
};


struct Tile{
  enum TileType {UNKNOWN, NORMAL, START, HOLE, SWAMP, EMPTY};

  TileType tileType = UNKNOWN;
  bool explored = false;

  Fixture fixtures[4];
};

struct Matrix{
  static const int matrixSize = 1000;
  static const int resolution = 10;
  static Tile tileMatrix[matrixSize][matrixSize];
  static int pointMatrix[matrixSize * resolution][matrixSize * resolution];
  static int const offset = ((matrixSize / resolution) / 2) * resolution;


};
}
}