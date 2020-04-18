#pragma once
//imports
#include "vector.hpp"
#define PI 3.14159265 

class Light{
    public:
        Vector origin; // origin of the light
        double intensity; // intensity of light
        explicit Light(Vector S, double I){
            origin = S;
            intensity = I;
        }
};