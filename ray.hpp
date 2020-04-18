#pragma once
//imports
#include "vector.hpp"

class Ray {
    public:
        Vector origin; //rays origin
        Vector direction; //rays direction
        explicit Ray(Vector O, Vector u){
            origin = O;
            direction = normalization(u); //makes it size 1
        }
};