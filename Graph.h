//
// Created by Oscar Guevara Viveros on 7/26/26.
//

#ifndef BICHROMATICGEOMETRICSPANNER_GRAPH_H
#define BICHROMATICGEOMETRICSPANNER_GRAPH_H
#include "ColoredPoint.h"
#include <vector>
#include <set>
#include <utility>

class Graph
{
public:
    bool addEdge(const ColoredPoint& a, const ColoredPoint& b); //given two points make an edge

    const std::vector<std::pair<ColoredPoint, ColoredPoint>>& getEdges() const; //return a vector of all edges

    size_t edgeCount() const;

private:
    std::vector<std::pair<ColoredPoint, ColoredPoint>> edges_; //vector of edges
    std::set<std::pair<int, int>> edgeIds_;
};


#endif //BICHROMATICGEOMETRICSPANNER_GRAPH_H
