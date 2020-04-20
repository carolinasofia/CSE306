//imports
#include <iostream>
#include "vector.hpp"
#include "sphere.hpp"
#include "sphere.cpp"
#include "ray.hpp"
#include "scene.hpp"
#include "scene.cpp"
#include "camera.hpp"
#include "light.hpp"


#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include "vector"
#include "math.h"

int main()
{
    //make some spheres ??
    Sphere s_left = Sphere(Vector(-21,0,0), 10, Vector(1,1,1),"mirror");
    Sphere s_middle = Sphere(Vector(0, 0, 0), 10, Vector(1, 1, 1));

    Sphere s_right = Sphere(Vector(21, 0, 0), 10, Vector(1, 1, 1),"transparent",1.5);
    // to make a hollow sphere
    Sphere s_right_hollow = Sphere(Vector(21, 0, 0), 9, Vector(1, 1, 1),"transparent",1.5,true);
    //background spheres
    Sphere s_green = Sphere(Vector(0, 0, -1000), 940, Vector(0, 1, 0));
    Sphere s_blue = Sphere(Vector(0, -1000, 0), 990, Vector(0, 0, 1));
    Sphere s_magenta = Sphere(Vector(0, 0, 1000), 940, Vector(1,0,1));
    Sphere s_red = Sphere(Vector(0, 1000, 0), 940,Vector(1, 0, 0));
    Sphere s_cyan = Sphere(Vector(-1000, 0, 0), 940, Vector(0, 1, 1));
    Sphere s_yellow = Sphere(Vector(1000, 0, 0), 940, Vector(1, 1, 0));

    Vector Q = Vector(0,0,55);          // center of camera
    double alpha = 60;                  // field of view
    int W = 720;                        // width
    int H = 720;                        // height
    // make the camera
    Camera cam = Camera(Q,alpha,W,H);   
    // make the light
    Light L = Light(Vector(-10,20,40),pow(10,5));
    
    
    //make the scene
    Scene scene = Scene({s_middle, s_left, s_right_hollow, s_right, s_green, s_blue, s_magenta, s_red, s_cyan, s_yellow}, L);

    int max_path_length = 10; // needed for eg mirrors for like where the ray bounces to
    unsigned char data[W * H * 3]; //array of size w*h*3 (because 3 colours)
    
    for (int i = 0; i < H; i++){
        for (int j = 0; j < W; j++){
            // for every 'pixel'
            Vector color = Vector(0,0,0); // initialise colour
            auto direction = cam.pixel(j,H-i-1)-Q; 
            Ray r = Ray(Q,direction);
  
            color = scene.intensity_reflexion(r,max_path_length);
            
            //GAMMA CORRECTION
            double power = 1. / 2.2;
            data[(i * W + j) * 3 + 0] = std::min(255., std::max(0., pow(color[0], power) * 255));
            data[(i * W + j) * 3 + 1] = std::min(255., std::max(0., pow(color[1], power) * 255));
            data[(i * W + j) * 3 + 2] = std::min(255., std::max(0., pow(color[2], power) * 255));
        }
    }

    stbi_write_jpg("image.jpg", W, H, 3, data, 0);
    std::cout << "return";
    return 0;
}
