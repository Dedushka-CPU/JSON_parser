#include "parser.h"

void JSONParser::parse(){
    std::string key="";
    while(tokenizer.hasMoreTokens()){
        Token token;
        std::cout<<token.toString()<<"\n";
        switch (token.type)
        {
            case TOKEN::CURLY_OPEN:
                std::shared_ptr<JSON::JSON_Node> parseObject();
                parseObject->printNode(0);
                if(!root){
                    root=parseObject;
                } 
                break;
            case TOKEN::ARRAY_OPEN
                std::shared_ptr<JSON::JSON_Node> parseOject();
                if(!root){
                    root=parseObject;
                } 
                break;
            case TOKEN::NUMBER:
                tokenizer.roolBackToken();
                std::shared_ptr<JSON::JSON_Node> parsedNumber=parseNumber();
                if(!root){
                    root=parsedNumber;
                } 
                break;
            case TOKEN::STRING:
                tokenizer.roolBackToken();
                std::shared_ptr<JSON::JSON_Node> parseString=parseString();
                if(!root){
                    root=parseString;
                } 
                break; 
            case TOKEN::BOOLEAN:
                tokenizer.rollBackToken();
                std::shared_ptr<JSON::JSON_Node> parseBoolean=parseBoolean();
            default:
                break;
        }
        
    }
}