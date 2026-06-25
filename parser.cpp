//
// Created by Carl Luo on 24/06/2026.
//

#include "parser.h"

std::unique_ptr<Expr> expression()
{
    return equality();
}

std::unique_ptr<Expr> equality()
{
   auto expr = comparison();

    while (match(BANG_EQUAL, EQUAL_EQUAL)) {
        Token op = previous();
        auto right = comparison();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }
}
