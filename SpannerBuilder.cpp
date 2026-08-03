//
// Created by Oscar Guevara Viveros on 7/26/26.
//

#include "SpannerBuilder.h"
#include "Neighborhood.h"
constexpr int MU = 9;
constexpr int MU_PLUS_1 = MU + 1;

//case 1: both N(i, j) and N(i + 10, j) are monochromatic of diff colors (bistar centered at r* b*)
void case1(Graph& G, TileGrid& grid, Tile& a, Tile& b, int i, int j, bool aIsRed)
{
    if (aIsRed)
    {
        const ColoredPoint* rStar =  rightmostRedInNeighborhood(grid, i, j);
        const ColoredPoint* bStar = leftmostBlueInNeighborhood(grid, i + MU_PLUS_1, j);

        for (const auto& p : b.getPoints())
            if (!p.isRed) G.addEdge(*rStar, p);

        for (const auto& p : a.getPoints())
            if (p.isRed) G.addEdge(*bStar, p);

        G.addEdge(*rStar, *bStar);
    }
    else
    {
        const ColoredPoint* bStar = rightmostBlueInNeighborhood(grid, i, j);
        const ColoredPoint* rStar = leftmostRedInNeighborhood(grid, i + MU_PLUS_1, j);

        for (const auto& p : b.getPoints())
            if (p.isRed) G.addEdge(*bStar, p);

        for (const auto& p : a.getPoints())
            if (!p.isRed) G.addEdge(*rStar, p);

        G.addEdge(*bStar, *rStar);
    }
}
//end of case 1

//case2 exactly one of either n(i,j) or n(i + 10, j) is mono and the other is bichro
void case2(Graph& G, TileGrid& grid, Tile& a, Tile& b, int i, int j, bool aIsMono)
{
    if (aIsMono)
    {
        if (a.hasRed())
        {
            const ColoredPoint* bStar = leftmostBlueInNeighborhood(grid, i + MU_PLUS_1, j);
            for (const auto& p : a.getPoints())
                if (p.isRed) G.addEdge(*bStar, p);
                else
                {
                    const ColoredPoint* rStarStar = leftmostRedInNeighborhood(grid, i + MU_PLUS_1, j);
                    for (const auto& p : a.getPoints())
                        if (!p.isRed) G.addEdge(*rStarStar, p);
                }
        }
        else
        {
            if (b.hasRed())
            {
                const ColoredPoint* bStar = leftmostBlueInNeighborhood(grid, i, j);
                for (const auto& p : b.getPoints())
                    if (p.isRed) G.addEdge(*bStar, p);
                    else
                    {
                        const ColoredPoint* rStarStar = leftmostRedInNeighborhood(grid, i, j);
                        for (const auto& p : b.getPoints())
                            if (!p.isRed) G.addEdge(*rStarStar, p);
                    }
            }
        }
    }
}
            //end of case 2

            //case 3 Both N(i,j) and N(i + mu + 1, j) are bichromatic, two edges

            void case3(Graph& G, TileGrid& grid, Tile& a, Tile& b, int i, int j)
{
    const ColoredPoint* rStar = rightmostRedInNeighborhood(grid, i, j);
    const ColoredPoint* bstar = leftmostBlueInNeighborhood(grid, i + MU_PLUS_1, j);
    G.addEdge(*rStar, *bstar);

    const ColoredPoint* rStarStar = leftmostRedInNeighborhood(grid, i + MU_PLUS_1, j);
    const ColoredPoint* bStarStar = rightmostBlueInNeighborhood(grid, i, j);
    G.addEdge(*rStarStar, *bStarStar);
}

//end of case 3

Graph buildSpanner(TileGrid& grid)
{
    Graph G;

    for (auto& [key, tileA] : grid)
    {
       auto[i,j] = key; //get i, j for key

        Tile* tileBPtr = grid.getTile(i + MU_PLUS_1, j); //get tile + 10 away
        if (tileBPtr == nullptr) continue; //if it doesnt exist continue
        Tile& tileB = *tileBPtr; //if such a tile does exist it is now tile b

        Neighborhood N1 =  buildNeighborhood(grid, i, j);
        Neighborhood N2 =  buildNeighborhood(grid, i + MU_PLUS_1, j);

        if (N1.isMonochromatic() && N2.isMonochromatic())
        {
            bool aIsRed = tileA.hasRed();
            bool bIsRed = tileB.hasRed();
            if (aIsRed == bIsRed) continue; //case 0 no edges added same color mono neighbors
            case1(G, grid, tileA, tileB, i, j, aIsRed);
        }
        else if (N1.isMonochromatic() != N2.isMonochromatic())
        {
            case2(G, grid, tileA, tileB, i, j, N1.isMonochromatic());
        }
        else
        {
            case3(G, grid, tileA, tileB, i, j);
        }
    }
    return G;

}


