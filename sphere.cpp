#include "sphere.hpp"

// declaration of the function instersect
// found in the class Sphere
// returns an Intersection

//the const means that you HAVE TO send a const ray
Intersection Sphere::intersect(const Ray& r){
    // return the intersection point between the sphere and the given ray

    double t = 0; //?
    bool is_inter = true; // is an intersection?
    Vector u = r.direction; // direction of ray
    Vector O = r.origin; // origin of ray
    Vector C = this->center; // center of sphere 
    double R = this->radius; // radius of sphere

    //????
    auto delta = pow(dot(u, O - C), 2) - ((pow(norm(O - C), 2)) - pow(R, 2)); 

    if (delta < 0){  
        // no solution, no intersection between the ray and the sphere
        is_inter = false;
        return Intersection();
    }
    else{
        // there is an intersection
        // or two

        auto t_temp = dot(u, C - O);
        auto t1 = t_temp - sqrt(delta);
        auto t2 = t_temp + sqrt(delta);

        if (t2 < 0){
            //
            is_inter = false;
            return Intersection();
        }
        else if (t1 >= 0)
            t = t1;
        else
            t = t2;
        double distance = t;
        Vector vec = O + t * u;

        auto temp = vec - C;
        Vector normal = temp / norm(temp);
        return Intersection(is_inter, vec, normal, distance,index);
    }
}