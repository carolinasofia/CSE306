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
        for (int j = 0; j < subjectPolygon.vertices.size();j++){ // for each vertex of the subject polygon
            // make an edge
            Vector curVertex = subjectPolygon.vertices[j]; 
            Vector prevVertex = subjectPolygon.vertices[(j>0)?(j-1):subjectPolygon.vertices.size()-1];
            // compute intersection between the infinite line supported by clipEdge and edge (i-1,i)
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

std::vector<Polygon> voronoi(Polygon samples){
    std::vector<Polygon> voronoiDiagram; // holds all voronoi cells
    Polygon voronoiCell; 
    Polygon bigQuad = Polygon({Vector(0,0,0),Vector(0,1,0),Vector(1,1,0),Vector(1,0,0)});

    for (int i = 0; i < samples.vertices.size();i++){ //for every sample
        //for each sample
        Vector samplei = samples.vertices[i];
        voronoiCell = bigQuad; //make polygon to hold its voronoi cell starting off as the quadrilateral
        
        // find the bisector with the all other samples and use the sutherland thingy
        for (int j = 0; j <samples.vertices.size(); j++){
            if(j!=i){
                //for all other samples
                Vector samplej = samples.vertices[j];
                Polygon tempPoly = Polygon();
                for (int i = 0; i < voronoiCell.vertices.size();i++){ // for each vertex of the subject polygon
                    // make an edge
                    Vector curVertex = voronoiCell.vertices[i]; 
                    Vector prevVertex = voronoiCell.vertices[(i>0)?(i-1):voronoiCell.vertices.size()-1];
                    // compute intersection between the infinite line supported by clipEdge and edge (i-1,i)
                    Vector intersection = intersectVoronoi(prevVertex,curVertex,samplei,samplej);
                    if (insideVoronoi(curVertex,samplei,samplej)){
                        if (!insideVoronoi(prevVertex,samplei,samplej)){
                            // the subject polygon edge crosses the clip edge, and we leave the clipping area
                            tempPoly.vertices.push_back(intersection);
                        }
                        tempPoly.vertices.push_back(curVertex);
                    }
                    else if (insideVoronoi(prevVertex,samplei,samplej)){
                        // the subject polygon edge crosses the clip edge, and we enter the clipping area
                        tempPoly.vertices.push_back(intersection);
                    }
                }
                voronoiCell = tempPoly;
            }
        }
        voronoiDiagram.push_back(voronoiCell);
    }
    return voronoiDiagram;
}

std::vector<Polygon> powerVoronoi(Polygon samples){
    std::vector<Polygon> powerDiagram; // holds all power cells
    Polygon powerCell; 
    Polygon bigQuad = Polygon({Vector(0,0,0),Vector(0,1,0),Vector(1,1,0),Vector(1,0,0)});
    
    for (int i = 0; i < samples.vertices.size();i++){ //for every sample
        //for each sample
        Vector samplei = samples.vertices[i];
        double wi = pow(samples.radii[i],2);
        powerCell = bigQuad; //make polygon to hold its voronoi cell starting off as the quadrilateral
        
        // find the bisector with the all other samples and use the sutherland thingy
        for (int j = 0; j <samples.vertices.size(); j++){
            if(j!=i){
                //for all other samples
                Vector samplej = samples.vertices[j];
                double wj = pow(samples.radii[j],2);
                Polygon tempPoly = Polygon();
                for (int i = 0; i < powerCell.vertices.size();i++){ // for each vertex of the subject polygon
                    // make an edge
                    Vector curVertex = powerCell.vertices[i]; 
                    Vector prevVertex = powerCell.vertices[(i>0)?(i-1):powerCell.vertices.size()-1];
                    // compute intersection between the infinite line supported by clipEdge and edge (i-1,i)
                    Vector intersection = intersectPower(prevVertex,curVertex,samplei,samplej,wi,wj);
                    if (insidePower(curVertex,samplei,samplej,wi,wj)){
                        if (!insidePower(prevVertex,samplei,samplej,wi,wj)){
                            // the subject polygon edge crosses the clip edge, and we leave the clipping area
                            tempPoly.vertices.push_back(intersection);
                        }
                        tempPoly.vertices.push_back(curVertex);
                    }
                    else if (insidePower(prevVertex,samplei,samplej,wi,wj)){
                        // the subject polygon edge crosses the clip edge, and we enter the clipping area
                        tempPoly.vertices.push_back(intersection);
                    }
                }
                powerCell = tempPoly;
            }
        }
        powerDiagram.push_back(powerCell);
    }
    return powerDiagram;
}

// saves a static svg file. The polygon vertices are supposed to be in the range [0..1], and a canvas of size 1000x1000 is created
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
//draws dots and polygons
void save_svg(const Polygon &vectors, const std::vector<Polygon> &polygons,std::string filename, std::string fillcol = "none")
{
    FILE *f = fopen(filename.c_str(), "w+");
    fprintf(f, "<svg xmlns = \"http://www.w3.org/2000/svg\" width = \"1000\" height = \"1000\">\n");
    for (size_t i = 0; i < polygons.size(); i++){
        fprintf(f, "<g>\n");
        fprintf(f, "<polygon points = \"");
        for (size_t j = 0; j < polygons[i].vertices.size(); j++){
            fprintf(f, "%3.3f, %3.3f ", (polygons[i].vertices[j][0] * 1000), (1000 - polygons[i].vertices[j][1] * 1000));
        }
        fprintf(f, "\"\nfill = \"%s\" stroke = \"black\"/>\n", fillcol.c_str());
        fprintf(f, "</g>\n");
    }
    for (auto &vect : vectors.vertices){
        fprintf(f, "<g>\n");
        fprintf(f, "<circle cx = \"%3.3f\" cy = \"%3.3f\" r=\"5\"/>", vect[0] * 1000, 1000 - vect[1] * 1000);
        fprintf(f, "</g>\n");
    }
    fprintf(f, "</svg>\n");
    fclose(f);
}

// Adds one frame of an animated svg file. frameid is the frame number (between 0 and nbframes-1).
// polygons is a list of polygons, describing the current frame.
// The polygon vertices are supposed to be in the range [0..1], and a canvas of size 1000x1000 is created
void save_svg_animated(const std::vector<Polygon> &polygons, std::string filename, int frameid, int nbframes) {
    FILE* f;
    if (frameid == 0) {
        f = fopen(filename.c_str(), "w+");
        fprintf(f, "<svg xmlns = \"http://www.w3.org/2000/svg\" width = \"1000\" height = \"1000\">\n");
        fprintf(f, "<g>\n");
    } else {
        f = fopen(filename.c_str(), "a+");
    }
    fprintf(f, "<g>\n");
    for (int i = 0; i < polygons.size(); i++) {
        fprintf(f, "<polygon points = \"");
        for (int j = 0; j < polygons[i].vertices.size(); j++) {
            fprintf(f, "%3.3f, %3.3f ", (polygons[i].vertices[j][0] * 1000), (1000-polygons[i].vertices[j][1] * 1000));
        }
        fprintf(f, "\"\nfill = \"none\" stroke = \"black\"/>\n");
    }
    fprintf(f, "<animate\n");
    fprintf(f, "    id = \"frame%u\"\n", frameid);
    fprintf(f, "    attributeName = \"display\"\n");
    fprintf(f, "    values = \"");
    for (int j = 0; j < nbframes; j++) {
        if (frameid == j) {
            fprintf(f, "inline");
        } else {
            fprintf(f, "none");
        }
        fprintf(f, ";");
    }
    fprintf(f, "none\"\n    keyTimes = \"");
    for (int j = 0; j < nbframes; j++) {
        fprintf(f, "%2.3f", j / (double)(nbframes));
        fprintf(f, ";");
    }
    fprintf(f, "1\"\n   dur = \"5s\"\n");
    fprintf(f, "    begin = \"0s\"\n");
    fprintf(f, "    repeatCount = \"indefinite\"/>\n");
    fprintf(f, "</g>\n");
    if (frameid == nbframes - 1) {
        fprintf(f, "</g>\n");
        fprintf(f, "</svg>\n");
    }
    fclose(f);
}

Polygon bigQuad(Polygon samples){
   //make extremely large quadrilateral
    int minX, maxX = samples.vertices[0][0];
    int minY, maxY = samples.vertices[0][1];
    for (int i = 1; i < samples.vertices.size();i++){
        Vector sample = samples.vertices[i];
        if (sample[0] > maxX) maxX = sample[0];
        if (sample[0] < minX) minX = sample[0];
        if (sample[1] > maxY) maxY = sample[1];
        if (sample[1] < minY) minY = sample[1];
    }
    Polygon bigQuad = Polygon({Vector(minX-2,minY-2,0),Vector(minX-2,maxY+2,0),Vector(maxX+2,maxY+2,0),Vector(maxX+2,minY-2,0)}); 
    return bigQuad;
}