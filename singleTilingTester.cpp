//
// Created by Oscar Guevara Viveros on 8/12/26.
//
//
// SingleTilingTester.cpp
//
// Tests exactly ONE tiling:
//   theta   = 0
//   lambda  = 1
//   shifted = false
//

#include <iostream>
#include <vector>
#include <cmath>

#include "InputHelper.h"
#include "paperMath.h"
#include "TileGrid.h"
#include "SpannerBuilder.h"
#include "Graph.h"

int main()
{


    double epsilon = InputHelper::getEpsilon();
    int mu = 9;

    std::cout << "file name? ";

    std::string filename;
    std::cin >> filename;

    std::vector<ColoredPoint> points =
        InputHelper::readPointsFromFile(filename);

    if (points.empty())
    {
        std::cout << "No points\n";
        return 1;
    }

   //param
    double delta = paperMath::calcDelta(epsilon);

    // FIRST TEST:
    // One angle, one scale, unshifted.
    double theta = 0.0;
    double lambda = 1.0;
    bool shifted = false;

    std::cout << "\n===== SINGLE TILING TEST =====\n";
    std::cout << "epsilon = " << epsilon << "\n";
    std::cout << "mu      = " << mu << "\n";
    std::cout << "delta   = " << delta << "\n";
    std::cout << "theta   = " << theta << "\n";
    std::cout << "lambda  = " << lambda << "\n";
    std::cout << "shifted = " << std::boolalpha << shifted << "\n";

//transform points

    std::vector<ColoredPoint> transformed;
    transformed.reserve(points.size());

    double cosT = std::cos(-theta);
    double sinT = std::sin(-theta);

    for (const auto& p : points)
    {
        double x = p.point.x();
        double y = p.point.y();

        // For this first test shifted == false,
        // so this does nothing.
        if (shifted)
        {
            y -= 0.5;
        }

        // Inverse rotation
        double xr = x * cosT - y * sinT;
        double yr = x * sinT + y * cosT;

        // Inverse scaling
        double xs = xr / lambda;
        double ys = yr / lambda;

        ColoredPoint np;
        np.point = Kernel::Point_2(xs, ys);
        np.isRed = p.isRed;
        np.number = p.number;

        transformed.push_back(np);
    }

    //build one tile grid
    TileGrid grid(1.0, delta);

    for (const auto& p : transformed)
    {
        grid.insertPoint(p);
    }

    std::cout << "Occupied tiles: " << grid.tileCount() << "\n";

   //build spanner for one tiling
    Graph G = buildSpanner(grid);

   //results
    std::cout << "\n===== RESULT =====\n";
    std::cout << "Edges: " << G.edgeCount() << "\n";

    std::cout << "\nEdges:\n";

    for (const auto& [a, b] : G.getEdges())
    {
        std::cout << a.number
                  << " -- "
                  << b.number
                  << "\n";
    }

    return 0;
}