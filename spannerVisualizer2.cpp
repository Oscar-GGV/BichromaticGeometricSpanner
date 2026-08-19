//
// Created by Oscar Guevara Viveros on 8/10/26.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "InputHelper.h"
#include "paperMath.h"
#include "Graph.h"
#include "FullSpannerBuilder.h"

int main()
{
    double epsilon = InputHelper::getEpsilon();
    int mu = 9;

    std::cout << "file name? ";
    std::string filename;
    std::cin >> filename;

    std::vector<ColoredPoint> points = InputHelper::readPointsFromFile(filename);
    if (points.empty())
    {
        std::cout << "No points\n";
        return 1;
    }

    FullSpannerBuilder builder(epsilon, mu, points);
    Graph G = builder.buildFullSpanner();
    std::cout << "Final edge count: " << G.edgeCount() << "\n";


    for (const auto& [a, b] : G.getEdges())
    {
        std::cout << a.number << " " << b.number << "\n";
    }

    std::cout << "Points loaded: " << points.size() << "\n";

    //  everything below here is identical to SpannerVisualizer.cpp

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
    const float padding = 40.0f;

    double dataWidth = (maxX - minX);
    double dataHeight = (maxY - minY);
    if (dataWidth == 0) dataWidth = 1;
    if (dataHeight == 0) dataHeight = 1;

    auto toScreen = [&](double x, double y) -> sf::Vector2f {
        float sx = padding + static_cast<float>((x - minX) / dataWidth) * (windowWidth - 2 * padding);
        float sy = padding + static_cast<float>((maxY - y) / dataHeight) * (windowHeight - 2 * padding);
        return sf::Vector2f(sx, sy);
    };

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Bichromatic Spanner - Full (theta, lambda)");

    sf::View view(sf::FloatRect(0, 0, windowWidth, windowHeight));
    window.setView(view);

    bool dragging = false;
    sf::Vector2i lastMousePos;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseWheelScrolled)
            {
                float zoomFactor = std::pow(1.02f, -event.mouseWheelScroll.delta);
                view.zoom(zoomFactor);
                window.setView(view);
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                dragging = true;
                lastMousePos = sf::Mouse::getPosition(window);
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                dragging = false;
            }
        }

        if (dragging)
        {
            sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
            sf::Vector2f delta = window.mapPixelToCoords(lastMousePos) - window.mapPixelToCoords(currentMousePos);
            view.move(delta);
            window.setView(view);
            lastMousePos = currentMousePos;
        }

        window.clear(sf::Color::White);

        for (const auto& [a, b] : G.getEdges())
        {
            sf::Vertex line[] = {
                sf::Vertex(toScreen(a.point.x(), a.point.y()), sf::Color(150, 150, 150)),
                sf::Vertex(toScreen(b.point.x(), b.point.y()), sf::Color(150, 150, 150))
            };
            window.draw(line, 2, sf::Lines);
        }

        const float radius = 4.0f;
        for (const auto& p : points)
        {
            sf::CircleShape circle(radius);
            circle.setFillColor(p.isRed ? sf::Color::Red : sf::Color::Blue);
            sf::Vector2f pos = toScreen(p.point.x(), p.point.y());
            circle.setPosition(pos.x - radius, pos.y - radius);
            window.draw(circle);
        }

        window.display();
    }

    return 0;
}
