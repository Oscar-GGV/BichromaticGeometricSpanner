//
// Created by Oscar Guevara Viveros on 7/12/26.
//

#ifndef BICHROMATICGEOMETRICSPANNER_PAIRHASH_H
#define BICHROMATICGEOMETRICSPANNER_PAIRHASH_H
#include <utility>
#include <cstddef>
#include <functional>

struct PairHash
{
    std::size_t operator() (const std::pair<int,int>& p) const {
    return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);//std::hash<int>()(p,first)
        //creates temporary std::hash<int> object and calls it
        //smart idea to shift bits of the second hash by 1 to avoid collisions
        //^ is xor
    }
};


#endif //BICHROMATICGEOMETRICSPANNER_PAIRHASH_H
