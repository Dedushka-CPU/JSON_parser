#ifndef PARSERJSON_PARSER_H
#define PARSERJSON_PARSER_H

#include "Tokenizer.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

class JSON_Node;

using JSONObject = std::map<std::string,std::shared_ptr<JSON_Node>>;
using JSONList = std::vector<std::shared_ptr<JSON_Node>>;

class JSON_Node {
    enum class Type {
        OBJECT,
        LIST,
        STRING,
        NUMBER,
        BOOLEAN,
        NULL_TYPE
    };
    union Values {
        JSONObject* object;
        JSONList* list;
        std::string* s;
        float fValue;
        bool bValue;
    } value ;
    Type type;
    auto returnObject() {
        if(type==Type::OBJECT) {
            return *value.object;
        }
        throw std::logic_error("Wrong return");
    }
    auto returnList() {
        if(type==Type::LIST) {
            return *value.list;
        }
        throw std::logic_error("Wrong return");
    }

    auto returnString() {
        if(type==Type::STRING) {
            return *value.list;
        }
        throw std::logic_error("Wrong return");
    }
    auto returnFloat() {
        if(type==Type::NUMBER) {
            return value.fValue;
        }
        throw std::logic_error("Wrong return");
    }
    auto returnBool() {
        if(type==Type::BOOLEAN) {
            return value.bValue;
        }
        throw std::logic_error("Wrong return");
    }
    void setObject(JSONObject* object) {
        this->value.object=object;
        type=Type::OBJECT;
    }
    void setList (JSONList* list) {
        this->value.list=list;
        type=Type::LIST;
    }
    void setString (std::string* str) {
        this->value.s=str;
        type=Type::STRING;
    }
    void setFloat(float fValue) {
        this->value.fValue=fValue;
        type=Type::NUMBER;
    }
    void setBool(bool bValue) {
        this->value.bValue=bValue;
        type=Type::BOOLEAN;
    }
};

class JSONParser{
private:
    std::fstream file;
    std::shared_ptr<JSON_Node> root;
    std::unique_ptr<JSON_Node> current;
    Tokenizer tokenizer;
public:
    JSONParser(const std::string filename):tokenizer(filename){};
    void parse();
    std::shared_ptr<JSON_Node> parseOject();
    std::shared_ptr<JSON_Node> parseString();
    std::shared_ptr<JSON_Node> parseNumber();
    std::shared_ptr<JSON_Node> parseList();
    std::shared_ptr<JSON_Node> parseBoolean();
    std::shared_ptr<JSON_Node> parseNull();

}

#endif //PARSERJSON_PARSER_H