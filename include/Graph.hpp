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

class Graph {
private:
    sf::RenderWindow *window;
    sf::Event event{};
    sf::Font *font;
    mn::CppLinuxSerial::SerialPort port;
    SizedVector<fpt> buffer;
    FPS fps;
    void readData();
    fpt deltaX;
    Morse morse;
    StateMachine stateMachine;
    void drawFPS();

public:
    explicit Graph(const std::string &deviceName,
                   mn::CppLinuxSerial::BaudRate baudRate,
                   sf::RenderWindow *window,
                   sf::Font *font,
                   int32_t bufferSize);

    ~Graph();

    void update();
};