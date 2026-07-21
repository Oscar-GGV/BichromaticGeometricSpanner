//
// Created by Oscar Guevara Viveros on 7/8/26.
//

#ifndef BICHROMATICGEOMETRICSPANNER_PAPERMATH_H
#define BICHROMATICGEOMETRICSPANNER_PAPERMATH_H


class paperMath
{
public:
    static double calcDelta(double epsilon);

    static double calcPhi(double delta, int mu);

    static double calcK(double phi);

};
#endif //BICHROMATICGEOMETRICSPANNER_PAPERMATH_H
