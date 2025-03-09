#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "JSONNode.h"
#include "Tokenizer.h"
#include <memory>
#include <fstream>

class JSONParser {
private:
    std::fstream file;
    std::shared_ptr<JSON::JSONNode> root;
    std::unique_ptr<JSON::JSONNode> current;
    Tokenizer tokenizer;

    std::shared_ptr<JSON::JSONNode> parseObject();
    std::shared_ptr<JSON::JSONNode> parseString();
    std::shared_ptr<JSON::JSONNode> parseNumber();
    std::shared_ptr<JSON::JSONNode> parseList();
    std::shared_ptr<JSON::JSONNode> parseBoolean();
    std::shared_ptr<JSON::JSONNode> parseNull();

public:
    explicit JSONParser(const std::string& filename);
    void parse();
};

#endif