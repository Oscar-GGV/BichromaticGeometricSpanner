Implementation of an algorithm found in "Bichromatic Geometric Spanners"
by the Authors Theodore Fung, Csaba D. Tóth

Overview:
  This project implements the algorithm described in Bichromatic (3 + ε)-Spanners in the Plane. The implementation constructs a sparse geometric graph connecting red and blue points while approximating shortest-path distances by a stretch factor of 3+ε.
  
Theodore Fung, Csaba D. Tóth
"Bichromatic Geometric Spanners"
https://arxiv.org/abs/2607.10062


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
    -const ColoredPoint* leftmostRed_
    -const ColoredPoint* rightmostRed_
    -const ColoredPoint* leftmostBlue_
    -const ColoredPoint* rightmostBlue_

    +Tile(i,j)
    +addPoint(p)
    +getPoints()
    +size()
    +getI()
    +getJ()
    +hasRed()
    +hasBlue()
    +isMonochromatic()
    +isBichromatic()
    +leftmostRed()
    +rightmostRed()
    +leftmostBlue()
    +rightmostBlue()
}

class TileGrid {
    -double tileSize_
    -unordered_map~pair<int,int>,Tile,PairHash~ tiles_

    +TileGrid(tileSize)
    +insertPoint(p)
    +getTile(i,j)
    +getTileForPoint(p)
    +tileCount()
    +begin()
    +end()
}

class Neighborhood {
    <<struct>>
    +bool hasRed
    +bool hasBlue
    +isMonochromatic()
    +isBichromatic()
}

class Graph {
    -vector~pair<ColoredPoint,ColoredPoint>~ edges_
    -set~pair<int,int>~ edgeIds_

    +addEdge(a,b)
    +getEdges()
    +edgeCount()
}

class PairHash {
    <<functor>>
    +operator()(pair<int,int>)
}

class paperMath {
    <<utility>>
    +calcDelta()
    +calcPhi()
    +calcK()
}

class InputHelper {
    <<utility>>
    +getEpsilon()
    +checkDouble()
    +checkInt()
    +redChecker()
}

class SpannerBuilder

Tile *-- ColoredPoint : stores
TileGrid *-- Tile : owns
TileGrid ..> PairHash : uses hash
Graph --> ColoredPoint : edge endpoints
Neighborhood ..> TileGrid : neighborhood queries
Neighborhood ..> ColoredPoint : returns pointers
SpannerBuilder ..> TileGrid
SpannerBuilder ..> Graph
```
Work in Progress:
  - creating logic for the four cases described in the article
  - create a user interface that shows the user all of the edges taken using the algorithm
  - create a way for the user to give large sets of points

Dependencies:
- C++20
- CGAL (for points)
- CMAKE

Acknowledgements:
This project was developed as part of a Summer 2026 Research Experiences for Undergraduates (REU) program at California State University, Northridge. The REU program is supported by the National Science Foundation (NSF).

I would like to thank Csaba D. Tóth and Theodore Fung, for their guidance throughout this project.
  
