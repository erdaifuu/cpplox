#include "parser.h"

std::unique_ptr<Expr> Parser::expression()
{
    return equality();
}

std::unique_ptr<Expr> Parser::equality()
{
   auto expr = comparison();

    while (match({BANG_EQUAL, EQUAL_EQUAL})) {
        Token op = previous();
        auto right = comparison();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::comparison()
{
    auto expr = term();

    while (match({GREATER, GREATER_EQUAL, LESS, LESS_EQUAL})) {
        Token op = previous();
        auto right = term();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::term()
{
    auto expr = factor();

    while (match({MINUS, PLUS})) {
        Token op = previous();
        auto right = factor();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::factor()
{
    auto expr = unary();

    while (match({SLASH, STAR})) {
        Token op = previous();
        auto right = unary();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::unary()
{
    while (match({BANG, MINUS})) {
        Token op = previous();
        auto right = unary();
        return std::make_unique<Unary>(op, std::move(right));
    }

    return primary();
}

std::unique_ptr<Expr> Parser::primary() {
    if (match({FALSE})) return std::make_unique<Literal>("false");
    if (match({TRUE})) return std::make_unique<Literal>("true");
    if (match({NIL})) return std::make_unique<Literal>("null");

    if (match({NUMBER, STRING})) {
        return std::make_unique<Literal>(previous().literal);
    }

    if (match({LEFT_PAREN})) {
        std::unique_ptr<Expr> expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return std::make_unique<Grouping>(std::move(expr));
    }
}

bool Parser::match(std::initializer_list<TokenType> types)
{
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }

    return false;
}
Token Parser::consume(TokenType type, std::string message) {
    if (check(type)) return advance();

    throw error(peek(), message);
}


bool Parser::check(TokenType type)
{
    if (is_at_end()) return false;
    return peek().type == type;
}

Token Parser::advance()
{
    if (!is_at_end()) current++;
    return previous();
}

bool Parser::is_at_end() const
{
    return peek().type == END_OF_FILE;
}

Token Parser::peek() const
{
    return tokens[current];
}

Token Parser::previous() const
{
    return tokens[current - 1];
}

ParseError error(Token token, std::string message) {
    lox::error(token, message);
    return new ParseError();
}
