#ifndef CPPLOX_AST_PRINTER_H
#define CPPLOX_AST_PRINTER_H

#include <string>
#include <initializer_list>
#include "expr.h"

struct AstPrinter : visitor {
    std::string result;

    std::string print(expr& expr) {
        expr.accept(*this);
        return result;
    }

    void visit_literal(literal& expr) override {
        result = expr.value.empty() ? "nil" : expr.value;
    }

    void visit_grouping(grouping& expr) override {
        parenthesize("group", {expr.expression.get()});
    }

    void visit_unary(unary& expr) override {
        parenthesize(expr.op.lexeme, {expr.right.get()});
    }

    void visit_binary(binary& expr) override {
        parenthesize(expr.op.lexeme, {expr.left.get(), expr.right.get()});
    }

private:
    void parenthesize(const std::string& name, std::initializer_list<expr*> exprs) {
        std::string out = "(" + name;
        for (expr* expr : exprs) {
            expr->accept(*this);
            out += " " + result;
        }
        out += ")";
        result = out;
    }
};


#endif //CPPLOX_AST_PRINTER_H
