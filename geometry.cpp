#pragma once
#include "tools.cpp"
#include "ray.hpp"
#include "vector.hpp"

//abstract class
class Geometry{

    public:
        Vector albedo; // stands for the colour [red,green,blue]
        bool mirror = false; // if the sphere is a mirror, for reflection
        bool transparent = false; // if the sphere is transparent, for refraction
        double refIndex; // refraction index
        int index; // its place in the scene
        bool sphere; //is it a sphere

        virtual Intersection intersect (const Ray& r) = 0;

}; 