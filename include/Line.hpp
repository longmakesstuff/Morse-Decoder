#pragma once

#include <SFML/Graphics.hpp>
#include "Common.hpp"

class Line : public sf::Drawable {
private:
    sf::Vertex vertices[4];
    sf::Vector2f point1;
    sf::Vector2f point2;
    fpt thickness;
    sf::Color color;

    void initialize();

public:
    Line(const sf::Vector2f &point1, const sf::Vector2f &point2, fpt thickness=2.0, sf::Color color=sf::Color::Black);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void setThickness(float _thickness);

    void setColor(const sf::Color &_color);
};