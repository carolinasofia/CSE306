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

double area(Polygon p) {
    auto vertices = p.vertices;
    auto N = vertices.size();
    double sumArea = 0.0;
        for (int i=0;i<N;i++){
                double xi = vertices[i][0];
                double yi = vertices[i][1];
                double xii = vertices[(i+1)%N][0];
                double yii = vertices[(i+1)%N][1];

                sumArea = sumArea + ((xi*yii) - (xii*yi));
        }
    auto A = 0.5 * sumArea;
    return A;
}

double distanceIntegral(Polygon p,Vector Pi) {
    auto vertices = p.vertices;
    if(!vertices.size()) return 0;
    double I = 0;
    Vector c[3];
    c[0] = vertices[0];
    for(int i = 1; i < int(vertices.size()) - 1; i ++) {
        if(vertices[i][2] != 0) std::cout << "non zero z" << std::endl;
        double x = 0;
        c[1] = vertices[i];
        c[2] = vertices[i+1];
        for(int k = 0; k < 3; k ++) {
            for(int l = k; l < 3; l ++) {
                x += dot(c[k] - Pi, c[l] - Pi);
            }
        }
        double T = cross(c[0] - c[1], c[2] - c[1])[2]/2;
        I += T * x;
    }
    return I / 6;
}

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