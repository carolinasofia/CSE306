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

class VoronoiDiagram {
public: 
    Polygon points;
    Polygon boundingBox;
    std::vector<double> lambdas;
    VoronoiDiagram(Polygon pts, Polygon box, std::vector<double> ls){
        points = pts;
        boundingBox = box;
        lambdas = ls;
    }
};