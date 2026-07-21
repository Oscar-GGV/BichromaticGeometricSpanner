//
// Created by Oscar Guevara Viveros on 7/8/26.
//
#include <cmath>
#include "paperMath.h"


double paperMath::calcDelta(double epsilon)
{
    double delta = sqrt(epsilon/7.0);
    return delta;
}

double paperMath::calcPhi(double delta, int mu) //double in radians returned
{
    double phi = std::atan(delta/(2*mu + 4));
    return phi;
}

double paperMath::calcK(double phi)
{
    double pi = std::acos(-1.0);
    double k = pi/phi;\
return k;
}