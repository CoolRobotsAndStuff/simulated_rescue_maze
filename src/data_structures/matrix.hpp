#pragma once

#include <cstdint>

#include "generic_data_structures.hpp"

namespace simulated_rescue_maze {
namespace environment_model{


//Letter can be: {N, H, S, U, O, P, F}
struct Fixture {
  char letter = 'N';
  bool reported = false;
};

struct Tile{
  char tileType = 'N';
  bool explored = false;
  Fixture fixtures[4];
};


struct Point{
  bool occupied = false;
  bool traversable = true;
};

struct Matrix{
  static const int matrixSize = 500;
  static const int resolution = 8;

  static Tile tileMatrix[matrixSize][matrixSize];
  static int variablePointMatrix[matrixSize * resolution][matrixSize * resolution];
  static Point pointMatrix[matrixSize * resolution][matrixSize * resolution];

  static int const offset = matrixSize / 2 * resolution;


};
}
}