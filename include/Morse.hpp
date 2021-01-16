#pragma once

#include <cstdint>
#include <string>
#include <map>
#include <optional>

typedef enum TokenType {
    DOT, DASH
} TokenType;

class Token {
    uint64_t t_start;
    uint64_t t_end;
    uint64_t t_duration{};
    TokenType tokenType{};
public:
    Token(TokenType _tokenType);

    Token(Token && token) noexcept;

    Token(const Token & token);

    Token(uint64_t tStart, uint64_t tEnd);

    bool operator==(const Token &rhs) const;

    bool operator!=(const Token &rhs) const;

    bool operator<(const Token &rhs) const;

    bool operator>(const Token &rhs) const;

    bool operator<=(const Token &rhs) const;

    bool operator>=(const Token &rhs) const;
};

class Sequence {
private:
    std::vector<Token> tokens;
    static std::map<Sequence, std::string> map;
public:
    explicit Sequence(const std::vector<Token>& tokens);

    Sequence(const std::vector<TokenType>& tokenTypes);

    std::optional<std::string> addToken(const Token& token);

    std::optional<std::string> parse();

    bool operator<(const Sequence &rhs) const;

    bool operator>(const Sequence &rhs) const;

    bool operator<=(const Sequence &rhs) const;

    bool operator>=(const Sequence &rhs) const;

    bool operator==(const Sequence &rhs) const;

    bool operator!=(const Sequence &rhs) const;
};

typedef std::pair< Sequence, std::string> MorsePair;
