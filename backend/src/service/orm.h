#pragma once

#include <string>
namespace service
{
class ORM
{
public:
    ORM()
    {
    }

    ORM(const ORM &other) = delete;

    virtual ~ORM()
    {
    }


    virtual std::string createTable() = 0;
    virtual std::string tableName() = 0;
    virtual bool save() = 0;
    virtual bool remove() = 0;
};
}
