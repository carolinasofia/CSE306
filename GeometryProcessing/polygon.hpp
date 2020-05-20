#pragma once

#include <iostream>
#include "vector.hpp"
#include <vector>

class Polygon {  
public:
    std::vector<Vector> vertices;
    Polygon(std::vector<Vector> v){
        vertices = v;
    }
    Polygon(){};
}; 