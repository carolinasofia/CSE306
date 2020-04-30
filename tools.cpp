#include "math.h"
#include <random>
#define PI 3.14159265

// for uniform random generation
static std::default_random_engine engine1(10); // random seed = 10
static std::uniform_real_distribution<double> uniform1(0, 1);

Vector boxMuller () {
    Vector V;
    double r1 = uniform1(engine1) ;
    double r2 = uniform1(engine1) ;

    double x = (sqrt(-2 * log (r1)) *cos (2 * PI *r2))*0.5;
    double y = (sqrt(-2 * log (r1)) *sin (2 * PI *r2))*0.5;
    
    V = Vector(x,y,0);
    return V;
}
