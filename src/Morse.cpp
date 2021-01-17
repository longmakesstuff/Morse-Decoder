#include "Morse.hpp"


Morse::Morse() {
    this->alphaToMorse = std::map<std::string, std::string>{
            MorsePair("A", ".-"),
            MorsePair("Ä", ".-.-"),
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
            MorsePair("Ö", "---."),
            MorsePair("P", ".--."),
            MorsePair("Q", "--.-"),
            MorsePair("R", ".-."),
            MorsePair("S", "..."),
            MorsePair("ẞ", "...--.."),
            MorsePair("T", "-"),
            MorsePair("U", "..-"),
            MorsePair("Ü", "..--"),
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
            MorsePair(" ", "/"),
            MorsePair(":", "---..."),
            MorsePair(":", "-.--.-"),
    };
    this->morseToAlpha = reverse_map(this->alphaToMorse);
}

std::optional<std::string> Morse::encode(const std::string &word) {
    std::stringstream ss;
    for (size_t i = 0; i < word.size(); i++) {
        char upperLetter = std::toupper(word[i]);
        auto tryFind = this->alphaToMorse.find(std::string(1, upperLetter));
        if (tryFind != this->alphaToMorse.end()) {
            ss << tryFind->second;
        } else { // Defect word, no code for this letter found
            return std::nullopt;
        }
        // Append space unless last letter
        if (i != word.size() - 1) {
            ss << ' ';
        }
    }
    return std::optional<std::string>(ss.str());
}

std::optional<std::string> Morse::decode(const std::string &code) {
    // Try the whole morse word first if success, nothing else must be done
    auto tryWholeWord = this->morseToAlpha.find(code);

    if (tryWholeWord != this->morseToAlpha.end()) { // The token can be decoded as whole, easy take.
        return std::optional(tryWholeWord->second);
    } else { // The current morse token is not a single letter, have to decode letter for letter now.
        std::vector<std::string> letters = strSplit(code, " ");
        if (letters.empty()) {
            return std::nullopt;
        }

        std::stringstream ss;
        for (const auto &letter : letters) {
            auto encoded = this->morseToAlpha.find(letter);
            if (encoded != this->morseToAlpha.end()) {
                ss << encoded->second;
            } else {
                return std::nullopt;
            }
        }
        return std::optional(ss.str());
    }
}


std::optional<std::string> Morse::parse() {
    // Merge all together
    std::stringstream ss;
    for(const auto& token : this->tokens) {
        ss << token;
    }

    // Decode letter for letter
    std::vector<std::string> codeBlocks = strSplit(ss.str(), " ");
    if(codeBlocks.empty()) {
        return std::nullopt;
    }

    std::stringstream result;
    for(const auto& code : codeBlocks) {
        auto decoded = this->decode(code);
        if(decoded.has_value()) {
            result << decoded.value();
        }
    }

    // Reset current
    this->tokens = std::vector<std::string>();
    return std::optional(result.str());
}

void Morse::add(const std::string &code) {
    if (code.size() == 1) {
        this->tokens.push_back(code);
    } else if (code.size() > 1) {
        for (char i : code) {
            this->tokens.emplace_back(1, i);
        }
    }
}

void Morse::add(const char &code) {
    this->tokens.emplace_back(1, code);
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

std::map<std::string, std::string> &Morse::getAlphaToMorse() {
    return alphaToMorse;
}

std::map<std::string, std::string> &Morse::getMorseToAlpha() {
    return morseToAlpha;
}

std::ostream &operator<<(std::ostream &os, const Morse &morse) {
    os << "[Morse]{";
    for(const auto& letter : morse.tokens) {
        os << letter << ", ";
    }
    os << "}";
    return os;
}
