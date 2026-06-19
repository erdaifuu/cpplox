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
    explicit Scanner(std::string source)
        : source(std::move(source)) {}
    std::vector<Token> scan_tokens();

private:
    bool is_at_end() const;
    void scan_token();
    char advance();
    void add_token(token_type type);
    void add_token(token_type type, const std::string& literal);

    const std::string source;
    std::vector<Token> tokens;

    int start{};
    // TODO: we use current to grab token substrings, but in C++ we use start_index + length for that. Swap out with length eventually.
    int current{};
    int line{1};
};

#endif //CPPLOX_SCANNER_H
