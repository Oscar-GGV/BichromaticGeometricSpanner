#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "InputHelper.h"
#include "paperMath.h"
#include "TileGrid.h"
#include "Graph.h"
#include "SpannerBuilder.h"

int main()
{
    double epsilon = InputHelper::getEpsilon();
    double delta = paperMath::calcDelta(epsilon);

    std::cout << "file name? ";
    std::string filename;
    std::cin >> filename;

    std::vector<ColoredPoint> points = InputHelper::readPointsFromFile(filename);
    if (points.empty())
    {
        std::cout << "No points\n";
        return 1;
    }

    TileGrid grid(1.0, delta);
    for (const auto& p : points)
        grid.insertPoint(p);

    Graph G = buildSpanner(grid);
    std::cout << "Edge count: " << G.edgeCount() << "\n";

    // ---- find data bounding box, for mapping into pixel space ----
    double minX = points[0].point.x(), maxX = points[0].point.x();
    double minY = points[0].point.y(), maxY = points[0].point.y();
    for (const auto& p : points)
    {
        minX = std::min(minX, p.point.x());
        maxX = std::max(maxX, p.point.x());
        minY = std::min(minY, p.point.y());
        maxY = std::max(maxY, p.point.y());
    }

    const unsigned int windowWidth = 1000;
    const unsigned int windowHeight = 700;
    const float padding = 40.0f; // pixels of margin so points don't touch the edge

    double dataWidth = (maxX - minX);
    double dataHeight = (maxY - minY);
    if (dataWidth == 0) dataWidth = 1;   // avoid divide-by-zero if all points share an x
    if (dataHeight == 0) dataHeight = 1;

    // scale so the whole bounding box fits, preserving aspect ratio isn't required here
    // since x/y ranges are usually wildly different (delta is tiny) -- stretch independently
    auto toScreen = [&](double x, double y) -> sf::Vector2f {
        float sx = padding + static_cast<float>((x - minX) / dataWidth) * (windowWidth - 2 * padding);
        float sy = padding + static_cast<float>((maxY - y) / dataHeight) * (windowHeight - 2 * padding); // flip y
        return sf::Vector2f(sx, sy);
    };

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Bichromatic Spanner");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // draw edges first, so points render on top
        for (const auto& [a, b] : G.getEdges())
        {
            sf::Vertex line[] = {
                sf::Vertex(toScreen(a.point.x(), a.point.y()), sf::Color(150, 150, 150)),
                sf::Vertex(toScreen(b.point.x(), b.point.y()), sf::Color(150, 150, 150))
            };
            window.draw(line, 2, sf::Lines);
        }

        // draw points
        const float radius = 4.0f;
        for (const auto& p : points)
        {
            sf::CircleShape circle(radius);
            circle.setFillColor(p.isRed ? sf::Color::Red : sf::Color::Blue);
            sf::Vector2f pos = toScreen(p.point.x(), p.point.y());
            circle.setPosition(pos.x - radius, pos.y - radius); // center the circle on the point
            window.draw(circle);
        }

        window.display();
    }

    return 0;
}