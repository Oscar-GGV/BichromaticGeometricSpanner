//
// Created by Oscar Guevara Viveros on 8/10/26.
//

#ifndef BICHROMATICGEOMETRICSPANNER_FULLSPANNERBUILDER_H
#define BICHROMATICGEOMETRICSPANNER_FULLSPANNERBUILDER_H
#include <vector>
#include <unordered_map>
#include "ColoredPoint.h"
#include "Graph.h"

class FullSpannerBuilder
{
public:
    FullSpannerBuilder(double epsilon, int mu, std::vector<ColoredPoint> points);

    Graph buildFullSpanner(); //final product should be a graph that has the edges added from all the angles, scales, and shifts

private:
    double epsilon_;
    int mu_;
    double delta_;
    std::vector<ColoredPoint> points_;

    std::vector<ColoredPoint> transformPoints(double theta, double lambda, bool shifted) const;
    double findMinPairwiseDistance() const;
    double findBoundingBoxDiagonal() const;
    std::unordered_map<int, ColoredPoint> pointsByNumber_;
};


#endif //BICHROMATICGEOMETRICSPANNER_FULLSPANNERBUILDER_H
