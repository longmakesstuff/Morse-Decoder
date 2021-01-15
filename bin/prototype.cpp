#include <iostream>
#include <thread>
#include <chrono>
#include <SerialPort.hpp>

using namespace mn::CppLinuxSerial;


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main() {
    SerialPort serialPort("/dev/ttyACM0", BaudRate::B_9600);
    // Use SerialPort serialPort("/dev/ttyACM0", 13000); instead if you want to provide a custom baud rate
    serialPort.SetTimeout(-1); // Block when reading until any data is received
    serialPort.Open();

    try {
        while (true) {
            // Read some data back (will block until at least 1 byte is received due to the SetTimeout(-1) call above)
            std::string readData;
            serialPort.Read(readData);
            std::cout << readData << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }catch (std::exception& exception ){
        // Close the serial port
        serialPort.Close();
    }
}

#pragma clang diagnostic pop