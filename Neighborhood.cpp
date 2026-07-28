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
    for (int di = -1; di <= 1; ++di)
    {
        for (int dj = -1; dj <= 1; ++dj)
        {
            Tile* t = grid.getTile(i + di, j + dj);
            if (t == nullptr) continue;
            if (t->hasRed()) n.hasRed = true;
            if (t->hasBlue()) n.hasBlue = true;
        }
    }
    return n;
}