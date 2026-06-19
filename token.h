#ifndef CPPLOX_TOKEN_H
#define CPPLOX_TOKEN_H

#include "token_type.h"
#include <string>

class Token
{
public:
    const token_type type;
    const std::string lexeme;
    const std::string literal;
    const int line;

    Token(token_type type, std::string lexeme, std::string literal, int line)
        : type(type), lexeme(lexeme), literal(literal), line(line) {}

    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const Token& t);
};

#endif //CPPLOX_TOKEN_H
