#include "../include/json_node.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace json
{
JSONNode::JSONNode()
{
}

JSONNode::JSONNode(Type t)
    : type(t)
{
}

JSONNode::~JSONNode()
{
}

JSONObject* JSONNode::returnObject() const
{
    if (type == Type::OBJECT)
        return values.object;

    throw std::logic_error("Improper return");
}

JSONList* JSONNode::returnList() const
{
    if (type == Type::LIST)
        return values.list;

    throw std::logic_error("Improper return");
}

std::string* JSONNode::returnString() const
{
    if (type == Type::STRING)
        return values.s;

    throw std::logic_error("Improper return");
}

float JSONNode::returnFloat() const
{
    if (type == Type::NUMBER)
        return values.fValue;

    throw std::logic_error("Improper return");
}

bool JSONNode::returnBoolean() const
{
    if (type == Type::BOOLEAN)
        return values.fValue;

    throw std::logic_error("Improper return");
}

void JSONNode::setObject(JSONObject* object)
{
    values.object = object;
    type          = Type::OBJECT;
}

void JSONNode::setString(std::string* s)
{
    values.s = s;
    type     = Type::STRING;
}

void JSONNode::setNumber(float f)
{
    values.fValue = f;
    type          = Type::NUMBER;
}

void JSONNode::setList(JSONList* list)
{
    values.list = list;
    type        = Type::LIST;
}

void JSONNode::setBoolean(bool b)
{
    values.bValue = b;
    type          = Type::BOOLEAN;
}

void JSONNode::setNull()
{
    type = Type::NULL_TYPE;
}

std::string JSONNode::toString(int indentationLevel)
{
    std::string spaceString = std::string(indentationLevel, ' ');
    std::stringstream ss;
    switch (type)
    {
    case Type::STRING: {
        ss << spaceString << *values.s;
        break;
    }
    case Type::NUMBER: {
        ss << spaceString << values.fValue;
        break;
    }
    case Type::BOOLEAN: {
        ss << spaceString << (values.bValue ? "true" : "false");
        break;
    }
    case Type::NULL_TYPE: {
        ss << spaceString << "null";
        break;
    }
    case Type::LIST: {
        ss << "[";
        unsigned int index = 0;
        for (auto node : (*values.list))
        {
            ss << node->toString(indentationLevel + 1);
            if (index < (*values.list).size() - 1)
                ss << spaceString << ", ";

            index++;
        }
        ss << spaceString << "]\n";
        break;
    }
    case Type::OBJECT: {
        ss << "{\n";
        for (JSONObject::iterator i = (*values.object).begin(); i != (*values.object).end(); i++)
        {
            ss << spaceString << i->first << ": ";
            ss << i->second->toString(indentationLevel + 1);
            JSONObject::iterator next = i;
            next++;
            if (next != (*values.object).end())
                ss << spaceString << ",";
            ss << spaceString + "\n";
        }
        ss << "}\n";
        break;
    }
    }

    ss << "}\n";

    return ss.str();
}

void JSONNode::printNode(int indentationLevel)
{
    std::cout << toString(indentationLevel);
}
} // namespace json
