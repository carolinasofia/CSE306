// imports
#include "scene.hpp"
#include "sphere.hpp"
#include "math.h"
#include <random>
// for uniform random generation
static std::default_random_engine engine(10); // random seed = 10
static std::uniform_real_distribution<double> uniform(0, 1);

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
                min_d = temp.distance;
                res = temp;
            }
        }
    }
    return res;
}
Vector random_cos(const Vector &N){
    double r1 = uniform(engine);
    double r2 = uniform(engine);

    double RHS = sqrt(1-r2);

    double x = cos(2*PI*r1)*RHS;
    double y = sin(2*PI*r1)*RHS;
    double z = sqrt(r2);

    // detect the smallest component of N in absolute value
    double minN = std::min(std::min(abs(N[0]), abs(N[1])), abs(N[2]));
    
    Vector t1;
    // find it and force it to be zero
    for (int i = 0; i<3;i++){
        //swap the two other components
        //negate one of them to produce t1
        if(abs(N[i]) == minN){
            if(i == 0){
                t1 = Vector(0,N[2],-N[1]);
            }
            else if(i==1){
                t1 = Vector(N[2],0,-N[0]);
            }
            else{
                t1 = Vector(N[1],-N[0],0);
            }
        }
    }
    
    //normalize t1
    t1 = normalization(t1);
    //obtain t2 by cross product between N and t1
    Vector t2 = cross(N,t1);
    //random vector = xt1 + yT2 + zN 
    return (x * t1) + (y*t2) + (z*N);

}
//REFLEXION
Vector Scene::getColour(const Ray& r, int ray_depth){
    if (ray_depth < 0){
        // base case
        return Vector(0.,0.,0.);
    }

    Intersection inter = this->intersection(r); // intersection between the ray and this.scene

    Vector N = inter.normal; // normal to the intersection
    Vector P = inter.position + N*0.01; // offset the reflected ray slightly to minimise noise

    if (inter.is_intersection){
        // if there is an intersection
        if (spheres[inter.index].mirror){
            //if the sphere is a mirror
            Ray reflect = Ray(P,r.direction - 2*dot(r.direction,N)*N);
            return getColour(reflect,ray_depth-1);
        }
        else if(spheres[inter.index].transparent){
            // if the sphere is transparent
            double n1,n2;

            if(spheres[inter.index].hollow){
                // if hollow and entering
                N = -N;
                n1 = spheres[inter.index].refIndex;
                n2 = 1.5; 
            }
            if (dot(r.direction, N) > 0){
                // ray inside the sphere
                N = -N; 
                n1 = spheres[inter.index].refIndex;
                n2 = 1; // refractive index of incoming plane
            } 
            else {
                n1 = 1; // refractive index of incoming plane
                n2 = spheres[inter.index].refIndex;
            }
            
            //FRESNELs LAW
            auto k0 = pow((n1-n2),2)/pow((n1+n2),2);
            auto R = k0 + ((1-k0)*pow(1-abs(dot(N,r.direction)),5));
            auto T = 1 - R;

            auto u = uniform(engine); // uniform random number between 0 and 1

            if (u < R){
                //Fresnels
                // return a reflection ray 
                // *0.02 is to counter the 0.01 from the definition of P
                Ray reflectedRay = Ray(P,r.direction - 2 * dot(r.direction,N)*N);

                return getColour(reflectedRay, ray_depth-1);
            }
            else{
                //return a refracted ray

                // tangential component
                Vector w_T = (n1/n2) * (r.direction - dot(r.direction,N)*N);
                auto temp = (1-(pow(n1/n2,2)*(1- pow(dot(r.direction,N),2))));
                if(temp<0){
                    // to stop total internal reflection
                    Ray ray = Ray(P,r.direction - 2*dot(r.direction,N)*N);
                    return getColour(ray,ray_depth-1);
                }

                // normal component
                Vector w_N = (-N) * sqrt(temp);
            
                Vector w_t = (w_T + w_N);
                Ray refractRay = Ray(P - N *0.02, w_t);
                return getColour(refractRay,ray_depth-1);
            }
        }
        else{
            // if not a mirror|transparent then difuse surface
            double I = light.intensity;
            Vector S = light.origin;
            
            auto s = spheres[inter.index]; //sphere that ray is intersecting with
            Vector albedo = s.albedo; // colour of that sphere

            double d = norm(S - P); // norm of distance between light source and intersection
            Vector omega = (S - P) / d; // non-norm distance between light and intersection of length 1

            Ray r_light = Ray(S, - omega); // make new ray starting from light origin in the opposite direction
            // if the intersection between the new ray and the scene has a greater distance that the distance between the light and intersection then visibility = 1
            int visibility = this->intersection(r_light).distance > d ? 1 : 0; 
            
            Vector Lo = (I / (4 * PI * pow(d, 2))) * (albedo / PI) * (visibility * std::max(dot(N, omega), 0.));

            //add indirect lighting
            Ray randomRay = Ray(P, random_cos(N));
            Lo += pointwise(albedo,getColour(randomRay,ray_depth-1));
            return Lo;
        }
    }
    // if there was no intersection
    return Vector(0.,0.,0.);
}