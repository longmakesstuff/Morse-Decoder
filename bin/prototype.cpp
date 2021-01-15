#include <iostream>
#include <thread>
#include <chrono>
#include <SerialPort.hpp>
#include <String.hpp>
#include <SizedVector.hpp>
#include "Common.hpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main() {
    mn::CppLinuxSerial::SerialPort serialPort("/dev/ttyACM0",  mn::CppLinuxSerial::BaudRate::B_9600);

    serialPort.SetTimeout(-1); // Block when reading until any data is received

    serialPort.Open();

    std::vector<fpt> buffer;

    try {
        while (true) {
            // Read some data back (will block until at least 1 byte is received due to the SetTimeout(-1) call above)
            std::string readData;
            serialPort.Read(readData);
            auto tokens = strSplit(readData);
            buffer = strToNum<fpt>(tokens);
            for(auto token : buffer) {
                std::cout << token << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    } catch (std::exception &exception) {
        // Close the serial port
        serialPort.Close();
    }
}

#pragma clang diagnostic pop