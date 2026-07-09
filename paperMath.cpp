//
// Created by Oscar Guevara Viveros on 7/8/26.
//
#include <cmath>
#include "paperMath.h"


double paperMath::calcDelta(double epsilon)
{
    double delta = sqrt(1/epsilon);
    return delta;
}