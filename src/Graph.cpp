#include "Graph.hpp"


Graph::Graph(const std::string &deviceName,
             mn::CppLinuxSerial::BaudRate baudRate,
             sf::RenderWindow *window,
             sf::Font *font,
             int32_t bufferSize,
             SpeedLevel speedLevel) : window(window), font(font), port(deviceName, baudRate), buffer(bufferSize),
                                   speedController(speedLevel), stateMachine(&speedController) {
    LOG_INFO("Using speed controller: " << speedController);
    LOG_INFO("Opening serial port")
    // Initializing port
    port.SetTimeout(-1); // Block when reading until any data is received
    port.Open();
    LOG_INFO("GUI initialized successfully")
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
}

void Graph::drawPoints() {
   fpt mean = buffer.mean();
   fpt delta = WINDOW_HEIGHT / 2 - mean;
   fpt deltaX = WINDOW_WIDTH / buffer.getCap();

    for (size_t i = 1; i < buffer.size(); i++) {
        Line line(sf::Vector2f((i - 1) * deltaX, WINDOW_HEIGHT - buffer[i - 1] - delta),
                  sf::Vector2f(i * deltaX, WINDOW_HEIGHT - buffer[i] - delta), 4, sf::Color{50, 50, 50});

        window->draw(line);
    }

    Line meanLine(sf::Vector2f(0, WINDOW_HEIGHT / 2), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT / 2), 4, sf::Color{50, 50, 50});
    window->draw(meanLine);
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

    // Notify state machine
    if (buffer.size() > 0) {
        fpt mean = this->buffer.mean();
        fpt std = this->buffer.std();
        fpt last = this->buffer.data().back();
        auto machineOutput = stateMachine.enter(last, mean, std);
        if (machineOutput.has_value()) {
            morse.add(machineOutput.value());
            if (machineOutput.value().find(" ") != std::string::npos) {
                auto morseDecoded = morse.parse();
                if (morseDecoded.has_value()) {
                    auto value = morseDecoded.value();
                    for(char i : value) {
                        messages.push_back(std::string(1, i));
                    }
                }
            }
        }
    }
    // Drawing white background
    window->clear(sf::Color::White);

    this->drawPoints();
    this->drawFPS();
    this->drawMessages();
    this->drawInfo();

    // Refresh mainPanel
    window->display();
}

void Graph::drawFPS() {
    std::stringstream ss;
    fps.update();
    ss << fps.getFPS() << " FPS";
    sf::Text fpsText{ss.str(), *font, 15};
    fpsText.setPosition(WINDOW_WIDTH - 75, 10);
    fpsText.setFillColor(sf::Color::Black);
    window->draw(fpsText);
}

void Graph::drawMessages() {
    std::stringstream ss;
    ss << "[Parsed messages] - \"";
    for(const auto& message: messages.data()) {
        ss << message;
    }
    ss << "_\"";
    sf::Text messageTests{ss.str(), *font, 35};

    messageTests.setPosition(WINDOW_WIDTH / 2 - messageTests.getLocalBounds().width / 2 , WINDOW_HEIGHT - 250);
    messageTests.setFillColor(sf::Color::Black);

    window->draw(messageTests);
}


void Graph::drawInfo() {
    std::stringstream meanInfo;
    meanInfo << "[Mean] - " << buffer.mean();
    sf::Text meanText{meanInfo.str(), *font, 15};
    meanText.setPosition(10, 5);
    meanText.setFillColor(sf::Color::Black);


    std::stringstream entropyInfo;
    entropyInfo << "[Entropy] - " << buffer.entropy();
    sf::Text entropyText {entropyInfo.str(), *font, 15};
    entropyText.setPosition(10, 25);
    entropyText.setFillColor(sf::Color::Black);

    window->draw(meanText);
    window->draw(entropyText);
}
