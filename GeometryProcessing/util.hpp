#pragma once

#include "tools.hpp"
#include "polygon.hpp"
#include "lbfgs.h"
#include <vector>

static lbfgsfloatval_t _evaluate(
        void *instance,
        const lbfgsfloatval_t *x,
        lbfgsfloatval_t *g,
        const int n,
        const lbfgsfloatval_t step
        )
        {
                return reinterpret_cast<objective_function*>(instance)->evaluate(x, g, n, step);
        }

lbfgsfloatval_t evaluate(
        const lbfgsfloatval_t *x,
        lbfgsfloatval_t *g,
        const int n,
        const lbfgsfloatval_t step
)
{
        lbfgsfloatval_t fx = 0.0;

        for (int i = 0;i < n;i += 2) {
            lbfgsfloatval_t t1 = 1.0 - x[i];
            lbfgsfloatval_t t2 = 10.0 * (x[i+1] - x[i] * x[i]);
            g[i+1] = 20.0 * t2;
            g[i] = -2.0 * (x[i] * g[i+1] + t1);
            fx += t1 * t1 + t2 * t2;
        }
        return fx;
}

static int _progress(
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
        return reinterpret_cast<objective_function*>(instance)->progress(x, g, fx, xnorm, gnorm, step, n, k, ls);
}

int progress(
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

        // 'this' from the sample code is the instance.

        //Call lbfgs            
        int ret = lbfgs(N, m_x, &fx, _evaluate, _progress, this, NULL);
        
        std::vector<double> weights(N);
        // have to do a for loop instead of a = since they are different types
        for (int i = 0;i < N;i++){
                weights[i] = m_x[i];
        }
        
        return weights;
}