cmake_minimum_required(VERSION 4.2)
project(BichromaticGeometricSpanner)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CGAL REQUIRED)
find_package(Eigen3 REQUIRED)

include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)


add_executable(BichromaticGeometricSpanner
        main.cpp
        SpannerBuilder.cpp
        SpannerBuilder.h
        Neighborhood.cpp
        Neighborhood.h
        Graph.cpp
        Graph.h
        ColoredPoint.cpp
        ColoredPoint.h
        InputHelper.cpp
        InputHelper.h
        paperMath.cpp
        paperMath.h
        Tile.cpp
        Tile.h
        TileGrid.cpp
        TileGrid.h
        PairHash.cpp
        PairHash.h
)
add_executable(tileTester
TileTester.cpp
        ColoredPoint.cpp
        ColoredPoint.h
        InputHelper.cpp
        InputHelper.h
        paperMath.cpp
        paperMath.h
        Tile.cpp
        Tile.h
        TileGrid.cpp
        TileGrid.h
        PairHash.cpp
        PairHash.h
        )

add_executable(GraphTester
GraphTester.cpp
        Graph.cpp
        Graph.h
        ColoredPoint.cpp
        ColoredPoint.h
        InputHelper.cpp
        InputHelper.h
        paperMath.cpp
        paperMath.h
        Tile.cpp
        Tile.h
        TileGrid.cpp
        TileGrid.h
        PairHash.cpp
        PairHash.h
)

add_executable(NeighborhoodTester
NeighborhoodTester.cpp
Neighborhood.cpp
Neighborhood.h
        Graph.cpp
        Graph.h
        ColoredPoint.cpp
        ColoredPoint.h
        InputHelper.cpp
        InputHelper.h
        paperMath.cpp
        paperMath.h
        Tile.cpp
        Tile.h
        TileGrid.cpp
        TileGrid.h
        PairHash.cpp
        PairHash.h)

add_executable(SpannerBuilderTester
        SpannerBuilderTester.cpp
        SpannerBuilder.cpp
        SpannerBuilder.h
        Neighborhood.cpp
        Neighborhood.h
        Graph.cpp
        Graph.h
        ColoredPoint.cpp
        ColoredPoint.h
        InputHelper.cpp
        InputHelper.h
        paperMath.cpp
        paperMath.h
        Tile.cpp
        Tile.h
        TileGrid.cpp
        TileGrid.h
        PairHash.cpp
        PairHash.h
)

add_executable(SpannerVisualizer
        SpannerVisualizer.cpp
        SpannerBuilder.cpp
        SpannerBuilder.h
        Neighborhood.cpp
        Neighborhood.h
        Graph.cpp
        Graph.h
        ColoredPoint.cpp
        ColoredPoint.h
        InputHelper.cpp
        InputHelper.h
        paperMath.cpp
        paperMath.h
        Tile.cpp
        Tile.h
        TileGrid.cpp
        TileGrid.h
        PairHash.cpp
        PairHash.h
)

target_link_libraries(SpannerVisualizer
        PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        CGAL::CGAL
        Eigen3::Eigen
)

target_link_libraries(SpannerBuilderTester
        PRIVATE
        CGAL::CGAL
        Eigen3::Eigen
)


target_link_libraries(tileTester
        PRIVATE
        CGAL::CGAL
        Eigen3::Eigen
)

target_link_libraries(BichromaticGeometricSpanner
        PRIVATE
        CGAL::CGAL
        Eigen3::Eigen
)

target_link_libraries(GraphTester
        PRIVATE
        CGAL::CGAL
        Eigen3::Eigen
)
target_link_libraries(NeighborhoodTester
        PRIVATE
        CGAL::CGAL
        Eigen3::Eigen
)