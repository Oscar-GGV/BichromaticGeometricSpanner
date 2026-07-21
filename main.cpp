#include <iostream>
//for input and output
#include <vector>
//used for saving all the points
#include "Coloredpoint.h"
//used for the ColoredPoint struct consisting of 2_d point and a color and a number

#include "InputHelper.h"

#include "paperMath.h"

#include "TileGrid.h"


int main()
{

    int mu = 9; //always 9

    //epsilon = (0 to 1) non-inclusive
    double epsilon = InputHelper::getEpsilon(); //uses the getEpsilon function from InputHelper
    double delta = paperMath::calcDelta(epsilon);

    std::cout << "How many points? ";
    int number = InputHelper::checkInt(); //uses checkInt from InputHelper

    std::vector<ColoredPoint> points; //array of ColoredPoint objects
    std::cout << "Rules: \n NO duplicate points\n";
    std::cout << "Each Color must have a color\n Red is 0 Blue is 1\n";

    for (int i = 0; i < number; i++) //add however many points the user wanted
    {
        //int color;
        ColoredPoint point;
        std::cout << "x: ";
        double x = InputHelper::checkDouble(); //uses checkDouble method in InputHelper
        std::cout << "y: ";
        double y = InputHelper::checkDouble(); //uses checkDouble method in InputHelper
       // std::cout << "\n;";
        std::cout << "color: ";
        point.isRed = InputHelper::redChecker(); //uses the redChecker method in InputHelper
        point.point = Kernel::Point_2(x,y);
        points.push_back(point);
    }
    //grid tile
    TileGrid grid(1.0, delta); //width 1, height delta THIS IS THE CASE FOR theta = 0, lamda = 1

    for (const auto& p : points)
    {
        grid.insertPoint(p);
    }

    std::cout << "Tiles created: " << grid.tileCount() << std::endl;
 /*for (ColoredPoint i : points)
 {
     std::cout << i.point << i.isRed << std::endl;
 }*/
}
