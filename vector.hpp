#pragma once  // needed for preprocessing

//imports
#include <iostream>
#include <math.h>
#include <vector>

class Vector{
    private:
        double coords[3]; // the three coordinates

    public:
        // The explicit keyword indicates the Vector’s constructor cannot be called from implicit conversions.
        explicit Vector(double x = 0., double y = 0., double z = 0.)
        {
            coords[0] = x;
            coords[1] = y;
            coords[2] = z;
            };
            Vector &operator+=(const Vector &b)
            {
                coords[0] += b[0];
                coords[1] += b[1];
                coords[2] += b[2];
                return *this;
            }
            // returns a const double - meaning you cant change it later
            // const after args means you promise you wont change args
            const double &operator[](int i) const { return coords[i]; }
            // NOT SURE WHY WE NEED TWO ??
            double &operator[](int i) { return coords[i]; }
};
// addition of two vectors
Vector operator+(const Vector &a, const Vector &b){
    return Vector(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}
// subtraction of two vectors
Vector operator-(const Vector &a, const Vector &b){
    return Vector(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
}
// negation
Vector operator-(const Vector &b){
    return Vector(- b[0], - b[1], - b[2]);
}
// dot product
double dot(const Vector &a, const Vector &b){
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
// norm of a vector - length 
double norm(const Vector &a){
    return sqrt(pow(a[0], 2) + pow(a[1], 2) + pow(a[2], 2));
}
// cross multiplication of two vectors
Vector cross(const Vector &a, const Vector &b){
    return Vector(a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]);
}
// normalization
// means dividing it by its length in order to make it length one
Vector normalization(const Vector &a){
    double nrm = norm(a);
    return Vector(a[0] / nrm, a[1] / nrm, a[2] / nrm);
}
// multiplication - double * vector
// returns vector
Vector operator*(const double t, const Vector &a){
    return Vector(t * a[0], t * a[1], t * a[2]);
}
// multiplication - vector * double
// returns vector
Vector operator*(const Vector &a, const double t){
    return Vector(t * a[0], t * a[1], t * a[2]);
}
// division - vector/double
// returns vector
Vector operator/(const Vector &a, const double t){
    return Vector(a[0]/t, a[1]/t, a[2]/t);
}
// division - double/vector
Vector operator/(const double t, const Vector &a){
    return Vector(a[0] / t, a[1] / t, a[2] / t);
}
//print the vector as [x,y,z]
void print(Vector a){
    std::cout << "[" << a[0] << ", " << a[1] << ", " << a[2] << "]" << std::endl;
}
Vector average(std::list<Vector> colours){
    double n = colours.size();
    Vector result = Vector(0,0,0); // total of all colour vectors added
    for (std::list<Vector>::iterator it = colours.begin(); it != colours.end(); it++){
    //for(int i = 0; i < n-1; i++){
        // const Vector temp = ;
        result = result + *it;
    }
    //divide by size of list
    return result/n;
}