#ifndef CPPLOX_EXPR_H
#define CPPLOX_EXPR_H

#include <memory>
#include <string>
#include "token.h"

struct Binary;
struct Grouping;
struct Literal;
struct Unary;

struct Visitor {
    virtual void visit_binary(Binary& expr) = 0;
    virtual void visit_grouping(Grouping& expr) = 0;
    virtual void visit_literal(Literal& expr) = 0;
    virtual void visit_unary(Unary& expr) = 0;
    virtual ~Visitor() = default;
};

struct Expr {
    virtual void accept(Visitor& visitor) = 0;
    virtual ~Expr() = default;
};

struct Binary : Expr {
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;

    Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
        : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

    void accept(Visitor& visitor) override { visitor.visit_binary(*this); }
};

struct Grouping : Expr {
    std::unique_ptr<Expr> expression;

    explicit Grouping(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {}

    void accept(Visitor& visitor) override { visitor.visit_grouping(*this); }
};

struct Literal : Expr {
    std::string value;

    explicit Literal(std::string value)
        : value(std::move(value)) {}

    void accept(Visitor& visitor) override { visitor.visit_literal(*this); }
};

struct Unary : Expr {
    Token op;
    std::unique_ptr<Expr> right;

    Unary(Token op, std::unique_ptr<Expr> right)
        : op(std::move(op)), right(std::move(right)) {}

    void accept(Visitor& visitor) override { visitor.visit_unary(*this); }
};

#endif //CPPLOX_EXPR_H
