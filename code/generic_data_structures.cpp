#include <iostream>
#include "generic_data_structures.hpp"

using namespace std;

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

void FloatVector3D::print(){
    cout << "x: " << x << " y: " << y << " z: " << z << endl;
}

void DoubleVector3D::print(){
    cout << "x: " << x << " y: " << y << " z: " << z << endl;
}