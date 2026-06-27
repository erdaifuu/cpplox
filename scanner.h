#ifndef CPPLOX_SCANNER_H
#define CPPLOX_SCANNER_H

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "token_type.h"
#include "token.h"

class scanner
{
public:
    explicit scanner(std::string source)
        : source(std::move(source)) {}
    std::vector<token> scan_tokens();

private:
    // helpers
    bool is_at_end() const;
    char advance();
    bool match(char expected);
    char peek() const;
    char peek_next() const;

    // token
    void scan_token();
    void add_token(token_type type);
    void add_token(token_type type, const std::string& literal);

    // literal scanner helpers
    void string();
    void number();
    void identifier();

    // static char classification
    static bool is_digit(char c);
    static bool is_alpha(char c);
    static bool is_alphanumeric(char c);

    // variables
    const std::string source;
    std::vector<token> tokens;
    static const std::unordered_map<std::string, token_type> keywords;

    int start{};
    // TODO: we use current to grab token substrings, but in C++ we use start_index + length for that. Swap out with length eventually.
    int current{};
    int line{1};
};

#endif //CPPLOX_SCANNER_H
