#pragma once

#include <iostream>
#include "vector.hpp"
#include <vector>
#include "polygon.hpp"

//Sutherland polygon clipping
Polygon sutherland(Polygon subjectPolygon, Polygon clipPolygon){
    Polygon outPolygon;
    for(int i = 0; i < clipPolygon.vertices.size();i++){ // for each edge of the clip polygon
        Vector clipEdgeV1 = clipPolygon.vertices[i]; //clip edge vertex1
        Vector clipEdgeV2 = clipPolygon.vertices[(i>0)?(i-1):clipPolygon.vertices.size()-1]; //clip edge vertex2
        outPolygon = Polygon();
        for (int i = 0; i < subjectPolygon.vertices.size();i++){ // for each vertex of the subject polygon
            // make an edge
            Vector curVertex = subjectPolygon.vertices[i]; 
            Vector prevVertex = subjectPolygon.vertices[(i>0)?(i-1):subjectPolygon.vertices.size()-1];
            // compute intersection between the infinIte line supported by clipEdge and edge (i-1,i)
            Vector intersection = intersect(prevVertex,curVertex,clipEdgeV1,clipEdgeV2);
            if (inside(curVertex,clipEdgeV1,clipEdgeV2)){
                if (!inside(prevVertex,clipEdgeV1,clipEdgeV2)){
                    // the subject polygon edge crosses the clip edge, and we leave the clipping area
                    outPolygon.vertices.push_back(intersection);
                }
                outPolygon.vertices.push_back(curVertex);
            }
            else if (inside(prevVertex,clipEdgeV1,clipEdgeV2)){
                // the subject polygon edge crosses the clip edge, and we enter the clipping area
                outPolygon.vertices.push_back(intersection);
            }
        }
    subjectPolygon = outPolygon;
    }
    return outPolygon;
}

void save_svg(const std::vector<Polygon> &polygons, std::string filename, std::string fillcol = "none") {
        FILE* f = fopen(filename.c_str(), "w+");
        fprintf(f, "<svg xmlns = \"http://www.w3.org/2000/svg\" width = \"1000\" height = \"1000\">\n");
        for (int i=0; i<polygons.size(); i++) {
            fprintf(f, "<g>\n");
            fprintf(f, "<polygon points = \"");
            for (int j = 0; j < polygons[i].vertices.size(); j++) {
                fprintf(f, "%3.3f, %3.3f ", (polygons[i].vertices[j][0] * 1000), (1000 - polygons[i].vertices[j][1] * 1000));
            }
            fprintf(f, "\"\nfill = \"%s\" stroke = \"black\"/>\n", fillcol.c_str());
            fprintf(f, "</g>\n");
        }
        fprintf(f, "</svg>\n");
        fclose(f);
}