#pragma once
#include "tools.cpp"
#include "ray.hpp"

//abstract class
class Geometry{

    public:
        virtual Intersection intersect (const Ray& r) = 0;

};