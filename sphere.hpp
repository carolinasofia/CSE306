#pragma once

//imports
#include "vector.hpp"
#include "ray.hpp"
#include <limits>

// you need this in intersection constructor
// To have a default distance when there is no intersection 
double inf = std::numeric_limits<double>::infinity();

class Intersection {
    public:
        bool is_intersection; // ?
        Vector position; // ?
        Vector normal; //the normal of the intersection
        double distance; // distance between the ?
        int index; // ?
        Intersection(bool b = false, Vector P = Vector(0, 0, 0), Vector N = Vector(0, 0, 0), double d = inf, int i = 0)
        {
            is_intersection = b; 
            position = P; 
            normal = N;  
            distance = d;   
            index = i; 
        }
};

class Sphere {
    public:
        Vector center; // center of the sphere
        double radius; // radius of the sphere
        Vector albedo; // stands for the colour [red,green,blue]
        int index; // its place in the scene
        bool mirror = false; // if the sphere is a mirror, for reflection
        bool transparent = false; // if the sphere is transparent, for refraction
        double refIndex; // refraction index
        bool hollow; // if a sphere is hollow

        Intersection intersect(const Ray &r); // JUST A DECLARATION - definition found in cpp file

        explicit Sphere(Vector C, double R,Vector A = Vector(0,0,0),std::string surface = "diffuse", double n = 0, bool h = false){
            center = C;
            radius = R;
            albedo = A; //colour
            if (surface == "mirror") mirror = true;
            if (surface == "transparent") transparent = true;
            refIndex = n; // refraction index
            hollow = h; // hollow
        }
};