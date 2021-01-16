#include <utility>
#include <vector>
#include "Morse.hpp"


Morse::Morse() {
    map = std::map<std::string, std::string>{
            MorsePair("A", ".-"),
            MorsePair("B", "-..."),
            MorsePair("C", "-.-."),
            MorsePair("D", "-.."),
            MorsePair("E", "."),
            MorsePair("F", "..-."),
            MorsePair("G", "--."),
            MorsePair("H", "...."),
            MorsePair("I", ".."),
            MorsePair("J", ".---"),
            MorsePair("K", "-.-"),
            MorsePair("L", ".-.."),
            MorsePair("M", "--"),
            MorsePair("N", "-."),
            MorsePair("O", "---"),
            MorsePair("P", ".--."),
            MorsePair("Q", "--.-"),
            MorsePair("R", ".-."),
            MorsePair("S", "..."),
            MorsePair("T", "-"),
            MorsePair("U", "..-"),
            MorsePair("V", "...-"),
            MorsePair("W", ".--"),
            MorsePair("X", "-..-"),
            MorsePair("Y", "-.--"),
            MorsePair("Z", "--.."),
            MorsePair("1", ".----"),
            MorsePair("2", "..---"),
            MorsePair("3", "...--"),
            MorsePair("4", "....-"),
            MorsePair("5", "....."),
            MorsePair("6", "-...."),
            MorsePair("7", "--..."),
            MorsePair("8", "---.."),
            MorsePair("9", "----."),
            MorsePair("0", "-----"),
            MorsePair(",", "--..--"),
            MorsePair(".", ".-.-.-"),
            MorsePair("?", "..--.."),
            MorsePair("/", "-..-."),
            MorsePair("-", "-....-"),
            MorsePair("(", "-.--."),
            MorsePair(")", "-.--.-")
    };

}

std::optional<std::string> Morse::parse() {
    // Splitting by white space
    std::stringstream ss;
    for (const auto &token : tokens) {
        ss << token;
    }
    std::vector<std::string> words = strSplit(ss.str(), "\n");

    //
}

bool Morse::operator<(const Morse &rhs) const {
    return tokens < rhs.tokens;
}

bool Morse::operator>(const Morse &rhs) const {
    return rhs < *this;
}

bool Morse::operator<=(const Morse &rhs) const {
    return !(rhs < *this);
}

bool Morse::operator>=(const Morse &rhs) const {
    return !(*this < rhs);
}

bool Morse::operator==(const Morse &rhs) const {
    return tokens == rhs.tokens;
}

bool Morse::operator!=(const Morse &rhs) const {
    return !(rhs == *this);
}
