#pragma once

#include "tools.hpp"
#include "polygon.hpp"
#include "lbfgs.h"
#include <vector>

lbfgsfloatval_t evaluate(
        void *instance,
        const lbfgsfloatval_t *x,
        lbfgsfloatval_t *g,
        const int n,
        const lbfgsfloatval_t step
)
{
        lbfgsfloatval_t fx = 0.0;

        
        auto voronoiInstance = (VoronoiDiagram *) instance;
        auto points = voronoiInstance->points.vertices;
        auto lambdas = voronoiInstance->lambdas;
        //auto boundingBox = voronoiInstance->boundingBox;


        for(int i = 0; i < n; i++) {
                points[i][2] = x[i];
        }
        auto voronoiDiagram = voronoi(points);
    
        double sx = 0;

        for(int i = 0; i < n; i++) {
                float T = abs(voronoiDiagram[i].area());
                sx += T;
                g[i] = T - lambdas[i];
                float aT = voronoiDiagram[i].distanceIntegral(points[i]);
                fx += x[i] * g[i] - abs(aT);
        }
        
        return fx;
}

int progress(
        void *instance,
        const lbfgsfloatval_t *x,
        const lbfgsfloatval_t *g,
        const lbfgsfloatval_t fx,
        const lbfgsfloatval_t xnorm,
        const lbfgsfloatval_t gnorm,
        const lbfgsfloatval_t step,
        int n,
        int k,
        int ls
        )
{
        printf("Iteration %d:\n", k);
        printf("  fx = %f, x[0] = %f, x[1] = %f\n", fx, x[0], x[1]);
        printf("  xnorm = %f, gnorm = %f, step = %f\n", xnorm, gnorm, step);
        printf("\n");
        return 0;
}
    
std::vector<double> semiOptimal(Polygon samples, std::vector<double> lambdas){
    
        int N = samples.vertices.size();

        lbfgsfloatval_t fx;
        lbfgsfloatval_t *m_x = lbfgs_malloc(N);
        
        //**************COPIED FROM SAMPLE CODE****************//
        if (m_x == NULL) {
                printf("ERROR: Failed to allocate a memory block for variables.\n");
                //TODO : THROW ERROR
        }
        // Initialize the variables
        for (int i = 0;i < N;i += 2) {
                m_x[i] = -1.2;
                m_x[i+1] = 1.0;
        }
        //*****************************************************//
        //auto boundingBox = bigQuad(samples); 
        Polygon boundingBox = Polygon({Vector(0,0,0),Vector(0,1,0),Vector(1,1,0),Vector(1,0,0)}); 
        auto instance = new VoronoiDiagram(samples,boundingBox,lambdas);

        //Call lbfgs            
        int ret = lbfgs(N, m_x, &fx, evaluate, progress, instance, NULL);
        
        std::vector<double> weights(N);
        // have to do a for loop instead of a = since they are different types
        for (int i = 0;i < N;i++){
                weights[i] = m_x[i];
        }
        
        return weights;
}

//Polygon X = positions
//double V = velocity
//double m = mass
// std::vector<Polygon,std::vector<double>> gallouetMerigot(Polygon X,std::vector<Vector> V, std::vector<double> m){
//         //std::vector<double> uniform = ;
//         std::vector<double> v_weights = semiOptimal(X,uniform); 

//         Polygon X_prime;
//         std::vector<Vector> v_prime;

//         int N = X.vertices.size();

//         double e = 0.004;
//         double dt = 0.002;
//         Vector g = Vector(0,-9.81,0); 

//         for (int i = 0;i<N;i++){ //for each particle
//                  auto F_spring = (1/pow(e,2)) * (Centroid(,v_weights[i]) - X.vertices[i])); //TODO add the cell for that particle
//                 auto F = F_spring + g;
//                 v_prime[i] = V[i] + (dt/m[i])*F;
//                 X_prime.vertices[i]= X.vertices[i] + dt*V[i];
//         }
        
//         std::vector<Polygon,std::vector<double>> result = {X_prime,v_prime};

//         return result;
// } 

// Vector Centroid(std::vector<Vector> vertices, double){
//         double CX,CY;
//         int N = vertices.size();

//         double sumArea = 0.0;
//         for (int i=0;i<N;i++){
//                 double xi = vertices[i][0];
//                 double yi = vertices[i][1];
//                 double xii = vertices[i+1][0];
//                 double yii = vertices[i+1][1];

//                 sumArea = sumArea + ((xi*yii) - (xii-yi));
//         }
//         auto A = 0.5 * sumArea;

//         double sumCX = 0.0;
//         for (int i=0;i<N;i++){
//                 double xi = vertices[i][0];
//                 double yi = vertices[i][1];
//                 double xii = vertices[i+1][0];
//                 double yii = vertices[i+1][1];
//                 sumCX = sumCX + ((xi + xii)*((xi*yii)-(xii*yi)));
//         }
//         CX = (1/A) * sumCX;

//         double sumCY = 0.0;
//         for (int i=0;i<N;i++){
//                 double xi = vertices[i][0];
//                 double yi = vertices[i][1];
//                 double xii = vertices[i+1][0];
//                 double yii = vertices[i+1][1];
//                 sumCY = sumCY + ((yi + yii)*((xi*yii)-(xii*yi)));
//         }
//         CY = (1/A) * sumCY;

//         return Vector(CX,CY,0);
// }