#pragma once

//imports
#include <vector>
#include "sphere.hpp"
#include "light.hpp"

class Scene{
     public:
        std::vector<Geometry *> content; // a list of spheres 
       

        //DECLARATIONS
        Intersection intersection(const Ray& r);    
        Vector getColour(const Ray &r, int ray_depth); 
        Light light = Light(Vector(0,0,0),0);
        
         
        explicit Scene(std::vector<Geometry*> G,Light L){
            content = G;
            light = L;
            for (int i = 0; i < content.size(); i++){
                // for every sphere make their index their index in the sphere list??
                content[i]->index = i;
            }
        }
};