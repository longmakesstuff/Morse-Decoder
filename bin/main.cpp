#include <SFML/Graphics.hpp>
#include <Common.hpp>
#include <Graph.hpp>

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    settings.depthBits = 32;
    sf::RenderWindow window({WINDOW_WIDTH, WINDOW_HEIGHT}, "Live Data Plotter", sf::Style::Default, settings);
    window.setFramerateLimit(45);

    Graph graph("/dev/ttyACM0", mn::CppLinuxSerial::BaudRate::B_19200, &window, 500);

    // Main loop
    while (window.isOpen()) {
        graph.update();
    }
}