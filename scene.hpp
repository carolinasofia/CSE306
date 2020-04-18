#pragma once

//imports
#include <vector>
#include "sphere.hpp"
#include "light.hpp"

class Scene{
     public:
        std::vector<Sphere> spheres; // ??
        //DECLARATIONS
        Intersection intersection(const Ray& r); 
        Vector intensity_reflexion(const Ray &r, int ray_depth); 
        Light light = Light(Vector(0,0,0),0);
        
        // explicit 
        explicit Scene(std::vector<Sphere> S, Light L){
            spheres = S;
            light = L;
            for (int i = 0; i < spheres.size(); i++){
                // for every sphere make their index their index in the sphere list??
                spheres[i].index = i;
            }
        }
}