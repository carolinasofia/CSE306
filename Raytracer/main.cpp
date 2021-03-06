//imports
#include <iostream>
#include "vector"
#include "math.h"
#include <list>
#include <chrono>
using namespace std::chrono; 
//files
#include "vector.hpp"
#include "sphere.hpp"   
#include "sphere.cpp"
#include "tools.cpp"
#include "ray.hpp"
#include "scene.hpp"
#include "scene.cpp"
#include "camera.hpp"
#include "light.hpp"
#include "geometry.cpp"
#include "mesh.cpp"


#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"


int main()
{
    auto start = high_resolution_clock::now(); 
  
    //make spheres
    Geometry* s_middle = new Sphere(Vector(0, 0, 0), 10, Vector(1, 1, 1),"transparent",1.5);
    Geometry* s_left = new Sphere(Vector(-21,0,0), 10, Vector(1,1,1));

    Geometry* s_right = new Sphere(Vector(21, 0, 0), 10, Vector(1, 1, 1),"transparent",1.5);
    // to make a hollow sphere
    Geometry* s_right_hollow = new Sphere(Vector(21, 0, 0), 9, Vector(1, 1, 1),"transparent",1.5,true);
    // background spheres
    Geometry* s_green = new Sphere(Vector(0, 0, -1000), 940, Vector(0, 1, 0));
    Geometry* s_blue = new Sphere(Vector(0, -1000, 0), 990, Vector(0, 0, 1));
    Geometry* s_magenta = new Sphere(Vector(0, 0, 1000), 940, Vector(1,0,1));
    Geometry* s_red = new Sphere(Vector(0, 1000, 0), 940,Vector(1, 0, 0));
    Geometry* s_cyan = new Sphere(Vector(-1000, 0, 0), 940, Vector(0, 1, 1));
    Geometry* s_yellow = new Sphere(Vector(1000, 0, 0), 940, Vector(1, 1, 0));

    Vector Q = Vector(0,0,55);          // center of camera
    double alpha = 60;                  // field of view
    const int W = 500;                        // width of image
    const int H = 500;                        // height of image
    // make the camera
    Camera camera = Camera(Q,alpha,W,H);   
    // make the light
    Light L = Light(Vector(-10,20,40),pow(10,5));
    
    //Geometry* m = new TriangleMesh(Vector(1,1,0),"diffuse",2);
    Geometry* cat = new TriangleMesh("davyjones.obj",H,W);
    
    
    //make the scene
    //Scene scene = Scene({s_middle,s_left,s_right,s_green,s_blue,s_magenta,s_red,s_cyan,s_yellow,m}, L);
    Scene scene = Scene({cat}, L);
    //Scene scene = Scene({s_green,s_blue,s_magenta,s_red,s_cyan,s_yellow,cat}, L);


    int max_path_length = 2; // needed for eg mirrors for where the ray bounces to
    unsigned char data[W * H * 3]; //array of size w*h*3 (because 3 colours)
    
    //for every pixel in the image
    #pragma omp parallel for schedule(dynamic, 1)
    for (int i = 0; i < H; i++){
        for (int j = 0; j < W; j++){
            Vector colour = Vector(0,0,0); // initialise colour
            auto direction = camera.pixel(j,H-i-1)-Q;   //find the direction of the camera
            Ray r = Ray(Q,direction); // ray starting at the center of the camera in the direction of the pixel
                //Fresnel
                //list to hold all the colours
                std::list<Vector> colours;
                for (int k = 0; k <1; k++){
                    //send K rays
                    Vector randomdir = boxMuller();//BOXMULLER
                    Vector newdir = direction + randomdir;
                    
                    Ray randomray = Ray(Q,newdir);
                
                    colour = scene.getColour(randomray,max_path_length); 
                    colours.push_back(colour);
                }
                colour = average(colours);
            

            //GAMMA CORRECTION
            double power = 1. / 2.2;
            data[(i * W + j) * 3 + 0] = std::min(255., std::max(0., pow(colour[0], power) * 255)); //R
            data[(i * W + j) * 3 + 1] = std::min(255., std::max(0., pow(colour[1], power) * 255)); //G
            data[(i * W + j) * 3 + 2] = std::min(255., std::max(0., pow(colour[2], power) * 255)); //B
        }
    }

    stbi_write_jpg("image.jpg", W, H, 3, data, 0);  
 
    // Get ending timepoint 
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    duration = duration/1000;
    std::cout << "Time taken by function: " << duration.count() << " milliseconds" << std::endl; 
    std::cout << "Time taken by function: " << duration.count()/1000 << " seconds" << std::endl; 
    std::cout << "Time taken by function: " << duration.count()/60000 << " minutes" << std::endl; 


    return 0; 
}
