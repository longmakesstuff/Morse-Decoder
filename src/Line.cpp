#include "Line.hpp"

void Line::initialize() {
    sf::Vector2f direction = point2 - point1;
    sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

    sf::Vector2f offset = (thickness / 2.f) * unitPerpendicular;

    vertices[0].position = point1 + offset;
    vertices[1].position = point2 + offset;
    vertices[2].position = point2 - offset;
    vertices[3].position = point1 - offset;

    for (auto &vertex : vertices)
        vertex.color = color;
}

Line::Line(const sf::Vector2f &point1, const sf::Vector2f &point2, fpt thickness, sf::Color color) : point1(point1),
                                                                                                     point2(point2),
                                                                                                     thickness(thickness),
                                                                                                     color(color) {
    initialize();
}

void Line::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(vertices, 4, sf::Quads);
}

void Line::setThickness(float _thickness) {
    Line::thickness = _thickness;
    initialize();
}

void Line::setColor(const sf::Color &_color) {
    Line::color = _color;
    initialize();
}
