#ifndef CPPLOX_SCANNER_H
#define CPPLOX_SCANNER_H

#include <string>
#include <utility>
#include <vector>
#include "token_type.h"
#include "token.h"

class Scanner
{
public:
    Scanner(std::string source)
        : source(std::move(source)) {}
    std::vector<Token> scan_tokens();

private:
    const std::string source;
    std::vector<Token> tokens;
    int start{};
    int current{};
    int line{1};
    std::
};

#endif //CPPLOX_SCANNER_H
