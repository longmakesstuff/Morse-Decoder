#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main() {
    uint32_t buffer;
    FILE *file = fopen("/dev/ttyACM0", "rb");
    while (true) {
        size_t readed = fread(&buffer, 4, 1, file);
        std::cout << readed << ": " << buffer << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

#pragma clang diagnostic pop