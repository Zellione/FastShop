#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace json
{
class JSONNode;
using JSONObject = std::map<std::string, std::shared_ptr<JSONNode>>;
using JSONList   = std::vector<std::shared_ptr<JSONNode>>;

class JSONNode
{
  public:
    enum class Type
    {
        OBJECT,
        LIST,
        STRING,
        NUMBER,
        BOOLEAN,
        NULL_TYPE
    };

  public:
    JSONNode();
    JSONNode(Type t);
    JSONNode(const JSONNode &other) = delete;
    ~JSONNode();

    JSONObject* returnObject() const;
    JSONList* returnList() const;
    std::string* returnString() const;
    float returnFloat() const;
    bool returnBoolean() const;

    void setObject(JSONObject* object);
    void setString(std::string* s);
    void setNumber(float f);
    void setList(JSONList* list);
    void setBoolean(bool b);
    void setNull();

    std::string toString(int indentationLevel);
    void printNode(int indentationLevel);

  private:
    union Values {
        JSONObject* object;
        JSONList* list;
        std::string* s;
        float fValue;
        bool bValue;
    } values;

    Type type;
};
} // namespace json
