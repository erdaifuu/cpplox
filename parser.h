#ifndef CPPLOX_PARSER_H
#define CPPLOX_PARSER_H

#include "expr.h"
#include "token.h"

#include <vector>

class parser
{
public:
    explicit parser(std::vector<token> tokens)
        : tokens(std::move(tokens)) {};

private:
    // helpers
    bool match(std::initializer_list<token_type> types);
    bool check(token_type type);
    token consume(token_type type, std::string message);
    token advance();
    bool is_at_end() const;
    token peek() const;
    token previous() const;

    // parsing
    std::unique_ptr<expr> expression();
    std::unique_ptr<expr> equality();
    std::unique_ptr<expr> comparison();
    std::unique_ptr<expr> term();
    std::unique_ptr<expr> factor();
    std::unique_ptr<expr> unary();
    std::unique_ptr<expr> primary();

    // variables
    const std::vector<token> tokens;
    int current = 0;
};


#endif //CPPLOX_PARSER_H
