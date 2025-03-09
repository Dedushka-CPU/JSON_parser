#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <fstream>
#include <string>

enum class TOKEN {
    CURLY_OPEN,
    CURLY_CLOSE,
    COLON,
    STRING,
    NUMBER,
    ARRAY_OPEN,
    ARRAY_CLOSE,
    COMMA,
    BOOLEAN,
    NULL_TYPE
};

struct Token {
    std::string value;
    TOKEN type;
    std::string toString();
};

class Tokenizer {
private:
    std::fstream file;
    std::streampos prevPos;
    char getWithoutWhiteSpace();

public:
    explicit Tokenizer(const std::string& fileName);
    Token getToken();
    bool hasMoreTokens();
    void rollBackToken();
};

#endif