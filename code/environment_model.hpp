#include "generic_data_structures.hpp"

namespace env_model {
    class Camera{
        public:
            FloatVector3D position; 
            FloatVector3D orientation;
            int resolution[2];
            float h_fov;
            float v_fov;
    };

    class Wheel{
        public:
            FloatVector3D position;
            float diameter;
            float velocity;
    };

    class Lidar{
        public:
            FloatVector3D position;
            float v_fov;
    };
    
    class Robot{
        public:
            //mts
            FloatVector3D position;
            //mts*s
            FloatVector3D velocity;
            //mts*s*s
            FloatVector3D acceleration;

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