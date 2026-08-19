Implementation of an algorithm found in "Bichromatic Geometric Spanners"
by the Authors Theodore Fung, Csaba D. Tóth

Overview:
  This project implements the algorithm described in Bichromatic (3 + ε)-Spanners in the Plane. The implementation constructs a sparse geometric graph connecting red and blue points while approximating shortest-path distances by a stretch factor of 3+ε.

Theodore Fung, Csaba D. Tóth
"Bichromatic Geometric Spanners"
https://arxiv.org/abs/2607.10062

How to Run:
Download CGAL EIGEN library

Run the executable from the project root directory, and when prompted for a points file, enter `points.txt` (or the path to your own points file, relative to the project root).

SpannerVisualizer executable is the standard 1 angle, 1 scale, 1 shift that the paper uses to describe cases
SpannerVisualizer2 executable is the full program

Points file format:
One point per line: `x y color`, where `color` is `0` for red or `1` for blue.

Example:
```
0.5 0.05 0
0.5 0.15 1
10.5 0.05 1
10.5 0.15 0
```
  


Features:
  - Recieves epsilon from the user
  - Gets points from the user(x,y, and color)
  - Calculates the delta described in the article
  - Creates a grid based on the delta described in the article
  - For each point, calulate i and j for the tile, if such a tile has already been created add the point to that tile, otherwise create a new tile.
  - There is a collection of tiles held within an unordered_tree, Key is (i, j) and the value is the tile itself with the collection of points within it
  - created a test to check the functionality of the tiles and tile flags/grid in general

UML Class Diagram:
```mermaid
classDiagram
    direction LR
 
    class ColoredPoint {
        <<struct>>
        +Point_2 point
        +bool isRed
        +int number
    }
 
    class Tile {
        -int i_
        -int j_
        -vector~ColoredPoint~ points_
        -int colorFlag_
        -int leftmostRed_
        -int rightmostRed_
        -int leftmostBlue_
        -int rightmostBlue_
        +Tile(int i, int j)
        +addPoint(ColoredPoint p) void
        +getPoints() vector~ColoredPoint~
        +size() size_t
        +getI() int
        +getJ() int
        +colorFlag() int
        +isMonochromatic() bool
        +isBichromatic() bool
        +hasRed() bool
        +hasBlue() bool
        +leftmostRed() ColoredPoint*
        +rightmostRed() ColoredPoint*
        +leftmostBlue() ColoredPoint*
        +rightmostBlue() ColoredPoint*
    }
 
    class PairHash {
        <<functor>>
        +operator()(pair~int,int~) size_t
    }
 
    class TileGrid {
        -double width_
        -double height_
        -unordered_map~pair~int,int~, Tile, PairHash~ tileMap_
        +TileGrid(double width, double height)
        +insertPoint(ColoredPoint p) void
        +getTile(int i, int j) Tile*
        +getTileForPoint(ColoredPoint p) Tile*
        +tileCount() size_t
        +begin()
        +end()
        -computeIndex(ColoredPoint p) pair~int,int~
    }
 
    class Neighborhood {
        <<struct>>
        +bool hasRed
        +bool hasBlue
        +isMonochromatic() bool
        +isBichromatic() bool
    }
 
    class NeighborhoodFns {
        <<free functions>>
        +buildNeighborhood(grid, i, j) Neighborhood
        +rightmostRedInNeighborhood(grid, i, j) ColoredPoint*
        +leftmostRedInNeighborhood(grid, i, j) ColoredPoint*
        +rightmostBlueInNeighborhood(grid, i, j) ColoredPoint*
        +leftmostBlueInNeighborhood(grid, i, j) ColoredPoint*
    }
 
    class Graph {
        -vector~pair~ColoredPoint,ColoredPoint~~ edges_
        -set~pair~int,int~~ edgeIds_
        +addEdge(ColoredPoint a, ColoredPoint b) bool
        +getEdges() vector~pair~ColoredPoint,ColoredPoint~~
        +edgeCount() size_t
    }
 
    class SpannerBuilder {
        <<free functions>>
        +buildSpanner(TileGrid grid) Graph
        -case1(G, grid, a, b, i, j, aIsRed) void
        -case2(G, grid, a, b, i, j, aIsMono) void
        -case3(G, grid, a, b, i, j) void
    }
 
    class FullSpannerBuilder {
        -double epsilon_
        -int mu_
        -double delta_
        -vector~ColoredPoint~ points_
        -unordered_map~int, ColoredPoint~ pointsByNumber_
        +FullSpannerBuilder(double epsilon, int mu, vector~ColoredPoint~ points)
        +buildFullSpanner() Graph
        -transformPoints(theta, lambda, shifted) vector~ColoredPoint~
        -findMinPairwiseDistance() double
        -findBoundingBoxDiagonal() double
    }
 
    class paperMath {
        <<utility>>
        +calcDelta(double epsilon) double
        +calcPhi(double delta, int mu) double
        +calcK(double phi) int
        +generatePhiSet(int k) vector~double~
        +calcGamma(int mu) double
        +generateLambdaSet(gamma, pMin, pMax) vector~double~
        +calcLambdaExponentRange(gamma, minSpacing, maxSpread, mu) pair~int,int~
    }
 
    class InputHelper {
        <<utility>>
        +getEpsilon() double
        +checkDouble() double
        +checkInt() int
        +redChecker() bool
        +readPointsFromFile(string filename) vector~ColoredPoint~
    }
 
    class main {
        <<driver>>
        +main() int
    }
 
    %% ---- relationships ----
    Tile "1" *-- "many" ColoredPoint : stores
    TileGrid "1" *-- "many" Tile : owns (tileMap_)
    TileGrid ..> PairHash : hashes (i,j) keys
    TileGrid ..> ColoredPoint : insertPoint / computeIndex
 
    Neighborhood <.. NeighborhoodFns : builds / returns
    NeighborhoodFns ..> TileGrid : 3x3 tile scan
    NeighborhoodFns ..> ColoredPoint : returns pointers
 
    Graph "1" o-- "many" ColoredPoint : edge endpoints
 
    SpannerBuilder ..> TileGrid : iterates tiles
    SpannerBuilder ..> Neighborhood : classifies tile pair
    SpannerBuilder ..> NeighborhoodFns : rightmost/leftmost lookups
    SpannerBuilder ..> Graph : builds & returns
 
    FullSpannerBuilder "1" *-- "many" ColoredPoint : points_ / pointsByNumber_
    FullSpannerBuilder ..> paperMath : angle/scale math
    FullSpannerBuilder ..> TileGrid : builds one grid per (theta, lambda, shift)
    FullSpannerBuilder ..> SpannerBuilder : calls buildSpanner per tiling
    FullSpannerBuilder ..> Graph : merges edges into finalGraph
 
    main ..> InputHelper : epsilon + points
    main ..> paperMath : calcDelta
    main ..> TileGrid : builds grid
    main ..> SpannerBuilder : buildSpanner
    main ..> Graph : prints edges
    InputHelper ..> ColoredPoint : readPointsFromFile
```


Dependencies:
- C++20
- CGAL (for points)
- CMAKE

Acknowledgements:
This project was developed as part of a Summer 2026 Research Experiences for Undergraduates (REU) program at California State University, Northridge. The REU program is supported by the National Science Foundation (NSF).

I would like to thank Csaba D. Tóth and Theodore Fung, for their guidance throughout this project.
  
