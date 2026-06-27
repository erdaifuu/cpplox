#include "parser.h"

#include "lox.h"

std::unique_ptr<expr> parser::parse() {
    try {
        return expression();
    } catch (const parse_error&) {
        return nullptr;
    }
}

std::unique_ptr<expr> parser::expression()
{
    return equality();
}

std::unique_ptr<expr> parser::equality()
{
   auto expr = comparison();

    while (match({BANG_EQUAL, EQUAL_EQUAL})) {
        token op = previous();
        auto right = comparison();
        expr = std::make_unique<binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<expr> parser::comparison()
{
    auto expr = term();

    while (match({GREATER, GREATER_EQUAL, LESS, LESS_EQUAL})) {
        token op = previous();
        auto right = term();
        expr = std::make_unique<binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<expr> parser::term()
{
    auto expr = factor();

    while (match({MINUS, PLUS})) {
        token op = previous();
        auto right = factor();
        expr = std::make_unique<binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<expr> parser::factor()
{
    auto expr = unary();

    while (match({SLASH, STAR})) {
        token op = previous();
        auto right = unary();
        expr = std::make_unique<binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<expr> parser::unary()
{
    while (match({BANG, MINUS})) {
        token op = previous();
        auto right = unary();
        return std::make_unique<unary>(op, std::move(right));
    }

    return primary();
}

std::unique_ptr<expr> parser::primary() {
    if (match({FALSE})) return std::make_unique<literal>("false");
    if (match({TRUE})) return std::make_unique<literal>("true");
    if (match({NIL})) return std::make_unique<literal>("null");

    if (match({NUMBER, STRING})) {
        return std::make_unique<literal>(previous().literal);
    }

    if (match({LEFT_PAREN})) {
        std::unique_ptr<expr> expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return std::make_unique<grouping>(std::move(expr));
    }

    throw error(peek(), "Expect expression.");
}

bool parser::match(std::initializer_list<token_type> types)
{
    for (token_type type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }

    return false;
}
token parser::consume(token_type type, std::string message) {
    if (check(type)) return advance();

    throw error(peek(), message);
}


bool parser::check(token_type type)
{
    if (is_at_end()) return false;
    return peek().type == type;
}

token parser::advance()
{
    if (!is_at_end()) current++;
    return previous();
}

bool parser::is_at_end() const
{
    return peek().type == END_OF_FILE;
}

token parser::peek() const
{
    return tokens[current];
}

token parser::previous() const
{
    return tokens[current - 1];
}

parser::parse_error parser::error(const token& token, const std::string& message) {
    ::error(token, message);
    return {};
}

void parser::synchronize() {
    advance();

    while (!is_at_end()) {
        if (previous().type == SEMICOLON) return;

        switch (peek().type) {
        case CLASS:
        case FUN:
        case VAR:
        case FOR:
        case IF:
        case WHILE:
        case PRINT:
        case RETURN:
            return;
        }

        advance();
    }
}
