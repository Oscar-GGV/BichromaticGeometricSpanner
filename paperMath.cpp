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

int paperMath::calcK(double phi)
{
    double pi = std::acos(-1.0);
    int k = static_cast<int>(std::ceil(pi/phi));
return k;
}
//discrete set of angles
std::vector<double> paperMath::generatePhiSet(int k)
{
    std::vector<double> angles;
    double pi = std::acos(-1.0);
    for (int r = 0; r < k; r++)
    {
        angles.push_back(2.0 * r * pi/k);
    }
    return angles;
}