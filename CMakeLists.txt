cmake_minimum_required(VERSION 4.2)
project(BichromaticGeometricSpanner)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CGAL REQUIRED)
find_package(Eigen3 REQUIRED)

add_executable(BichromaticGeometricSpanner
        main.cpp
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

target_link_libraries(BichromaticGeometricSpanner
        PRIVATE
        CGAL::CGAL
        Eigen3::Eigen
)