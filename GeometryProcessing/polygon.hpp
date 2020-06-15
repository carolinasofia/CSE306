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

double integral(Polygon poly,Vector Pi) {
    double ans = 0.0;
    auto vertices = poly.vertices;
    int N = vertices.size();

    double sum = 0.0;

    for (int k = 1;k < N;k++){
        auto Xk = vertices[k][0];
        auto Xkk = vertices[k-1][0];
        auto Yk = vertices[k][1];
        auto Ykk = vertices[k-1][1];

        double equ1 = ((Xkk*Yk)-(Xk*Ykk));
        double equ2 = (pow(Xkk,2) + (Xkk*Xk) + pow(Xk,2) + pow(Ykk,2) + (Ykk*Yk) + pow(Yk,2));
        double equ3 = (-4 * ((Pi[0]*(Xkk + Xk)) + (Pi[1] * (Ykk + Yk)))) + 6 * pow(norm(Pi),2);

        sum = sum + (equ1 * (equ2 + equ3));
    }
   

    return (1/12) * sum;
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