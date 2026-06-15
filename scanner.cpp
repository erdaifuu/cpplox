#include "scanner.h"
#include <utility>

std::vector<Token> scan_tokens()
{
    while (!isAtEnd())
    {
        // We are at the beginning of the next lexeme.
        start = current;
        scan_token();
    }

    tokens.push_back(Token( END_OF_FILE , "", null, line));
    return tokens;
}