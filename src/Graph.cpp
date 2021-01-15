#include "Graph.hpp"


Graph::Graph(const std::string &deviceName,
             mn::CppLinuxSerial::BaudRate baudRate,
             sf::RenderWindow *window,
             int32_t bufferSize) : window(window), port(deviceName, baudRate), buffer(bufferSize) {
    port.SetTimeout(-1); // Block when reading until any data is received
    port.Open();
}

Graph::~Graph() {
    port.Close();
    if (window->isOpen()) {
        window->close();
    }
}

void Graph::readData() {
    // Read data from the arduino port
    std::string readData;
    port.Read(readData);

    // Pre processing
    auto tokens = strSplit(readData);
    auto numbers = strToNum<fpt>(tokens);
    buffer.push_back(numbers);

    for(SignalFilter * filter : filters) {
        filter(buffer);
    }
}

void Graph::update() {
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            default:
                break;
        }
    }
    this->readData();

    // Drawing white background
    window->clear(sf::Color::White);

    fpt deltaX = WINDOW_WIDTH / buffer.data().size();
    for(int32_t i = 1; i < buffer.data().size(); i++) {
        sf::VertexArray line(sf::LinesStrip, 2);
        line[0].position = sf::Vector2f((i - 1) * deltaX, WINDOW_HEIGHT - buffer[i - 1]);
        line[0].color  = sf::Color::Black;
        line[1].position = sf::Vector2f(i * deltaX, WINDOW_HEIGHT - buffer[i]);
        line[1].color = sf::Color::Black;
        window->draw(line);
    }

    // Refresh mainPanel
    window->display();
}
