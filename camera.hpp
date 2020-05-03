#pragma once
//imports
#include "vector.hpp"
//definitions
#define PI 3.14159265
#define rtd double(180 / PI) // radian to degree: radian * rtd = degree
#define dtr double(PI / 180) // degree to radian

class Camera{
    public:
        Vector center;      // center of camera
        double fov;         // field of view 
        double f;           // distance between screen and center
        double width;       
        double height;       
        explicit Camera(Vector Q, double alpha, int W, int H){
            center = Q;
            fov = alpha;
            width = W;
            height = H;
        }
        Vector pixel(int x, int y){
            double f = this->width / (2*tan(dtr*this->fov/2)); //width of this camera / (2 * tan(radian conversion of the fov angle/2)

            // return a vector of : // lecture note facts
            // the center of the camera (x value) + the x value of the pixel + 0.5 + width/2 
            // the center of the camera (y value) + the y value of the pixel + 0.5 - height/2
            // the center of the camera (z value) - f 
            return Vector(this->center[0] + x + 0.5 - this->width / 2, 
                        this->center[1] + y + 0.5 - this->height / 2, 
                        this->center[2] - f);
        }
};