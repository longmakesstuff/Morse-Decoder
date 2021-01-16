#include "Morse.hpp"


Morse::Morse() {
    this->alphaToMorse = std::map<std::string, std::string>{
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
    this->morseToAlpha = reverse_map(this->alphaToMorse);
}

std::optional<std::string> Morse::encode(const std::string &word) {
    std::stringstream ss;
    for (char letter : word) {
        if (letter == ' ') { // White space, no need to encode
            ss << ' ';
        } else { // Everything else, encode
            auto tryFind = this->alphaToMorse.find(std::string(1, letter));
            if (tryFind != this->alphaToMorse.end()) {
                ss << tryFind->second;
            } else { // Defect word, no code for this letter found
                return std::nullopt;
            }
        }
    }
    return std::optional<std::string>();
}

std::optional<std::string> Morse::decode(const std::string &code) {
    // Try the whole morse word first if success, nothing else must be done
    auto tryWholeWord = this->morseToAlpha.find(code);

    if (tryWholeWord != this->morseToAlpha.end()) { // The token can be decoded as whole, easy take.
        return std::optional(code);
    } else { // The current morse token is not a single letter, have to decode letter for letter now.
        // The current letter consist of more than one letters or none at all (defect code)
        // Try letter for letter of the morse word

        // Parsed characters of the code
        std::vector<std::string> characters;

        // Iterate letter for letter from the token
        std::stringstream buffer;

        // If the chars from the buffer could be decoded, the decoded lastDecodedChar will be stored here
        std::string lastDecodedChar;

        // Indicate if the buffer was decoded once in the past run
        bool decodedOnce = false;

        // Iterate letter for letter
        for (char letter : code) {
            buffer << letter;

            auto tryLetter = this->morseToAlpha.find(buffer.str());

            if (tryLetter != this->morseToAlpha.end()) { // Can decode the buffer, store the decoded lastDecodedChar
                decodedOnce = true;
                lastDecodedChar = tryLetter->second;
            } else if (decodedOnce) {
                // Can not decode the buffer. Since the string lastDecodedChar is a valid decoded string, we can append it to the end lastDecodedChar

                // Reset buffer for the next letter
                buffer = std::stringstream{};

                // Append the current letter for the next round
                buffer << letter;

                // Push the parsed character to end lastDecodedChar
                characters.push_back(lastDecodedChar);

                // Reset flag
                decodedOnce = false;
            } else {
                // The code is invalid and can not be parsed, break
                return std::nullopt;
            }
        }

        // Concat the parsed letters to a word and return it
        std::stringstream result;
        for (const auto &parsedLetter : characters) {
            result << parsedLetter;
        }
        return std::optional(result.str());
    }
}


std::optional<std::string> Morse::parse() {
    // Splitting by white space
    std::stringstream ss;
    for (const auto &token : this->tokens) {
        ss << token;
    }
    std::vector<std::string> codes = strSplit(ss.str(), " ");

    // Check for empty list
    if (codes.empty()) {
        return std::nullopt;
    }

    // Every parsed codes from the buffer
    std::vector<std::string> parsed;

    // Check every word except the last one
    // The last one could still not be complete
    for (size_t i = 0; i < codes.size() - 1; i++) {
        std::string code = codes[i];
        std::optional<std::string> parsedWord = this->decode(code);
        if (parsedWord.has_value()) {
            parsed.push_back(parsedWord.value());
            parsed.emplace_back(" ");
        }
    }

    // Only parse the last code if the code is complete
    if(this->tokens.back() == " "){ // If the last letter is a white space, then the last code is complete
        std::optional<std::string> parsedWord = this->decode(codes.back());
        if (parsedWord.has_value()) {
            parsed.push_back(parsedWord.value());
            parsed.emplace_back(" ");
        }

        // Reset the tokens
        this->tokens = std::vector<std::string>();
    } else { // If the last letter is not a white space, the last code is still not complete
        // Reset the token
        this->tokens = std::vector<std::string>();

        // Push the last incomplete code back to tokens
        for(char & i : codes.back()) {
            this->tokens.emplace_back(1, i);
        }
    }

    // Nothing was parsed
    if (parsed.empty()) {
        return std::nullopt;
    } else {
        // Return the parsed values
        std::stringstream result;

        for (auto &i : parsed) {
            result << i;
        }

        return std::optional(result.str());
    }
}

void Morse::add(const std::string &code) {
    if(code.size() == 1) {
        this->tokens.push_back(code);
    }else if (code.size() > 1) {
        for(char i : code) {
            this->tokens.emplace_back(1, i);
        }
    }
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
