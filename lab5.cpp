#pragma once
#include "vector.hpp"
#include <iostream>
#include "vector"
#include "math.h"
#include <list>


#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"


void imageRetarget(){
    int W ;                       
    int H ;
    int channels;
    //unsigned char data[W * H * 3];

    
    unsigned char *data = stbi_load("lab5.png", &W, &H, &channels, 3);
    //energy map
    // const int height = H;
    // const int width = W;
    // int energy[height*width];
    std::list<int> energy;
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            int I = data[(i * W + j) * 3 + 0] + data[(i * W + j) * 3 + 1] + data[(i * W + j) * 3 + 2]; //R+G+B
            energy.push_back(I);
        }
    }
    //cumulated energy map
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            int C = 
            data[(i * W + j) * 3 + 0] + data[(i * W + j) * 3 + 1] + data[(i * W + j) * 3 + 2]; //R+G+B
            cumulatedEnergy.push_back(C);
        }
    }

   

}
int C(int x, int y,unsigned char* data,std::list<int> energy){
    
    return std::min(C(x-1,y-1),C(x, y-1),C(x+1,y-1));
     
}