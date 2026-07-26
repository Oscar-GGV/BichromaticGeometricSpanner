#include <iostream>
//for input and output
#include <vector>
//used for saving all the points
#include "Coloredpoint.h"
//used for the ColoredPoint struct consisting of 2_d point and a color and a number

#include "InputHelper.h"

#include "paperMath.h"

#include "TileGrid.h"

int main()
{
    std::cout << std::boolalpha;
    double epsilon = InputHelper::getEpsilon(); // 3 + epsilon spanner
    double delta = paperMath::calcDelta(epsilon);
    std::vector<ColoredPoint> points;
    ColoredPoint one;
    //all points are relatively close to eachother to test tile size
    one.point = Kernel::Point_2(1.0,2.0);
    one.isRed = true;
    points.push_back(one);
    ColoredPoint two;
    two.point = Kernel::Point_2(1.1,2.1);
    two.isRed = true;
    points.push_back(two);
    //point one and two should be in the same tile.
    ColoredPoint three;
    three.point = Kernel::Point_2(1.2,2.2);
    three.isRed = true;
    points.push_back(three);
    ColoredPoint four;
    four.point = Kernel::Point_2(1.3,2.3);
    four.isRed = true;
    points.push_back(four);
    ColoredPoint five;
    five.point = Kernel::Point_2(1.4, 2.4);
    five.isRed = false;
    points.push_back(five);

    TileGrid grid(1.0, delta);

    for (const auto& p : points)
    {
        grid.insertPoint(p);
    }
    std::cout << "Tiles created: " << grid.tileCount() << std::endl;
   Tile* t = grid.getTileForPoint(one);
    if (t)
    {
        std::cout <<"[I, J]= " << t->getI() << "," << t->getJ() << " " <<  "colorFlag= " << t->colorFlag() << " monochromatic= " << t->isMonochromatic() << " bichromatic= " <<t->isBichromatic() << "\n";
    }

    Tile* b = grid.getTileForPoint(two);
    if (b)
    {
        std::cout <<"[I, J]= " << b->getI() << "," << b->getJ() << " " << "colorFlag= " << b->colorFlag() << " monochromatic= " << b->isMonochromatic() << " bichromatic= " <<b->isBichromatic() << "\n";
    }

    Tile* c = grid.getTileForPoint(three);
    if (c)
    {
        std::cout <<"[I, J]= " << c->getI() << "," << c->getJ() << " " << "colorFlag= " << c->colorFlag() << " monochromatic= " << c->isMonochromatic() << " bichromatic= " <<c->isBichromatic() << "\n";
    }

    Tile* d = grid.getTileForPoint(four);
    if (d)
    {
        std::cout <<"[I, J]= " << d->getI() << "," << d->getJ() << " " << "colorFlag= " << d->colorFlag() << " monochromatic= " << d->isMonochromatic() << " bichromatic= " <<d->isBichromatic() << "\n";

    }
    Tile* f = grid.getTileForPoint(five);
    if (f)
    {
        std::cout <<"[I, J]= " << f->getI() << "," << f->getJ() << " " << "colorFlag= " << f->colorFlag() << " monochromatic= " << f->isMonochromatic() << " bichromatic= " <<f->isBichromatic() << "\n";

    }




}
