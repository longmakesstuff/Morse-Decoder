#include <SFML/Graphics.hpp>
#include <Common.hpp>
#include <Graph.hpp>
#include <Speed.hpp>

int main() {
    LOG_INFO("Initializing GUI")
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Morse decoder", sf::Style::Close, settings);
    window.setSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));
    window.setFramerateLimit(60);

    // Load font
    sf::Font font;
    font.loadFromFile("DejaVuSans.ttf");

    Graph graph("/dev/ttyACM0", mn::CppLinuxSerial::BaudRate::B_38400, &window, &font, 1000, SpeedLevel::FAST);

    // Main loop
    while (window.isOpen()) {
        graph.update();
    }
}