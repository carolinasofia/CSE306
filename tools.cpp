#pragma once

//imports
#include "vector.hpp"
#include "ray.hpp"
#include <limits>
#include "math.h"
#include <random>
#define PI 3.14159265

// for uniform random generation
static std::default_random_engine engine1(10); // random seed = 10
static std::uniform_real_distribution<double> uniform1(0, 1);

// you need this in intersection constructor
// To have a default distance when there is no intersection 
double inf = std::numeric_limits<double>::infinity();

class Intersection {
    public:
        bool is_intersection; // 
        Vector position; // 
        Vector normal; //the normal of the intersection
        double distance; // 
        int index; // 
        Intersection(bool b = false, Vector P = Vector(0, 0, 0), Vector N = Vector(0, 0, 0), double d = inf, int i = 0)
        {
            is_intersection = b; 
            position = P; 
            normal = N;  
            distance = d;   
            index = i; 
        }
};


Vector boxMuller () {
    Vector V;
    double r1 = uniform1(engine1) ;
    double r2 = uniform1(engine1) ;

    double x = (sqrt(-2 * log (r1)) *cos (2 * PI *r2))*0.5;
    double y = (sqrt(-2 * log (r1)) *sin (2 * PI *r2))*0.5;
    
    V = Vector(x,y,0);
    return V;
}
