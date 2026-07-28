//
// Created by Oscar Guevara Viveros on 7/27/26.
//

#include <iostream>
//for input and output
#include <vector>
//used for saving all the points
#include "ColoredPoint.h"
//used for the ColoredPoint struct consisting of 2_d point and a color and a number

#include "InputHelper.h"

#include "paperMath.h"

#include "Neighborhood.h"
int main()
{
    /*
    TileGrid grid(1, 1); //easy grid
    // Tile (0,0): all red
    ColoredPoint r1; r1.number = 0; r1.isRed = true;  r1.point = Kernel::Point_2(0.2, 0.2);
    grid.insertPoint(r1);

    // Tile (1,0): all blue
    ColoredPoint b1; b1.number = 1; b1.isRed = false; b1.point = Kernel::Point_2(1.2, 0.2);
    grid.insertPoint(b1);

    // Tile (0,1): mixed, makes N(0,0) bichromatic once folded in
    ColoredPoint b2; b2.number = 2; b2.isRed = false; b2.point = Kernel::Point_2(0.2, 1.2);
    grid.insertPoint(b2);

    Neighborhood n00 = buildNeighborhood(grid, 0, 0); //neighborhood at tile (0, 0)
    std::cout << "N(0,0) hasRed: " << n00.hasRed << " (expect 1)\n";
    std::cout << "N(0,0) hasBlue: " << n00.hasBlue << " (expect 1, because tile (0,1) is in its 3x3 block)\n";
    std::cout << "N(0,0) isBichromatic: " << n00.isBichromatic() << " (expect 1)\n"; //yes because there are both blue and red points

    Neighborhood n_empty = buildNeighborhood(grid, 5, 5); // nothing near here
    std::cout << "N(5,5) hasRed: " << n_empty.hasRed << " (expect 0)\n"; //no points
    std::cout << "N(5,5) isMonochromatic: " << n_empty.isMonochromatic() << " (expect 0 — mono requires exactly one color present, not zero)\n";

    */

     //Test for 3x3 specifically
     TileGrid grid(1,1);
    int id = 0;
    //for loop that fills all 0 tiles in the 3x3 neighborhood centered on (0,0)
    //i for (-1, 1) j (-1, 1)
    for (int i = -1; i<=1; i++)
    {
        for (int j = -1; j <=1; j++)
        {
            ColoredPoint p;
            p.number = id++;
            p.isRed = true;//all points are gonna be red to see if monochromatic checker works
            p.point = Kernel::Point_2(i+0.5, j + 0.5);
            grid.insertPoint(p);
        }
    }
    Neighborhood n00 = buildNeighborhood(grid, 0, 0); //neighborhood centered at (0,0)
    std::cout << "All 9 tiles red -> hasRed: " << n00.hasRed << " (expect 1)\n"; //all 9 points are red
    std::cout << "All 9 tiles red -> hasBlue: " << n00.hasBlue << " (expect 0)\n"; //there is no blue point so far. should be 0
    std::cout << "All 9 tiles red -> isMonochromatic: " << n00.isMonochromatic() << " (expect 1)\n";
    std::cout << "-------------\n";
    //now a new point is added that is blue
    ColoredPoint b;
    b.number = id++;
    b.isRed = false;
    b.point = Kernel::Point_2(1.5, 1.5); // lands in tile (1,1)
    grid.insertPoint(b);

    Neighborhood n00_after = buildNeighborhood(grid, 0, 0);
    std::cout << "After adding blue in corner (1,1) -> hasBlue: " << n00_after.hasBlue << " (expect 1)\n";
    std::cout << "isBichromatic: " << n00_after.isBichromatic() << " (expect 1)\n";
    std::cout << "----------------\n";

    //new test to see if new function work in identifying rr, lr, rb, lb
    const ColoredPoint* rr = rightmostRedInNeighborhood(grid, 0, 0);
    const ColoredPoint* lr = leftmostRedInNeighborhood(grid, 0, 0);
    const ColoredPoint* rb = rightmostBlueInNeighborhood(grid, 0, 0);
    const ColoredPoint* lb = leftmostBlueInNeighborhood(grid, 0, 0);

    std::cout << "rightmostRed x: " << (rr ? rr->point.x() : -999) << " (expect 1.5, from tile i=1)\n";
    std::cout << "leftmostRed x: "  << (lr ? lr->point.x() : -999) << " (expect -0.5, from tile i=-1)\n";
    std::cout << "rightmostBlue number: " << (rb ? rb->number : -1) << " (expect the id of point b, only blue point)\n";
    std::cout << "leftmostBlue number: "  << (lb ? lb->number : -1) << " (expect same id, only blue point)\n";
    std::cout << "-------------\n";

    //this point is in tile (2,0) it should not be a part of (0,0)
    //to use this specific part of the test comment out the added point above
    ColoredPoint farBlue;
    farBlue.number = id++;
    farBlue.isRed = false;
    farBlue.point = Kernel::Point_2(2.5, 0.5); // tile (2,0)
    grid.insertPoint(farBlue);

    Neighborhood n00_far = buildNeighborhood(grid, 0, 0);
    // this should be unchanged from n00_after, since (2,0) is out of range
    std::cout << "Still isBichromatic after far blue: " << n00_far.isBichromatic() << " (expect 0 if commented out the last blue point at (1,1), otherwise expect 1\n";

    const ColoredPoint* rb_after_far = rightmostBlueInNeighborhood(grid, 0, 0);
    std::cout << "rightmostBlue number after far blue added: " << (rb_after_far ? rb_after_far->number : -1)
               << " (expect same id as before — corner blue, NOT farBlue's id)\n";

}