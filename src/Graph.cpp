#include "Graph.hpp"


Graph::Graph(const std::string &deviceName,
             mn::CppLinuxSerial::BaudRate baudRate,
             sf::RenderWindow *window,
             sf::Font * font,
             int32_t bufferSize) : window(window), font(font), port(deviceName, baudRate), buffer(bufferSize) {
    LOG_INFO("Opening serial port")
    // Initializing port
    port.SetTimeout(-1); // Block when reading until any data is received
    port.Open();
    LOG_INFO("GUI initialized successfully")
    deltaX =  WINDOW_WIDTH / buffer.getCap();
}

Graph::~Graph() {
    LOG_INFO("Closing graph")
    port.Close();
    if (window->isOpen()) {
        window->close();
    }
}

void Graph::readData() {
    // Read data from the arduino port
    std::string readData;
    port.Read(readData);

    // Pre processing, split by \n
    auto tokens = strSplit(readData);

    // Remove beginning f and ending e
    tokens = encodeAndFilter(tokens);

    // Converting token to number

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
    LOG_DEBUG("Begin to read new data")
    this->readData();
    LOG_DEBUG("Finished reading new data")

    // Drawing white background
    window->clear(sf::Color::White);

    for(size_t i = 1; i < buffer.size(); i++) {
        sf::VertexArray line(sf::LinesStrip, 2);

        // Data multiplied with 10 at source
        // Divide with 10 again
        line[0].position = sf::Vector2f((i - 1) * deltaX, WINDOW_HEIGHT - buffer[i - 1]);
        line[0].color  = sf::Color::Black;
        line[1].position = sf::Vector2f(i * deltaX, WINDOW_HEIGHT - buffer[i]);
        line[1].color = sf::Color::Black;
        window->draw(line);
    }

    sf::VertexArray meanLine(sf::LinesStrip, 2);

    // Data multiplied with 10 at source
    // Divide with 10 again
    meanLine[0].position = sf::Vector2f(0, WINDOW_HEIGHT - buffer.mean());
    meanLine[0].color  = sf::Color::Red;
    meanLine[1].position = sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT - buffer.mean());
    meanLine[1].color = sf::Color::Red;
    window->draw(meanLine);

    drawFPS();

    // Refresh mainPanel
    window->display();
}

void Graph::drawFPS() {
    std::stringstream ss;
    fps.update();
    ss << "FPS: " << fps.getFPS();
    std::cout << ss.str() << std::endl;
    sf::Text fpsText{ss.str(), *font, 15};
    fpsText.setPosition( 50, 10);
    fpsText.setFillColor(sf::Color::Black);
    window->draw(fpsText);
}
