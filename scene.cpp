//imports
#include "scene.hpp"
#include "sphere.hpp"
#include "math.h"

// definition of function intersection in the class Scene
// returns an Intersection object between the ray and the scene
Intersection Scene::intersection(const Ray& r){
    int n = spheres.size(); //
    double min_d = inf; // minimum distance == infinity??
    Intersection res; // 
    for (int i = 0;i<n;i++){
        // for every spheres intersect with the ray
        auto temp = spheres[i].intersect(r);
        if (temp.is_intersection){
            // if there is an intersection
            if(temp.distance < min_d){
                // if the distance is smaller than infinity
                // then ??
                min_d = temp.distance;
                res = temp;
            }
        }
    }
    return res;
}