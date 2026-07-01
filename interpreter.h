//
// Created by Carl Luo on 28/06/2026.
//

#ifndef CPPLOX_INTERPRETER_H
#define CPPLOX_INTERPRETER_H

#include "expr.h"
#include "lox_value.h"

class interpreter : public visitor
{
public:
    lox_value visit_literal(literal& expr) override {
        return expr.value;
    }
};


#endif //CPPLOX_INTERPRETER_H
