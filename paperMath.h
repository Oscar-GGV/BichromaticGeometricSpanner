//
// Created by Oscar Guevara Viveros on 7/8/26.
//

#ifndef BICHROMATICGEOMETRICSPANNER_PAPERMATH_H
#define BICHROMATICGEOMETRICSPANNER_PAPERMATH_H

#include <vector>
class paperMath
{
public:
    static double calcDelta(double epsilon);

    static double calcPhi(double delta, int mu);

    static int calcK(double phi); //used for phi set

    static std::vector<double> generatePhiSet(int k); //set of discrete angles

    static double calcGamma(int mu); //3^1/(mu + 2)

    static std::vector<double> generateLambdaSet(double gamma, int pMin, int pMax); //scale

    static std::pair<int,int> calcLambdaExponentRange(double gamma, double minSpacing, double maxSpread, int mu); //p


};
#endif //BICHROMATICGEOMETRICSPANNER_PAPERMATH_H
