#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <fstream>
#include <iostream>
#include <memory> 

enum class TOKEN{
    UNKNOWN_TYPE,
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

struct Token{
    std::string value;
    TOKEN type;
    std::string toString();
};

class Tokenizer{
private:
    std::fstream file;
    size_t prevPos;
public:
    Tokenizer(std::string fileName);
    auto getWithoutSpace();
    auto getToken();
    auto hasMoreTokens();
    void rollBackToken();
};

#endif // TOKENIZER_H