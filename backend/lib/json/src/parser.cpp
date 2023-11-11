#include "../include/parser.h"
#include <iostream>
#include <memory>
#include <stdexcept>

namespace json
{
Parser::Parser(const std::string filename)
    : tokenizer(filename)
{
}

Parser::~Parser()
{
}

void Parser::parse()
{
    std::string key = "";
    while (tokenizer.hasMoreTokens())
    {
        Token token;
        try
        {
            token = tokenizer.getToken();
            std::cout << token.toString() << std::endl;
            switch (token.type)
            {
            case TOKEN::CURLY_OPEN: {
                std::shared_ptr<json::JSONNode> parsedObject = parseObject();
                parsedObject->printNode(0);
                if (!root)
                    root = parsedObject;
                break;
            }
            case TOKEN::ARRAY_OPEN: {
                std::shared_ptr<json::JSONNode> parsedList = parseList();
                if (!root)
                    root = parsedList;
                break;
            }
            case TOKEN::STRING: {
                tokenizer.rollBackToken();
                std::shared_ptr<json::JSONNode> parsedString = parseString();
                if (!root)
                    root = parsedString;
                break;
            }
            case TOKEN::NUMBER: {
                tokenizer.rollBackToken();
                std::shared_ptr<json::JSONNode> parsedNumber = parseNumber();
                if (!root)
                    root = parsedNumber;
                break;
            }
            case TOKEN::BOOLEAN: {
                tokenizer.rollBackToken();
                std::shared_ptr<json::JSONNode> parsedBoolean = parseBoolean();
                if (!root)
                    root = parsedBoolean;
                break;
            }
            default:
                break;
            }
        }
        catch (std::logic_error* e)
        {
            std::cout << e->what() << std::endl;
        }
    }
}

std::shared_ptr<json::JSONNode> Parser::parseObject()
{
    std::cout << "Parsing object " << std::endl;
    std::shared_ptr<json::JSONNode> node = std::make_shared<json::JSONNode>();
    json::JSONObject* keyObjectMap       = new json::JSONObject();
    bool hasCompleted                    = false;
    while (!hasCompleted)
    {
        if (!tokenizer.hasMoreTokens())
        {
            throw std::logic_error("No more tokens");
        }

        Token nextToken = tokenizer.getToken();
        std::string key = nextToken.value;
        std::cout << key << std::endl;
        tokenizer.getToken();
        nextToken = tokenizer.getToken();
        std::shared_ptr<JSONNode> node;
        switch (nextToken.type)
        {
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
    }

    node->setObject(keyObjectMap);

    return node;
}

std::shared_ptr<json::JSONNode> Parser::parseString()
{
    std::cout << "Parsing String" << std::endl;
    std::shared_ptr<JSONNode> node = std::make_shared<JSONNode>();
    Token token                    = tokenizer.getToken();
    std::string* sValue            = new std::string(token.value);
    node->setString(sValue);

    return node;
}

std::shared_ptr<json::JSONNode> Parser::parseNumber()
{
    std::cout << "Parsing Number" << std::endl;
    std::shared_ptr<JSONNode> node = std::make_shared<JSONNode>();
    Token nextToken                = tokenizer.getToken();
    std::string value              = nextToken.value;
    std::cout << value << std::endl;
    float fValue = std::stof(value);
    node->setNumber(fValue);

    return node;
}

std::shared_ptr<json::JSONNode> Parser::parseList()
{
    std::cout << "Parsing List" << std::endl;
    std::shared_ptr<JSONNode> node = std::make_shared<JSONNode>();
    JSONList* list                 = new JSONList();
    bool hasCompleted              = false;
    while (!hasCompleted)
    {
        if (!tokenizer.hasMoreTokens())
            throw std::logic_error("No more tokens");

        Token nextToken = tokenizer.getToken();
        std::shared_ptr<JSONNode> node;
        switch (nextToken.type)
        {
        case TOKEN::ARRAY_OPEN: {
            node = parseList();
            break;
        }
        case TOKEN::CURLY_OPEN: {
            node = parseObject();
            break;
        }
        case TOKEN::STRING: {
            tokenizer.rollBackToken();
            node = parseString();
            break;
        }
        case TOKEN::NUMBER: {
            tokenizer.rollBackToken();
            node = parseNumber();
            break;
        }
        case TOKEN::BOOLEAN: {
            tokenizer.rollBackToken();
            node = parseBoolean();
            break;
        }
        case TOKEN::NULL_TYPE: {
            node = parseNull();
            break;
        }
        default:
            break;
        }

        list->push_back(node);
        nextToken = tokenizer.getToken();
        if (nextToken.type == TOKEN::ARRAY_CLOSE)
            hasCompleted = true;
    }

    node->setList(list);
    return node;
}

std::shared_ptr<json::JSONNode> Parser::parseBoolean()
{
    std::cout << "Parsing boolean" << std::endl;
    std::shared_ptr<JSONNode> node = std::make_shared<JSONNode>();
    Token nextToken                = tokenizer.getToken();
    node->setBoolean(nextToken.value == "True" ? true : false);

    return node;
}

std::shared_ptr<json::JSONNode> Parser::parseNull()
{
    std::cout << "Parsing null" << std::endl;
    std::shared_ptr<JSONNode> node = std::make_shared<JSONNode>();
    node->setNull();

    return node;
}
} // namespace json
