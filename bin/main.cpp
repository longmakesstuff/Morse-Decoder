#include <SFML/Graphics.hpp>
#include <Common.hpp>
#include <Graph.hpp>

int main() {
    LOG_INFO("Initializing GUI")
    sf::RenderWindow window({WINDOW_WIDTH, WINDOW_HEIGHT}, "Live Data Plotter", sf::Style::Default);
    window.setFramerateLimit(60);

    // Load font
    sf::Font font;
    font.loadFromFile("DejaVuSans.ttf");

    Graph graph("/dev/ttyACM0", mn::CppLinuxSerial::BaudRate::B_19200, &window, &font, 500);


    // Main loop
    while (window.isOpen()) {
        graph.update();
    }
}