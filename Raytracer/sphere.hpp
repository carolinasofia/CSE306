#pragma once

//imports
#include "vector.hpp"
#include "ray.hpp"
#include <limits>
#include "tools.cpp"
#include "geometry.cpp"

class Sphere : public Geometry{
    public:
        Vector center; // center of the sphere
        double radius; // radius of the sphere
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