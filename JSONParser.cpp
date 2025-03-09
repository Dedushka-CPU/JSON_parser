#include "JSONParser.h"
#include <iostream>

JSONParser::JSONParser(const std::string& filename) : tokenizer(filename) {}

void JSONParser::parse() {
    std::string key;
    while (tokenizer.hasMoreTokens()) {
        Token token;
        try {
            token = tokenizer.getToken();
            std::cout << token.toString() << std::endl;
            switch (token.type) {
            case TOKEN::CURLY_OPEN: {
                std::shared_ptr<JSON::JSONNode> parsedObject = parseObject();
                parsedObject->printNode(0);
                if (!root) {
                    root = parsedObject;
                }
                break;
            }
            case TOKEN::ARRAY_OPEN: {
                std::shared_ptr<JSON::JSONNode> parsedList = parseList();
                if (!root) {
                    root = parsedList;
                }
                break;
            }
            case TOKEN::STRING: {
                tokenizer.rollBackToken();
                std::shared_ptr<JSON::JSONNode> parsedString = parseString();
                if (!root) {
                    root = parsedString;
                }
                break;
            }
            case TOKEN::NUMBER: {
                tokenizer.rollBackToken();
                std::shared_ptr<JSON::JSONNode> parsedNumber = parseNumber();
                if (!root) {
                    root = parsedNumber;
                }
                break;
            }
            case TOKEN::BOOLEAN: {
                tokenizer.rollBackToken();
                std::shared_ptr<JSON::JSONNode> parsedBoolean = parseBoolean();
                break;
            }
            case TOKEN::NULL_TYPE: {
                tokenizer.rollBackToken();
                std::shared_ptr<JSON::JSONNode> parsedNull = parseNull();
                if (!root) {
                    root = parsedNull;
                }
                break;
            }
            default:
                break;
            }
        }
        catch (const std::logic_error&) {
            break;
        }
    }
}

std::shared_ptr<JSON::JSONNode> JSONParser::parseObject() {
    std::cout << "Parsing object" << std::endl;
    std::shared_ptr<JSON::JSONNode> node = std::make_shared<JSON::JSONNode>();
    JSON::JSONObject* keyObjectMap = new JSON::JSONObject();
    bool hasCompleted = false;
    while (!hasCompleted && tokenizer.hasMoreTokens()) {
        Token nextToken = tokenizer.getToken();
        std::string key = nextToken.value;
        std::cout << key << std::endl;
        tokenizer.getToken();
        nextToken = tokenizer.getToken();
        switch (nextToken.type) {
        case TOKEN::STRING: {
            tokenizer.rollBackToken();
            (*keyObjectMap)[key] = parseString();
            break;
        }
        case TOKEN::ARRAY_OPEN: {
            (*keyObjectMap)[key] = parseList();
            break;
        }
        case TOKEN::NUMBER: {
            tokenizer.rollBackToken();
            (*keyObjectMap)[key] = parseNumber();
            break;
        }
        case TOKEN::CURLY_OPEN: {
            (*keyObjectMap)[key] = parseObject();
            break;
        }
        case TOKEN::BOOLEAN: {
            tokenizer.rollBackToken();
            (*keyObjectMap)[key] = parseBoolean();
            break;
        }
        case TOKEN::NULL_TYPE: {
            (*keyObjectMap)[key] = parseNull();
            break;
        }
        default:
            break;
        }
        nextToken = tokenizer.getToken();
        if (nextToken.type == TOKEN::CURLY_CLOSE) {
            hasCompleted = true;
        }
    }
    if (!hasCompleted) {
        throw std::logic_error("Unclosed object");
    }
    node->setObject(keyObjectMap);
    return node;
}

std::shared_ptr<JSON::JSONNode> JSONParser::parseString() {
    std::cout << "Parsing String" << std::endl;
    std::shared_ptr<JSON::JSONNode> node = std::make_shared<JSON::JSONNode>();
    Token token = tokenizer.getToken();
    std::string* sValue = new std::string(token.value);
    node->setString(sValue);
    return node;
}

std::shared_ptr<JSON::JSONNode> JSONParser::parseNumber() {
    std::cout << "Parsing Number" << std::endl;
    std::shared_ptr<JSON::JSONNode> node = std::make_shared<JSON::JSONNode>();
    Token nextToken = tokenizer.getToken();
    std::string value = nextToken.value;
    std::cout << value << std::endl;
    float fValue = std::stof(value);
    node->setNumber(fValue);
    return node;
}

std::shared_ptr<JSON::JSONNode> JSONParser::parseList() {
    std::cout << "Parsing List" << std::endl;
    std::shared_ptr<JSON::JSONNode> node = std::make_shared<JSON::JSONNode>();
    JSON::JSONList* list = new JSON::JSONList();
    bool hasCompleted = false;
    while (!hasCompleted && tokenizer.hasMoreTokens()) {
        Token nextToken = tokenizer.getToken();
        switch (nextToken.type) {
        case TOKEN::ARRAY_OPEN: {
            list->push_back(parseList());
            break;
        }
        case TOKEN::CURLY_OPEN: {
            list->push_back(parseObject());
            break;
        }
        case TOKEN::STRING: {
            tokenizer.rollBackToken();
            list->push_back(parseString());
            break;
        }
        case TOKEN::NUMBER: {
            tokenizer.rollBackToken();
            list->push_back(parseNumber());
            break;
        }
        case TOKEN::BOOLEAN: {
            tokenizer.rollBackToken();
            list->push_back(parseBoolean());
            break;
        }
        case TOKEN::NULL_TYPE: {
            list->push_back(parseNull());
            break;
        }
        case TOKEN::ARRAY_CLOSE: {
            hasCompleted = true;
            break;
        }
        default:
            break;
        }
        if (!hasCompleted) {
            nextToken = tokenizer.getToken();
            if (nextToken.type == TOKEN::ARRAY_CLOSE) {
                hasCompleted = true;
            }
        }
    }
    if (!hasCompleted) {
        throw std::logic_error("Unclosed list");
    }
    node->setList(list);
    return node;
}

std::shared_ptr<JSON::JSONNode> JSONParser::parseBoolean() {
    std::cout << "Parsing boolean" << std::endl;
    std::shared_ptr<JSON::JSONNode> node = std::make_shared<JSON::JSONNode>();
    Token nextToken = tokenizer.getToken();
    node->setBoolean(nextToken.value == "True" ? true : false);
    return node;
}

std::shared_ptr<JSON::JSONNode> JSONParser::parseNull() {
    std::cout << "Parsing null" << std::endl;
    std::shared_ptr<JSON::JSONNode> node = std::make_shared<JSON::JSONNode>();
    node->setNull();
    return node;
}