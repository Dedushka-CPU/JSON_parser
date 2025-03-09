#ifndef JSON_NODE_H
#define JSON_NODE_H

#include <map>
#include <memory>
#include <vector>
#include <string>

namespace JSON {
    class JSONNode;
    using JSONObject = std::map<std::string, std::shared_ptr<JSONNode>>;
    using JSONList = std::vector<std::shared_ptr<JSONNode>>;

    class JSONNode {
    private:
        enum class Type { OBJECT, LIST, STRING, NUMBER, BOOLEAN, NULL_TYPE };
        
        union Values {
            JSONObject* object;
            JSONList* list;
            std::string* s;
            float fValue;
            bool bValue;
            
            Values() {}
            ~Values() {}
        } values;

        Type type;

    public:
        JSONNode();
        explicit JSONNode(Type t);
        ~JSONNode();

        JSONObject& returnObject();
        JSONList& returnList();
        std::string& returnString();
        float returnFloat();
        bool returnBoolean();

        void setObject(JSONObject* object);
        void setString(std::string* s);
        void setNumber(float f);
        void setList(JSONList* list);
        void setBoolean(bool v);
        void setNull();

        std::string toString(int indentationLevel = 0) const;
        void printNode(int indentationLevel = 0) const;
    };
}

#endif