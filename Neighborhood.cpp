//
// Created by Oscar Guevara Viveros on 7/27/26.
//

#include "Neighborhood.h"

bool Neighborhood::isMonochromatic() const
{
    return hasRed != hasBlue;
}

bool Neighborhood::isBichromatic() const
{
    return hasRed && hasBlue;
}

Neighborhood buildNeighborhood(TileGrid& grid, int i, int j)
{
    Neighborhood n;
    //3x3 traversal
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            Tile* t = grid.getTile(i + di, j + dj);
            if (t == nullptr) continue;
            if (t->hasRed()) n.hasRed = true;
            if (t->hasBlue()) n.hasBlue = true;
        }
    }
    return n;
}

const ColoredPoint* rightmostRedInNeighborhood(TileGrid& grid, int i, int j)
{
    const ColoredPoint* best = nullptr;
    for (int di = -1; di <=1; di++)
    {
        for (int dj = -1; dj <= 1; dj++) {
            Tile* t = grid.getTile(i + di, j + dj);
            if (t == nullptr) continue;
            const ColoredPoint* can = t->rightmostRed();
            if (can && (!best || can->point.x() > best->point.x())) best = can;
        }
    }
    return best;
}

const ColoredPoint* leftmostBlueInNeighborhood(TileGrid& grid, int i, int j)
{
    const ColoredPoint* best = nullptr;
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            Tile* t = grid.getTile(i + di, j + dj);
            if (t == nullptr) continue;
            const ColoredPoint* can = t->leftmostBlue();
            if (can && (!best || can->point.x() < best->point.x())) best = can;
        }
    }
    return best;
}

const ColoredPoint* rightmostBlueInNeighborhood(TileGrid& grid, int i, int j)
{
    const ColoredPoint* best = nullptr;
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            Tile* t = grid.getTile(i + di, j + dj);
            if (t == nullptr) continue;
            const ColoredPoint* can = t->rightmostBlue();
            if (can && (!best || can->point.x() > best->point.x())) best = can;
        }
    }
    return best;
}

const ColoredPoint* leftmostRedInNeighborhood(TileGrid& grid, int i, int j)
{
    const ColoredPoint* best = nullptr;
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            Tile* t = grid.getTile(i + di, j + dj);
            if (t == nullptr) continue;
            const ColoredPoint* can = t->leftmostRed();
            if (can && (!best || can->point.x() < best->point.x())) best = can;
        }
    }
    return best;
}