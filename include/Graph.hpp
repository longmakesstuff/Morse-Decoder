#pragma once

#include <cinttypes>
#include <SFML/Graphics.hpp>
#include "FPS.hpp"
#include "String.hpp"
#include "SerialPort.hpp"
#include "Common.hpp"
#include "SizedVector.hpp"
#include "Morse.hpp"
#include "StateMachine.hpp"
#include "Speed.hpp"
#include "Line.hpp"

class Graph {
private:
    sf::RenderWindow *window;
    sf::Event event{};
    sf::Font *font;
    mn::CppLinuxSerial::SerialPort port;
    SizedVector<fpt> buffer;
    FPS fps;
    Morse morse;
    SpeedController speedController;
    StateMachine stateMachine;
    SizedVector<std::string> messages{100};

    void readData();
    void drawFPS();
    void drawPoints();
    void drawMessages();
    void drawInfo();

public:
    explicit Graph(const std::string &deviceName,
                   mn::CppLinuxSerial::BaudRate baudRate,
                   sf::RenderWindow *window,
                   sf::Font *font,
                   int32_t bufferSize,
                   SpeedLevel speedLevel);

    ~Graph();

    void update();
};