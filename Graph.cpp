//
// Created by Oscar Guevara Viveros on 7/26/26.
//

#include "Graph.h"
bool Graph::addEdge(const ColoredPoint& a, const ColoredPoint& b)
{
    //graph is full of undirected edges r*b* is the same as b*r*, this helps catch duplicates
   if (a.isRed == b.isRed) return false;

    int idA = a.number;
    int idB = b.number;
    auto key = (idA < idB) ? std::make_pair(idA, idB) : std::make_pair(idB, idA);

    if (edgeIds_.count(key)) return false;

    edgeIds_.insert(key);
    edges_.emplace_back(a, b);
    return true;
}

const std::vector<std::pair<ColoredPoint, ColoredPoint>>& Graph::getEdges() const
{
    return edges_;
}

size_t Graph::edgeCount() const
{
    return edges_.size();
}