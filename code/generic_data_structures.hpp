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

class FloatVector3D{
    public:
        float x;
        float y;
        float z;
        void print();
    };

class DoubleVector3D{
    public:
        double x;
        double y;
        double z;
        void print();
    };