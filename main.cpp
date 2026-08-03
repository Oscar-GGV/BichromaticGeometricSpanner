
#include <iostream>
#include "InputHelper.h"
#include "paperMath.h"
#include "TileGrid.h"
#include "Graph.h"
#include "SpannerBuilder.h"

int main()
{
    double epsilon = InputHelper::getEpsilon();
    double delta = paperMath::calcDelta(epsilon);

    std::cout << "file name? ";
    std::string filename;
    std::cin >> filename;

    std::vector<ColoredPoint> points = InputHelper::readPointsFromFile(filename);
    if (points.empty())
    {
        std::cout << "No points\n";
        return 1;
    }

    TileGrid grid(1.0, delta);
    for (const auto& p : points)
    {
        grid.insertPoint(p);
    }

    Graph G = buildSpanner(grid);
    std::cout << "Edge count: " << G.edgeCount() << "\n\n";
    for (const auto& [a, b] : G.getEdges()) {
        std::cout << "Edge " << a.number << " (" << (a.isRed ? "R" : "B") << ") -- "
                   << b.number << " (" << (b.isRed ? "R" : "B") << ")   "
                   << "[" << a.point.x() << "," << a.point.y() << "] -- ["
                   << b.point.x() << "," << b.point.y() << "]\n";
    }
    return 0;

}