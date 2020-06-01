#pragma once

#include <iostream>
#include "vector.hpp"
#include <vector>
#include <tuple>


class Polygon {  
public:
    std::vector<Vector> vertices;
    std::vector<double> radii;
    Polygon(std::vector<Vector> v){
        vertices = v;
    }
    Polygon(std::vector<Vector> v,std::vector<double> r){
        vertices = v;
        radii = r;
    }
    Polygon(){};
}; 