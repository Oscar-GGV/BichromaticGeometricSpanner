//
// Created by Oscar Guevara Viveros on 7/11/26.
//

#ifndef BICHROMATICGEOMETRICSPANNER_TILEGRID_H
#define BICHROMATICGEOMETRICSPANNER_TILEGRID_H
#include "Tile.h"
#include "Pairhash.h"

class TileGrid
{
    public:

    TileGrid(double width, double height);//constructor takes the size of the tile as an arg

    void insertPoint(const ColoredPoint& p); // figures out which tile the point goes in

    Tile* getTile(int i, int j); //returns tile, takes input of i and j, used * here so that a pointer to tile gets returned in csdr tile is NULL

    size_t tileCount() const; //returns how many tiles currently exist in the grid ~const doesnt change anything abt the obj


private: //only reachable from inside TileGrid
    std::pair<int, int> computeIndex(const ColoredPoint& p) const; //::pair bundles two values together ~here two ints i, j
    //takes a point works out which tile it belongs to ~used by insert point

    double width_;
    double height_;//stores the side length of each tile ~set once in the constructor ~used by computeIndez to find out which
    //tile a given point coordinates fall into.

    std::unordered_map<std::pair<int, int>, Tile, PairHash> tileMap_; //hashMap that stores all the tiles
    //<KeyType, ValueType, HashFunction>
    //given a Key Type, look up a Value Type in O(1)
    //key type is the pair , Tile is the value,

};


#endif //BICHROMATICGEOMETRICSPANNER_TILEGRID_H
