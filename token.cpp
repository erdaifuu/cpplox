#include "token.h"

#include <string>

std::string Token::to_string() const {
    return std::to_string(type) + " " + lexeme + " " + literal;
}

std::ostream& operator<<(std::ostream& os, const Token& t) {
    return os << t.to_string();
}