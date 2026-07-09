//
// Created by Oscar Guevara Viveros on 7/2/26.

#ifndef BICHROMATICGEOMETRICSPANNER_COLOREDPOINT_H
#define BICHROMATICGEOMETRICSPANNER_COLOREDPOINT_H

#include <CGAL/Simple_cartesian.h>
using Kernel = CGAL::Simple_cartesian<double>;


struct ColoredPoint
{
    Kernel::Point_2 point;
    bool isRed;
    int number;
};


#endif //BICHROMATICGEOMETRICSPANNER_COLOREDPOINT_H
