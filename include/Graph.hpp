#pragma once

#include <cinttypes>
#include <SFML/Graphics.hpp>
#include "String.hpp"
#include "SerialPort.hpp"
#include "Common.hpp"
#include "SizedVector.hpp"
#include "Noise.hpp"

class Graph {
private:
    sf::RenderWindow *window;
    sf::Event event;
    mn::CppLinuxSerial::SerialPort port;
    SizedVector<fpt> buffer;
    void readData();
    std::vector<SignalFilter *> filters;

public:
    explicit Graph(const std::string &deviceName,
                   mn::CppLinuxSerial::BaudRate baudRate,
                   sf::RenderWindow *window,
                   int32_t bufferSize);

    ~Graph();

    void update();
};