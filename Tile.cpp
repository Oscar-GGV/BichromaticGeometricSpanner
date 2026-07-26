//
// Created by Oscar Guevara Viveros on 7/9/26.
//

#include "Tile.h"



Tile::Tile(int i, int j) : i_(i), j_(j){}//constructor  given i and j create object tile with i and j

void Tile::addPoint(const ColoredPoint& p) //used to add points that pertaun to the tile
{
    points_.push_back(p); //add to the vertext of points within the tile
    colorFlag_ |= p.isRed ? RED_SEEN : BLUE_SEEN; //if point is red or in red seen otherwise or in blue seen
    //or turns a bit on

    int newIndex = static_cast<int>(points_.size()) - 1; //index of the point that was just added (used because of problem witj vector and space in memory)

    if (p.isRed) {
        if (leftmostRed_  == -1 || p.point.x() < points_[leftmostRed_].point.x())  leftmostRed_  = newIndex;
        if (rightmostRed_ == -1 || p.point.x() > points_[rightmostRed_].point.x()) rightmostRed_ = newIndex;
    } else {
        if (leftmostBlue_  == -1 || p.point.x() < points_[leftmostBlue_].point.x())  leftmostBlue_  = newIndex;
        if (rightmostBlue_ == -1 || p.point.x() > points_[rightmostBlue_].point.x()) rightmostBlue_ = newIndex;
    }
}

const std::vector<ColoredPoint>& Tile::getPoints() const //returns the points in the vertex within the tile
{
    return points_;
}


size_t Tile::size() const //returns how many points are in the tile
{
    return points_.size();
}

int Tile::getI() const { return i_; } //returns the i variable of tile

int Tile::getJ() const { return j_; } //returns the j variable of tile

int Tile::colorFlag() const
{
    return colorFlag_;
}

bool Tile::isMonochromatic() const
{
    return colorFlag_== RED_SEEN || colorFlag_ == BLUE_SEEN; //returns true of colorFlag_ is exactly 1 or 2
}

bool Tile::isBichromatic() const
{
    return colorFlag_ == (RED_SEEN | BLUE_SEEN); // == 3
}

const ColoredPoint* Tile::leftmostRed() const
{
    return leftmostRed_ == -1 ? nullptr : &points_[leftmostRed_];
}
const ColoredPoint* Tile::rightmostRed() const
{
    return rightmostRed_ == -1 ? nullptr : &points_[rightmostRed_];
}
const ColoredPoint* Tile::leftmostBlue() const
{
    return leftmostBlue_ == -1 ? nullptr : &points_[leftmostBlue_];
}
const ColoredPoint* Tile::rightmostBlue() const
{
    return rightmostBlue_ == -1 ? nullptr : &points_[rightmostBlue_];
}
