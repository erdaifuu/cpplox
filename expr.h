#ifndef CPPLOX_EXPR_H
#define CPPLOX_EXPR_H

#include <memory>
#include <string>
#include "token.h"

struct binary;
struct grouping;
struct literal;
struct unary;

struct visitor {
    virtual void visit_binary(binary& expr) = 0;
    virtual void visit_grouping(grouping& expr) = 0;
    virtual void visit_literal(literal& expr) = 0;
    virtual void visit_unary(unary& expr) = 0;
    virtual ~visitor() = default;
};

struct expr {
    virtual void accept(visitor& visitor) = 0;
    virtual ~expr() = default;
};

struct binary : expr {
    std::unique_ptr<expr> left;
    token op;
    std::unique_ptr<expr> right;

    binary(std::unique_ptr<expr> left, token op, std::unique_ptr<expr> right)
        : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

    void accept(visitor& visitor) override { visitor.visit_binary(*this); }
};

struct grouping : expr {
    std::unique_ptr<expr> expression;

    explicit grouping(std::unique_ptr<expr> expression)
        : expression(std::move(expression)) {}

    void accept(visitor& visitor) override { visitor.visit_grouping(*this); }
};

struct literal : expr {
    std::string value;

    explicit literal(std::string value)
        : value(std::move(value)) {}

    void accept(visitor& visitor) override { visitor.visit_literal(*this); }
};

struct unary : expr {
    token op;
    std::unique_ptr<expr> right;

    unary(token op, std::unique_ptr<expr> right)
        : op(std::move(op)), right(std::move(right)) {}

    void accept(visitor& visitor) override { visitor.visit_unary(*this); }
};

#endif //CPPLOX_EXPR_H
