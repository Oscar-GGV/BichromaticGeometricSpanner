//
// Created by Oscar Guevara Viveros on 7/9/26.
//

#ifndef BICHROMATICGEOMETRICSPANNER_TILE_H
#define BICHROMATICGEOMETRICSPANNER_TILE_H
#include "ColoredPoint.h"
static constexpr int RED_SEEN = 1; //01
static constexpr int BLUE_SEEN = 2; //10

class Tile
{
public:
    Tile(int i, int j); //constructor

    void addPoint(const ColoredPoint& p); //reference to point p

    const std::vector<ColoredPoint>& getPoints() const;

    size_t size() const;

    int getI() const;

    int getJ() const;

    int colorFlag() const; //0 = empty, 1= red, 2 = blue, 3 = bichromatic

    bool isMonochromatic() const; //true if 1 or 2 and non empty

    bool isBichromatic() const; //true if 3

private:

    int i_, j_;

    std::vector<ColoredPoint> points_; //points that live in this object

    int colorFlag_ = 0; //starts empty 00



};


#endif //BICHROMATICGEOMETRICSPANNER_TILE_H
