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
#include <chrono>
using namespace std::chrono;


int main()
{
    auto start = high_resolution_clock::now();
    //create subject polygon
    Polygon subjectPolygon = Polygon({Vector(0,0,0),Vector(0.2,0.2,0),Vector(0.3,0.2,0),Vector(0.3,0.1,0)});

    //create clipping polygon
    Polygon clipPolygon = Polygon({Vector(0,0,0),Vector(0,0.1,0),Vector(0.5,0.1,0),Vector(0.5,0,0)});

    //clip it
    //Polygon clippedPolygon = sutherland(subjectPolygon,clipPolygon);

    //std::vector<Polygon> polygons;
    //polygons.push_back(clippedPolygon);
    //polygons.push_back(clipPolygon);
    //polygons.push_back(subjectPolygon);
    //save_svg(polygons,"poly.svg");

    //VORONOI
    Polygon samples = Polygon({Vector(0.1,0.2,0),Vector(0.2,0.3,0),Vector(0.3,0.2,0),Vector(0.3,0.1,0)});
    save_svg(samples,voronoi(samples),"voronoi.svg");

    //POWER DIAGRAM
    Polygon samples1 = Polygon({Vector(0.1,0.2,0),Vector(0.2,0.3,0),Vector(0.3,0.2,0),Vector(0.3,0.1,0)},{0.01,0.03,0.05,0.03});
    save_svg(samples1,powerVoronoi(samples1),"power.svg");


    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    duration = duration / 1000;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
    std::cout<< "Done";
    return 0; 
}
