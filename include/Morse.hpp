#pragma once

#include <cstdint>
#include <string>
#include <map>
#include <optional>
#include <sstream>
#include <vector>
#include "String.hpp"

template<typename K, typename V>
static std::map<V, K> reverse_map(const std::map<K, V>& m) {
    std::map<V, K> r;
    for (const auto& kv : m)
        r[kv.second] = kv.first;
    return r;
}

class Morse {
private:
    std::map<std::string, std::string> alphaToMorse{};
    std::map<std::string, std::string> morseToAlpha{};
    std::vector<std::string> tokens;

public:
    Morse();

    /**
     * Converting english words to morse equivalent
     * @param word english word
     * @return morse code
     */
    std::optional<std::string> encode(const std::string& word);

    /**
     * Decode a single code block to english word
     * @param code a code block
     * @return english world
     */
    std::optional<std::string> decode(const std::string& code);

    /**
     * Decode the whole block of code and return decoded words
     * @return decoded words
     */
    std::optional<std::string> parse();

    /**
     * Append letter for letter from the code into the buffer
     * @param code incoming code
     */
    void add(const std::string& code);

    bool operator<(const Morse &rhs) const;

    bool operator>(const Morse &rhs) const;

    bool operator<=(const Morse &rhs) const;

    bool operator>=(const Morse &rhs) const;

    bool operator==(const Morse &rhs) const;

    bool operator!=(const Morse &rhs) const;
};

typedef std::pair<std::string, std::string> MorsePair;
