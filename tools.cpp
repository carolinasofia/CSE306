#include "math.h"
#include <random>
#define PI 3.14159265

// for uniform random generation
static std::default_random_engine engine1(10); // random seed = 10
static std::uniform_real_distribution<double> uniform1(0, 1);

void boxMuller ( double stdev , double &x , double &y ) {
double r1 = uniform1(engine1) ;
double r2 = uniform1(engine1) ;
x = sqrt(-2 * log (r1)) *cos (2 * PI *r2) *stdev ;
y = sqrt(-2 * log (r1)) *sin (2 * PI *r2) *stdev ;
}
