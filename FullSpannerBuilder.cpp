//
// Created by Oscar Guevara Viveros on 8/10/26.
//

#include "FullSpannerBuilder.h"
#include "paperMath.h"
#include "TileGrid.h"
#include "SpannerBuilder.h"
#include <cmath>
#include <limits>
#include <iostream>

// FullSpannerBuilder.cpp — build the lookup once, in the constructor
FullSpannerBuilder::FullSpannerBuilder(double epsilon, int mu, std::vector<ColoredPoint> points)
    : epsilon_(epsilon), mu_(mu), points_(std::move(points))
{
    delta_ = paperMath::calcDelta(epsilon_); //calc delta
    for (const auto& p : points_) //for all p in points
        pointsByNumber_[p.number] = p;
}

double FullSpannerBuilder::findMinPairwiseDistance() const
{
    double minDist = std::numeric_limits<double>::max();
    for (size_t a = 0; a < points_.size(); a++)
    {
        for (size_t b = a + 1; b < points_.size(); b++)
        {
            double dx = points_[a].point.x() - points_[b].point.x();
            double dy = points_[a].point.y() - points_[b].point.y();
            double dist = std::sqrt(dx * dx + dy * dy);
            minDist = std::min(minDist, dist);
        }
    }
    return minDist;
}

double FullSpannerBuilder::findBoundingBoxDiagonal() const //similar to what sfml ues for the point boundary for window size, essentially the boundary of all points
{
    double minX = points_[0].point.x(), maxX = points_[0].point.x();
    double minY = points_[0].point.y(), maxY = points_[0].point.y();
    for (const auto& p : points_)
    {
        minX = std::min(minX, p.point.x());
        maxX = std::max(maxX, p.point.x());
        minY = std::min(minY, p.point.y());
        maxY = std::max(maxY, p.point.y());
    }
    double width = maxX - minX;
    double height = maxY - minY;
    return std::sqrt(width * width + height * height);
}

std::vector<ColoredPoint> FullSpannerBuilder::transformPoints(double theta, double lambda, bool shifted) const
{
    std::vector<ColoredPoint> transformed;
    transformed.reserve(points_.size()); //used so that there arent any memory p

    double cosT = std::cos(-theta);
    double sinT = std::sin(-theta);

    for (const auto& p : points_)
    {
        double x = p.point.x();
        double y = p.point.y();

        if (shifted)
        {
            y -= 0.5;
        }

        double xr = x * cosT - y * sinT;
        double yr = x * sinT + y * cosT;

        double xs = xr / lambda;
        double ys = yr / lambda;

        ColoredPoint np;
        np.point = Kernel::Point_2(xs, ys);
        np.isRed = p.isRed;
        np.number = p.number;
        transformed.push_back(np);
    }

    return transformed;
}

Graph FullSpannerBuilder::buildFullSpanner()
{
    Graph finalGraph;

    double gamma = paperMath::calcGamma(mu_);
    double phi = paperMath::calcPhi(delta_, mu_);
    int k = paperMath::calcK(phi);
    std::vector<double> phiSet = paperMath::generatePhiSet(k);

    double minSpacing = findMinPairwiseDistance();
    double maxSpread = findBoundingBoxDiagonal();
    auto [pMin, pMax] = paperMath::calcLambdaExponentRange(gamma, minSpacing, maxSpread, mu_);
    std::vector<double> lambdaSet = paperMath::generateLambdaSet(gamma, pMin, pMax);



    std::cout << "Trying " << phiSet.size() << " angles x " << lambdaSet.size()
              << " scales x 2 (T/T') = " << (phiSet.size() * lambdaSet.size() * 2)
              << " total tilings\n";

    for (double theta : phiSet)
    {
        for (double lambda : lambdaSet)
        {
            for (bool shifted : {false, true})
            {
                size_t before = finalGraph.edgeCount();

                std::vector<ColoredPoint> transformed = transformPoints(theta, lambda, shifted);
                TileGrid grid(1.0, delta_);
                for (const auto& p : transformed)
                    grid.insertPoint(p);

                Graph stepGraph = buildSpanner(grid);
                for (const auto& [a, b] : stepGraph.getEdges())
                {
                    const ColoredPoint& originalA = pointsByNumber_.at(a.number);
                    const ColoredPoint& originalB = pointsByNumber_.at(b.number);

                    finalGraph.addEdge(originalA, originalB);

                    
                }

                size_t after = finalGraph.edgeCount();

                // std::cout << "theta=" << theta << " lambda=" << lambda << " shifted=" << shifted
                //           << "  new edges: " << (after - before) << "  total: " << after << "\n";

            }
        }
    }

    return finalGraph;
}