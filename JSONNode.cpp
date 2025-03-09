#include "JSONNode.h"
#include <stdexcept>
#include <iostream>

namespace JSON {
    JSONNode::JSONNode() : type(Type::NULL_TYPE) {
        values.bValue = false;
    }

    JSONNode::JSONNode(Type t) : type(t) {
        switch (t) {
            case Type::OBJECT: values.object = nullptr; break;
            case Type::LIST: values.list = nullptr; break;
            case Type::STRING: values.s = nullptr; break;
            case Type::NUMBER: values.fValue = 0.0f; break;
            case Type::BOOLEAN: values.bValue = false; break;
            case Type::NULL_TYPE: break;
        }
    }

    JSONNode::~JSONNode() {
        switch (type) {
            case Type::OBJECT: delete values.object; break;
            case Type::LIST: delete values.list; break;
            case Type::STRING: delete values.s; break;
            default: break;
        }
    }

    JSONObject& JSONNode::returnObject() {
        if (type == Type::OBJECT) {
            return *values.object;
        }
        throw std::logic_error("Type is not OBJECT");
    }

    JSONList& JSONNode::returnList() {
        if (type == Type::LIST) {
            return *values.list;
        }
        throw std::logic_error("Type is not LIST");
    }

    std::string& JSONNode::returnString() {
        if (type == Type::STRING) {
            return *values.s;
        }
        throw std::logic_error("Type is not STRING");
    }

    float JSONNode::returnFloat() {
        if (type == Type::NUMBER) {
            return values.fValue;
        }
        throw std::logic_error("Type is not NUMBER");
    }

    bool JSONNode::returnBoolean() {
        if (type == Type::BOOLEAN) {
            return values.bValue;
        }
        throw std::logic_error("Type is not BOOLEAN");
    }

    void JSONNode::setObject(JSONObject* object) {
        if (type == Type::OBJECT) delete values.object;
        values.object = object;
        type = Type::OBJECT;
    }

    void JSONNode::setString(std::string* s) {
        if (type == Type::STRING) delete values.s;
        values.s = s;
        type = Type::STRING;
    }

    void JSONNode::setNumber(float f) {
        values.fValue = f;
        type = Type::NUMBER;
    }

    void JSONNode::setList(JSONList* list) {
        if (type == Type::LIST) delete values.list;
        values.list = list;
        type = Type::LIST;
    }

    void JSONNode::setBoolean(bool v) {
        values.bValue = v;
        type = Type::BOOLEAN;
    }

    void JSONNode::setNull() {
        type = Type::NULL_TYPE;
    }

    std::string JSONNode::toString(int indentationLevel) const {
        std::string spaceString(indentationLevel, ' ');
        std::string outputString;

        switch (type) {
            case Type::STRING:
                outputString += spaceString + "\"" + *values.s + "\"";
                break;
            case Type::NUMBER:
                outputString += spaceString + std::to_string(values.fValue);
                break;
            case Type::BOOLEAN:
                outputString += spaceString + (values.bValue ? "true" : "false");
                break;
            case Type::NULL_TYPE:
                outputString += spaceString + "null";
                break;
            case Type::LIST: {
                outputString += spaceString + "[\n";
                for (size_t i = 0; i < values.list->size(); ++i) {
                    outputString += (*values.list)[i]->toString(indentationLevel + 2);
                    if (i < values.list->size() - 1) {
                        outputString += ",\n";
                    }
                }
                outputString += "\n" + spaceString + "]";
                break;
            }
            case Type::OBJECT: {
                outputString += spaceString + "{\n";
                size_t i = 0;
                for (const auto& [key, value] : *values.object) {
                    outputString += spaceString + "  \"" + key + "\": " + 
                                  value->toString(indentationLevel + 2);
                    if (i < values.object->size() - 1) {
                        outputString += ",\n";
                    }
                    i++;
                }
                outputString += "\n" + spaceString + "}";
                break;
            }
        }
        return outputString;
    }

    void JSONNode::printNode(int indentationLevel) const {
        std::cout << toString(indentationLevel) << std::endl;
    }
}