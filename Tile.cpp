//
// Created by Oscar Guevara Viveros on 7/9/26.
//

#include "Tile.h"



Tile::Tile(int i, int j) : i_(i), j_(j){}//constructor  given i and j create object tile with i and j

void Tile::addPoint(const ColoredPoint& p) //used to add points that pertaun to the tile
{
    points_.push_back(p); //add to the vertext of points within the tile
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

