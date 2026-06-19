#include "scanner.h"
#include <utility>

std::vector<Token> Scanner::scan_tokens()
{
    while (!isAtEnd())
    {
        // We are at the beginning of the next lexeme.
        start = current;
        scan_token();
    }

    tokens.emplace_back( END_OF_FILE , "", "", line);
    return tokens;
}

bool Scanner::is_at_end() const {
    return current >= source.length();
}

void Scanner::scan_token()
{
    char c = advance();
    switch (c)
    {
        case '(': add_token(LEFT_PAREN); break;
        case ')': add_token(RIGHT_PAREN); break;
        case '{': add_token(LEFT_BRACE); break;
        case '}': add_token(RIGHT_BRACE); break;
        case ',': add_token(COMMA); break;
        case '.': add_token(DOT); break;
        case '-': add_token(MINUS); break;
        case '+': add_token(PLUS); break;
        case ';': add_token(SEMICOLON); break;
        case '*': add_token(STAR); break;
    default:
        Lox.error(line, "Unexpected character.");;
    }
}

char Scanner::advance() {
    return source[current++];
}

void Scanner::add_token(token_type type) {
    add_token(type, "");
}

void Scanner::add_token(token_type type, const std::string& literal) {
    std::string text = source.substr(start, current - start);
    tokens.emplace_back(type, text, literal, line);
}
