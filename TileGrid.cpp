//
// Created by Oscar Guevara Viveros on 7/11/26.
//
#include "TileGrid.h"
TileGrid::TileGrid(double width, double height) : width_(width), height_(height) {} //constructor


std::pair<int, int> TileGrid::computeIndex(const ColoredPoint& p) const //function that is used to compute the tile
{ //given a point return the pair i and j
    int i = static_cast<int>(std::floor(p.point.x() / width_));
    int j = static_cast<int>(std::floor(p.point.y() / height_));
    return {i,j};
}


void TileGrid::insertPoint(const ColoredPoint& p)
{
    auto key = computeIndex(p);
    auto it = tileMap_.find(key);
    if (it==tileMap_.end())
    {
        it = tileMap_.emplace(key, Tile(key.first, key.second)).first;
    }
    it->second.addPoint(p);
}

Tile* TileGrid::getTile(int i, int j)
{
    auto it = tileMap_.find({i, j});
    return (it != tileMap_.end()) ? &it->second: nullptr;
}

size_t TileGrid::tileCount() const
{
    return tileMap_.size();

}



