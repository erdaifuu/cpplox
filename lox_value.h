//
// Created by Carl Luo on 30/06/2026.
//

#ifndef CPPLOX_LOX_VALUE_H
#define CPPLOX_LOX_VALUE_H

#include <string>
#include <variant>

using lox_value = std::variant<std::monostate, bool, double, std::string>;

#endif //CPPLOX_LOX_VALUE_H
