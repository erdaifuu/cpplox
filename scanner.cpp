#include "scanner.h"
#include <utility>

#include "lox.h"

const std::unordered_map<std::string, TokenType> Scanner::keywords = {
    {"and",    AND},
    {"class",  CLASS},
    {"else",   ELSE},
    {"false",  FALSE},
    {"for",    FOR},
    {"fun",    FUN},
    {"if",     IF},
    {"nil",    NIL},
    {"or",     OR},
    {"print",  PRINT},
    {"return", RETURN},
    {"super",  SUPER},
    {"this",   THIS},
    {"true",   TRUE},
    {"var",    VAR},
    {"while",  WHILE},
};

// helpers

bool Scanner::is_at_end() const
{
    return current >= source.length();
}

char Scanner::advance()
{
    return source[current++];
}

bool Scanner::match(char expected)
{
    if (is_at_end()) return false;
    if (source[current] != expected) return false;

    current++;
    return true;
}

char Scanner::peek() const
{
    if (is_at_end()) return '\0';
    return source[current];
}

char Scanner::peek_next() const
{
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];
}

// token

std::vector<Token> Scanner::scan_tokens()
{
    while (!is_at_end())
    {
        // We are at the beginning of the next lexeme.
        start = current;
        scan_token();
    }

    tokens.emplace_back(END_OF_FILE, "", "", line);
    return tokens;
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
    case '!': add_token(match('=') ? BANG_EQUAL : BANG); break;
    case '=': add_token(match('=') ? EQUAL_EQUAL : EQUAL); break;
    case '<': add_token(match('=') ? LESS_EQUAL : LESS); break;
    case '>': add_token(match('=') ? GREATER_EQUAL : GREATER); break;
    case '/':
        if (match('/')) { while (peek() != '\n' && !is_at_end()) advance(); }
        else { add_token(SLASH); }
        break;
    case ' ':
    case '\r':
    case '\t':
        break;
    case '\n': line++; break;

    // String Literals
    case '"': string(); break;

    // Digits (default case to avoid manual checking all 0-9 cases)
    default:
        //  I used static_cast with std here, then defined is_digit later, this is just for future reference & cool
        if (std::isdigit(static_cast<unsigned char>(c))) {
            number();
        } else if (is_alpha(c)) {
            identifier();
        } else {
            error(line, "Unexpected character.");
        }
    }
}

void Scanner::add_token(TokenType type)
{
    add_token(type, "");
}

void Scanner::add_token(TokenType type, const std::string& literal)
{
    std::string text = source.substr(start, current - start);
    tokens.emplace_back(type, text, literal, line);
}

// literal scanner helpers

void Scanner::string()
{
    while (peek() != '"' && !is_at_end()) {
        if (peek() == '\n') line++;
        advance();
    }

    if (is_at_end()) {
        error(line, "Unterminated string.");
        return;
    }

    // The closing ".
    advance();

    // Trim the surrounding quotes.
    std::string value = source.substr(start + 1, current - start - 2);
    add_token(STRING, value);
}

void Scanner::number()
{
    while (is_digit(peek())) advance();

    // Look for a fractional part.
    if (peek() == '.' && is_digit(peek_next())) {
        // Consume the "."
        advance();

        while (is_digit(peek())) advance();
    }

    // TODO: add_token can actually take other types (in Java we used Object, in C++ ?)
    // add_token(NUMBER, std::stod(source.substr(start, current - start)));
    add_token(NUMBER, source.substr(start, current - start));
}

void Scanner::identifier()
{
    while (is_alphanumeric(peek())) advance();

    std::string text = source.substr(start, current - start);
    TokenType type = IDENTIFIER;
    auto it = keywords.find(text);
    if (it != keywords.end()) type = it->second;
    add_token(type);
}

// static character classification

bool Scanner::is_digit(const char c)
{
    return c >= '0' && c <= '9';
}

bool Scanner::is_alpha(const char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
            c == '_';
}

bool Scanner::is_alphanumeric(const char c)
{
    return is_alpha(c) || is_digit(c);
}
