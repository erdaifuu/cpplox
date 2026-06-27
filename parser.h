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
    // helpers
    bool match(std::initializer_list<TokenType> types);
    bool check(TokenType type);
    Token consume(TokenType type, std::string message);
    Token advance();
    bool is_at_end() const;
    Token peek() const;
    Token previous() const;

    // parsing
    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> comparison();
    std::unique_ptr<Expr> term();
    std::unique_ptr<Expr> factor();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> primary();

    // variables
    const std::vector<Token> tokens;
    int current = 0;
};


#endif //CPPLOX_PARSER_H
