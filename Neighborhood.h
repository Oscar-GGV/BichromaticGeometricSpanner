//
// Created by Oscar Guevara Viveros on 7/27/26.
//

#ifndef BICHROMATICGEOMETRICSPANNER_NEIGHBORHOOD_H
#define BICHROMATICGEOMETRICSPANNER_NEIGHBORHOOD_H
#include "TileGrid.h"

struct Neighborhood
{
    bool hasRed = false;
    bool hasBlue = false;

    bool isMonochromatic() const; //true if 1 or 2
    bool isBichromatic() const; //true if 3


};

Neighborhood buildNeighborhood(TileGrid& grid, int i, int j);

#endif //BICHROMATICGEOMETRICSPANNER_NEIGHBORHOOD_H
