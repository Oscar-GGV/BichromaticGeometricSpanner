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
    //new addition SFML

    double minX = points[0].point.x(), maxX = points[0].point.x(); //smallest x and biggest x in points
    double minY = points[0].point.y(), maxY = points[0].point.y(); //smallest y and biggest y in points
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

    int iMin = static_cast<int>(std::floor(minX / 1.0)) - 1;
    int iMax = static_cast<int>(std::floor(maxX / 1.0)) + 1;
    int jMin = static_cast<int>(std::floor(minY / delta)) - 1;
    int jMax = static_cast<int>(std::floor(maxY / delta)) + 1;

    std::vector<sf::Vertex> gridLines;
    sf::Color gridColor(220, 220, 220);

    for (int i = iMin; i <= iMax; i++)
    {
        double x = i * 1.0;
        gridLines.push_back(sf::Vertex(toScreen(x, minY), gridColor));
        gridLines.push_back(sf::Vertex(toScreen(x, maxY), gridColor));
    }
    for (int j = jMin; j <= jMax; j++)
    {
        double y = j * delta;
        gridLines.push_back(sf::Vertex(toScreen(minX, y), gridColor));
        gridLines.push_back(sf::Vertex(toScreen(maxX, y), gridColor));
    }

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Bichromatic Spanner");

    //  camera: view controls what portion of the scene is visible
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

            // scroll wheel / trackpad  zoom
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                float scrollAmount = event.mouseWheelScroll.delta; // can be large/fractional on trackpads
                float zoomFactor = std::pow(1.02f, -scrollAmount);  // scales with actual gesture size
                view.zoom(zoomFactor);
                window.setView(view);
            }

            // left mouse button start/stop drag-to-pan
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

        // while dragging, move the view opposite to mouse movement
        if (dragging)
        {
            sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
            sf::Vector2f delta = window.mapPixelToCoords(lastMousePos) - window.mapPixelToCoords(currentMousePos);
            view.move(delta);
            window.setView(view);
            lastMousePos = currentMousePos;
        }

        window.clear(sf::Color::White);

        for (size_t k = 0; k + 1 < gridLines.size(); k += 2)
        {
            sf::Vertex line[] = { gridLines[k], gridLines[k + 1] };
            window.draw(line, 2, sf::Lines);
        }

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