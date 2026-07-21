//
// Created by Oscar Guevara Viveros on 7/9/26.
//

#ifndef BICHROMATICGEOMETRICSPANNER_TILE_H
#define BICHROMATICGEOMETRICSPANNER_TILE_H
#include "ColoredPoint.h"


class Tile
{
public:
    Tile(int i, int j); //constructor

    void addPoint(const ColoredPoint& p); //reference to point p

    const std::vector<ColoredPoint>& getPoints() const;

    size_t size() const;

    int getI() const;

    int getJ() const;

private:

    int i_, j_;

    std::vector<ColoredPoint> points_; //points that live in this object



};


#endif //BICHROMATICGEOMETRICSPANNER_TILE_H
