#include <utility>
#include <vector>
#include "Morse.hpp"

Token::Token(TokenType _tokenType) : t_start(0), t_end(0), t_duration(0), tokenType(_tokenType) {

}

Token::Token(Token &&token) noexcept: t_start(token.t_start), t_end(token.t_end), t_duration(token.t_duration),
                                      tokenType(token.tokenType) {
}

Token::Token(const Token &token) : t_start(token.t_start), t_end(token.t_end), t_duration(token.t_duration),
                                   tokenType(token.tokenType) {
}

Token::Token(uint64_t tStart, uint64_t tEnd) : t_start(tStart), t_end(tEnd) {}

bool Token::operator==(const Token &rhs) const {
    return tokenType == rhs.tokenType;
}

bool Token::operator!=(const Token &rhs) const {
    return !(rhs == *this);
}

bool Token::operator<(const Token &rhs) const {
    return this->tokenType < rhs.tokenType;
}

bool Token::operator>(const Token &rhs) const {
    return this->tokenType > rhs.tokenType;
}

bool Token::operator>=(const Token &rhs) const {
    return this->tokenType >= rhs.tokenType;
}

bool Token::operator<=(const Token &rhs) const {
    return this->tokenType <= rhs.tokenType;
}

Sequence::Sequence(const std::vector<Token> &tokens) :tokens(tokens) {

}

Sequence::Sequence(const std::vector<TokenType> &tokenTypes) {
    for(auto tokenType : tokenTypes) {
        this->tokens.emplace_back(tokenType);
    }
}


std::optional<std::string> Sequence::addToken(const Token &token) {
    return std::optional<std::string>();
}

std::optional<std::string> Sequence::parse() {
    return std::optional<std::string>();
}

bool Sequence::operator<(const Sequence &rhs) const {
    return tokens < rhs.tokens;
}

bool Sequence::operator>(const Sequence &rhs) const {
    return rhs < *this;
}

bool Sequence::operator<=(const Sequence &rhs) const {
    return !(rhs < *this);
}

bool Sequence::operator>=(const Sequence &rhs) const {
    return !(*this < rhs);
}

bool Sequence::operator==(const Sequence &rhs) const {
    return tokens == rhs.tokens;
}

bool Sequence::operator!=(const Sequence &rhs) const {
    return !(rhs == *this);
}

std::map<Sequence, std::string> Sequence::map{
        MorsePair(Sequence(std::vector<TokenType>{DOT, DASH}), "A"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DASH, DOT, DASH}), "Ä"),
        MorsePair(Sequence(std::vector<TokenType>{DASH, DOT, DOT, DOT}), "B"),
        MorsePair(Sequence(std::vector<TokenType>{DASH, DOT, DASH, DOT}), "C"),
        MorsePair(Sequence(std::vector<TokenType>{DASH, DOT, DOT}), "D"),
        MorsePair(Sequence(std::vector<TokenType>{DOT}), "E"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DOT, DASH, DOT}), "F"),
        MorsePair(Sequence(std::vector<TokenType>{DASH, DASH, DOT}), "G"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DOT, DOT, DOT}), "H"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DOT}), "I"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DASH, DASH, DASH}), "J"),
        MorsePair(Sequence(std::vector<TokenType>{DASH, DOT, DASH}), "K"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DASH, DOT, DOT}), "L"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DOT}), "M"),
        MorsePair(Sequence(std::vector<TokenType>{DASH, DOT}), "N"),
        MorsePair(Sequence(std::vector<TokenType>{DASH, DASH, DASH}), "O"),
        MorsePair(Sequence(std::vector<TokenType>{DASH, DASH, DASH, DOT}), "Ö"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DASH, DASH, DOT}), "P"),
        MorsePair(Sequence(std::vector<TokenType>{DASH, DASH, DOT, DASH}), "Q"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DASH, DOT}), "R"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DOT, DOT}), "S"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DOT, DOT, DASH, DASH, DOT, DOT}), "ẞ"),
        MorsePair(Sequence(std::vector<TokenType>{DASH}), "T"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DOT, DASH}), "U"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DOT, DASH, DASH}), "Ü"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DASH, DASH}), "W"),
        MorsePair(Sequence(std::vector<TokenType>{DASH, DOT, DOT, DASH}), "X"),
        MorsePair(Sequence(std::vector<TokenType>{DASH, DOT, DASH, DASH}), "Y"),
        MorsePair(Sequence(std::vector<TokenType>{DASH, DASH, DOT, DOT}), "Z"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DASH, DASH, DASH}), "1"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DOT, DASH, DASH}), "2"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DOT, DOT, DASH, DASH}), "3"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DOT, DOT, DOT, DASH}), "4"),
        MorsePair(Sequence(std::vector<TokenType>{DOT, DOT, DOT, DOT, DOT}), "5"),
        MorsePair(Sequence(std::vector<TokenType>{DASH, DOT, DOT, DOT, DOT}), "6"),
        MorsePair(Sequence(std::vector<TokenType>{DASH, DASH, DOT, DOT, DOT}), "7"),
        MorsePair(Sequence(std::vector<TokenType>{DASH, DASH, DASH, DOT, DOT}), "8"),
        MorsePair(Sequence(std::vector<TokenType>{DASH, DASH, DASH, DASH, DOT}), "9"),
        MorsePair(Sequence(std::vector<TokenType>{DASH, DASH, DASH, DASH, DASH}), "0"),

};