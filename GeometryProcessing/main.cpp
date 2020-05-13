//imports
#include <iostream>
#include "vector"
#include "math.h"
#include <list>
#include <chrono>
using namespace std::chrono; 
//files
#include "vector.hpp"
#include "polygon.hpp"
#include "tools.hpp"


int main()
{
    
    //create subject polygon
    Polygon subjectPolygon;
    subjectPolygon.vertices.push_back(Vector(0,0,0));
    subjectPolygon.vertices.push_back(Vector(0.2,0.2,0));
    subjectPolygon.vertices.push_back(Vector(0.3,0.2,0));
    subjectPolygon.vertices.push_back(Vector(0.3,0.1,0));

    //create clipping polygon
    Polygon clipPolygon;
    clipPolygon.vertices.push_back(Vector(0,0,0));
    clipPolygon.vertices.push_back(Vector(0,0.1,0));
    clipPolygon.vertices.push_back(Vector(0.5,0.1,0));
    clipPolygon.vertices.push_back(Vector(0.5,0,0));

    //clip it
    Polygon clippedPolygon = sutherland(subjectPolygon,clipPolygon);

    std::vector<Polygon> polygons;
    polygons.push_back(clippedPolygon);
    //polygons.push_back(clipPolygon);
    //polygons.push_back(subjectPolygon);
    save_svg(polygons,"poly.svg");

    std::cout<< "Done";
    return 0; 
}
