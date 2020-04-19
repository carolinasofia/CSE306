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

//REFLEXION
Vector Scene::intensity_reflexion(const Ray& r, int ray_depth){
    if (ray_depth < 0){
        // base case
        return Vector(0.,0.,0.);
    }

    Intersection inter = intersection(r); // intersection between the ray and this.scene
    Vector N = inter.normal; // normal to the intersection
    Vector P = inter.position + N*0.001; // offset the reflected ray slightly to minimise noise

    if (inter.is_intersection){
        // if there is an intersection
        if (spheres[inter.index].mirror){
            //if the sphere is a mirror
            Ray reflect = Ray(P,r.direction - 2*dot(r.direction,N)*N);
            return intensity_reflexion(reflect,ray_depth-1);
        }
        else{
            // if not a mirror then ?
            double I = light.intensity;
            Vector S = light.origin;
            
            Sphere s = spheres[inter.index]; //sphere that ray is intersecting with
            Vector albedo = s.albedo; // colour of that sphere

            double d = norm(S - P); // norm of distance between light source and intersection
            Vector omega = (S - P) / d; // non-norm distance between light and intersection of length 1

            Ray r_light = Ray(S, - omega); // make new ray starting from light origin in the opposite direction
            // if the intersection between the new ray and the scene has a greater distance that the distance between the light and intersection then visibility = 1
            int visibility = this->intersection(r_light).distance > d ? 1 : 0; 

            return (I / (4 * PI * pow(d, 2))) * (albedo / PI) * (visibility * std::max(dot(N, omega), 0.));
        }
    }
    // if there was no intersection
    return Vector(0.,0.,0.);
}