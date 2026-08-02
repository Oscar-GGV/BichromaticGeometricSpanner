//
// Created by Oscar Guevara Viveros on 7/30/26.
//

#include "SpannerBuilder.h"
#include <iostream>
//for input and output
#include <vector>
//used for saving all the points
#include "ColoredPoint.h"
//used for the ColoredPoint struct consisting of 2_d point and a color and a number

#include "InputHelper.h"

#include "paperMath.h"

#include "TileGrid.h"


int main()
{


    //epsilon = (0 to 1) non-inclusive
    double epsilon = InputHelper::getEpsilon(); //uses the getEpsilon function from InputHelper
    double delta = paperMath::calcDelta(epsilon);

    std::cout << "How many points? ";
    int number = InputHelper::checkInt(); //uses checkInt from InputHelper

    std::vector<ColoredPoint> points; //array of ColoredPoint objects
    std::cout << "Rules: \n NO duplicate points\n";
    std::cout << "Each Color must have a color\n Red is 0 Blue is 1\n";
    int idCounter = 0;

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
        point.number = idCounter++;
        points.push_back(point);
    }
    //grid tile
    TileGrid grid(1.0, delta); //width 1, height delta THIS IS THE CASE FOR theta = 0, lamda = 1

    for (const auto& p : points)
    {
        grid.insertPoint(p);
    }
    Graph G = buildSpanner(grid);
    std::cout << "Edge count:" << G.edgeCount() << "\n";
    /* Case 0 Expect 0 edges:
    Epsilon: 0.7
    How many points? 2
    x: 0.5
    y: 0.05
    color: 0
    x: 10.5
    y: 0.05
    color: 0


    Case 1 : expect 1 edge
    Epsilon: 0.7
    How many points? 2
    x: 0.5
    y: 0.05
    color: 0
    x: 10.5
    y: 0.05
    color: 1


    Case 3: expect 2 edges
    Epsilon: 0.7
    How many points? 4
    x: 0.5
    y: 0.05
    color: 0
    x: 0.5
    y: 0.15
    color: 1
    x: 10.5
    y: 0.05
    color: 1
    x: 10.5
    y: 0.15
    color: 0


    case 2: expect 1 edge
    Epsilon: 0.7
    How many points? 3
    x: 0.5
    y: 0.05
    color: 0
    x: 10.5
    y: 0.05
    color: 1
    x: 10.5
    y: 0.15
    color: 0
    */


    //edge output
    for (const auto& [a, b] : G.getEdges())
    {
        std::cout << "Edge " << a.number << " (" << (a.isRed ? "Red" : "Blue") << ") -- " << b.number << " (" << (b.isRed ? "Red" : "blue") << ") " << "[" << a.point.x() << "," << a.point.y() << "] -- [" << b.point.x() << "," << b.point.y() << "]\n";
    }

}

