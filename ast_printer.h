#ifndef CPPLOX_AST_PRINTER_H
#define CPPLOX_AST_PRINTER_H

#include <string>
#include <initializer_list>
#include "expr.h"

struct AstPrinter : Visitor {
    std::string result;

    std::string print(Expr& expr) {
        expr.accept(*this);
        return result;
    }

    void visit_literal(Literal& expr) override {
        result = expr.value.empty() ? "nil" : expr.value;
    }

    void visit_grouping(Grouping& expr) override {
        parenthesize("group", {expr.expression.get()});
    }

    void visit_unary(Unary& expr) override {
        parenthesize(expr.op.lexeme, {expr.right.get()});
    }

    void visit_binary(Binary& expr) override {
        parenthesize(expr.op.lexeme, {expr.left.get(), expr.right.get()});
    }

private:
    void parenthesize(const std::string& name, std::initializer_list<Expr*> exprs) {
        std::string out = "(" + name;
        for (Expr* expr : exprs) {
            expr->accept(*this);
            out += " " + result;
        }
        out += ")";
        result = out;
    }
};


#endif //CPPLOX_AST_PRINTER_H
