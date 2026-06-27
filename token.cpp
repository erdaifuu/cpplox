#include "token.h"

#include <string>

std::string token::to_string() const
{
    return std::to_string(type) + " " + lexeme + " " + literal;
}

std::ostream& operator<<(std::ostream& os, const token& t)
{
    return os << t.to_string();
}