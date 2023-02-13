#pragma once
#include "generic_data_structures.hpp"

namespace env_model {
    class Camera{
        public:
            Vector3D<float> position; 
            Vector3D<float> orientation;
            int resolution[2];
            float h_fov;
            float v_fov;
    };

    class Wheel{
        public:
            Vector3D<float> position;
            float diameter;
            float velocity;
    };

    class Lidar{
        public:
            Vector3D<float> position;
            float v_fov;
    };
    
    class Robot{
        public:
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

}