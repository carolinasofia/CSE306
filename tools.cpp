#pragma once

//imports
#include "vector.hpp"
#include "ray.hpp"
#include <limits>
#include "math.h"
#include <random>
#define PI 3.14159265
// for uniform random generation
static std::default_random_engine engine(10); // random seed = 10
static std::uniform_real_distribution<double> uniform(0, 1);

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
        Vector albedo; //for use with meshes
        Intersection(bool b = false, Vector P = Vector(0, 0, 0), Vector N = Vector(0, 0, 0), double d = inf, int i = 0, Vector A = Vector(1,0,0))
        {
            is_intersection = b; 
            position = P; 
            normal = N;  
            distance = d;   
            index = i; 
            albedo = A;
        }
};

Vector random_cos(const Vector &N){
    double r1 = uniform(engine);
    double r2 = uniform(engine);

    double RHS = sqrt(1-r2);

    double x = cos(2*PI*r1)*RHS;
    double y = sin(2*PI*r1)*RHS;
    double z = sqrt(r2);

    // detect the smallest component of N in absolute value
    double minN = std::min(std::min(abs(N[0]), abs(N[1])), abs(N[2]));
    
    Vector t1;
    // find it and force it to be zero
    for (int i = 0; i<3;i++){
        //swap the two other components
        //negate one of them to produce t1
        if(abs(N[i]) == minN){
            if(i == 0){
                t1 = Vector(0,N[2],-N[1]);
            }
            else if(i==1){
                t1 = Vector(N[2],0,-N[0]);
            }
            else{
                t1 = Vector(N[1],-N[0],0);
            }
        }
    }
    
    //normalize t1
    t1 = normalization(t1);
    //obtain t2 by cross product between N and t1
    Vector t2 = cross(N,t1);
    //random vector = xt1 + yT2 + zN 
    return (x * t1) + (y*t2) + (z*N);

}

Vector boxMuller () {
    Vector V;
    double r1 = uniform(engine) ;
    double r2 = uniform(engine) ;

    double x = (sqrt(-2 * log (r1)) *cos (2 * PI *r2))*0.5;
    double y = (sqrt(-2 * log (r1)) *sin (2 * PI *r2))*0.5;
    
    V = Vector(x,y,0);
    return V;
}

bool inRange(unsigned low, unsigned high, unsigned x){
    return (low <= x && x <= high);
}
