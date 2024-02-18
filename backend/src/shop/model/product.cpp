#include "product.h"
#include <memory>

namespace shop
{
namespace model
{
    Product::Product()
        : id(0),
          name(""),
          available(false),
          price(0.00)
    {
    }

    Product::Product(const Product& other)
    {
        id        = other.id;
        name      = std::string(other.name);
        available = other.available;
        price     = other.price;
    }

    Product::~Product()
    {
    }

    void Product::deserialize(std::shared_ptr<json::JSONNode> node)
    {
        auto root = node->returnObject();
        for (auto i = root->begin(); i != root->end(); i++)
        {
            if (i->first.compare("id") == 0)
            {
                id = (int)i->second->returnFloat();
                continue;
            }

            if (i->first.compare("name") == 0)
            {
                name = i->second->returnString();
                continue;
            }

            if (i->first.compare("available") == 0)
            {
                available = i->second->returnBoolean();
                continue;
            }

            if (i->first.compare("price") == 0)
            {
                price = i->second->returnFloat();
                continue;
            }
        }
    }

    std::shared_ptr<json::JSONNode> Product::serialize()
    {
        auto root   = std::make_shared<json::JSONNode>(json::JSONNode::Type::OBJECT);
        auto object = new json::JSONObject();

        ((*object)["id"] = std::make_shared<json::JSONNode>(json::JSONNode::Type::NUMBER))->setNumber(id);
        ((*object)["name"] = std::make_shared<json::JSONNode>(json::JSONNode::Type::STRING))
            ->setString(new std::string(name));
        ((*object)["available"] = std::make_shared<json::JSONNode>(json::JSONNode::Type::BOOLEAN))
            ->setBoolean(available);
        ((*object)["price"] = std::make_shared<json::JSONNode>(json::JSONNode::Type::NUMBER))->setNumber(price);
        root->setObject(object);

        return root;
    }

    std::string Product::createTable()
    {
        return "CREATE TABLE PRODUCT ("
               "ID INT PRIMARY KEY   NOT NULL, "
               "NAME           TEXT  NOT NULL, "
               "AVAILABLE      INT   NOT NULL, "
               "PRICE          REAL  NOT NULL );";
    }

    std::string Product::tableName()
    {
        return "product";
    }
} // namespace model
} // namespace shop
