#pragma once
#include "tools.cpp"
#include "ray.hpp"
#include "vector.hpp"

//abstract class
class Geometry{

    public:
        Vector albedo; // stands for the colour [red,green,blue]
        int index; // its place in the scene
        bool mirror = false; // if the sphere is a mirror, for reflection
        bool transparent = false; // if the sphere is transparent, for refraction
        double refIndex; // refraction index
        virtual Intersection intersect (const Ray& r) = 0;
        Vector center; // center of the sphere
        double radius; // radius of the sphere
        bool hollow; // if a sphere is hollow

};