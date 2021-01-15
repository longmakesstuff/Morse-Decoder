#include <SFML/Graphics.hpp>
#include <Common.hpp>

int main() {
    sf::RenderWindow window({(int32_t) WINDOW_WIDTH, (int32_t) WINDOW_HEIGHT}, "Snake AI");
    window.setFramerateLimit(10);

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }
        // Drawing white background
        window.clear(sf::Color::White);

        // Refresh mainPanel
        window.display();
    }
}