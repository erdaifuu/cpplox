#ifndef CPPLOX_PARSER_H
#define CPPLOX_PARSER_H

#include "expr.h"
#include "token.h"

#include <vector>

class Parser
{
public:
    explicit Parser(std::vector<Token> tokens)
        : tokens(std::move(tokens)) {};

private:
    const std::vector<Token> tokens;
    const int current = 0;

    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> equality()
};


#endif //CPPLOX_PARSER_H
