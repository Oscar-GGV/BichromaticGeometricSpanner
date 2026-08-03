//
// Created by Oscar Guevara Viveros on 7/7/26.
//

#ifndef BICHROMATICGEOMETRICSPANNER_INPUTHELPER_H
#define BICHROMATICGEOMETRICSPANNER_INPUTHELPER_H
#include <vector>
#include "ColoredPoint.h"

class InputHelper
{
    public:
    static double getEpsilon();

    static double checkDouble();

    static int checkInt();

    static bool redChecker();

    //Filereading
    static std::vector<ColoredPoint> readPointsFromFile(const std::string& filename);

};


#endif //BICHROMATICGEOMETRICSPANNER_INPUTHELPER_H
