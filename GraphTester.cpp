//
// Created by Oscar Guevara Viveros on 7/27/26.
//

#include "Graph.h"

int main()
{
    Graph G;
    ColoredPoint a; a.number = 0; a.isRed = true; a.point = Kernel::Point_2(1,1);
    ColoredPoint b; b.number = 1; b.isRed = false; b.point = Kernel::Point_2(5,5);
    ColoredPoint c; c.number = 2; c.isRed = true; c.point = Kernel::Point_2(2,2);
    ColoredPoint d; d.number = 3; d.isRed = false; d.point = Kernel::Point_2(3,3);

    //insertion test
    bool r1 = G.addEdge(a,b);
    std::cout << "Added a-b: " << r1 << "(expect 1)\n";
    //edge count test
    std::cout << "Edge count: " << G.edgeCount() << " (expect 1)\n";

    //test for duplicate

    bool r2 = G.addEdge(a,b);
    std::cout <<"Added a-b again: " << r2 << " (expect 0)\n";
    std::cout << "Edge count: " << G.edgeCount() << " (expect 1 still)\n";


    //test for reverse duplicate b, a
    bool r3 = G.addEdge(b,a);
    std::cout << "Added b-a: " << r3 << " (expect 0)\n";
    std::cout << "Edge count: " << G.edgeCount() << " (expect 1 still )\n";

    //test for rejection of same color points
    bool r4 = G.addEdge(a,c);
    std::cout << "Added a-c: " << r4 << " (expect 0)\n";
    std::cout << "Edge count: " << G.edgeCount() << " (expect 1 still )\n";

    //test for new regular edge
    bool r5 = G.addEdge(a,d);
    std::cout << "Added a-d: " << r5 << " (expect 1)\n";
    std::cout << "Edge count: " << G.edgeCount() << " (expect 2 )\n";

}