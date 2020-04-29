#include "math.h"
#include <random>
#define PI 3.14159265

// for uniform random generation
static std::default_random_engine engine1(10); // random seed = 10
static std::uniform_real_distribution<double> uniform1(0, 1);

Vector boxMuller () {
    double r1 = uniform1(engine1) ;
    double r2 = uniform1(engine1) ;
    double r3 = uniform1(engine1);
    double r4 = uniform1(engine1);

    double x = sqrt(-2 * log (r1)) *cos (2 * PI *r2);
    double y = sqrt(-2 * log (r1)) *sin (2 * PI *r2);
    double z = sqrt(-2 * log (r3)) *cos (2 * PI *r4);
    return Vector(x,y,z);
}
