#pragma once

#include <cstdint>
#include <string>
#include <map>
#include <optional>
#include <sstream>
#include "String.hpp"

constexpr char DOT = '.';
constexpr char DASH = '-';
constexpr char SPACE = ' ';

class Morse {
private:
    std::map<std::string, std::string> map{};
    std::vector<std::string> tokens;
public:
    Morse();

    std::optional<std::string> parse();

    bool operator<(const Morse &rhs) const;

    bool operator>(const Morse &rhs) const;

    bool operator<=(const Morse &rhs) const;

    bool operator>=(const Morse &rhs) const;

    bool operator==(const Morse &rhs) const;

    bool operator!=(const Morse &rhs) const;
};

typedef std::pair<std::string, std::string> MorsePair;
