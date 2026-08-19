//
// Created by Oscar Guevara Viveros on 7/8/26.
//
#include <cmath>
#include "paperMath.h"
#include <utility>

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

int paperMath::calcK(double phi) //pi/phi
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

double paperMath::calcGamma(int mu) //3^1/mu+2
{
    return std::pow(3.0, 1.0/(mu + 2));
}


std::vector<double> paperMath::generateLambdaSet(double gamma, int pMin, int pMax) //is gamma^p
{
    std::vector<double> lambdas;
    for (int p = pMin; p <= pMax; p++)
    {
        lambdas.push_back(std::pow(gamma, p));
    }
    return lambdas;
}

std::pair<int,int> paperMath::calcLambdaExponentRange(double gamma, double minSpacing, double maxSpread, int mu) //calc p
{
    double targetMin = minSpacing / (mu + 1); //min/10 // smallest scale worth trying
    double targetMax = maxSpread / mu;   //min/9       // largest scale worth trying
    int pMin = static_cast<int>(std::floor(std::log(targetMin) / std::log(gamma)));
    int pMax = static_cast<int>(std::ceil(std::log(targetMax) / std::log(gamma)));
    return {pMin, pMax};
}