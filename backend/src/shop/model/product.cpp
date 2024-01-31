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

    Product::~Product()
    {
    }

    void Product::deserialize(std::shared_ptr<json::JSONNode> node)
    {
        auto root = node->returnObject();
        auto product = root->begin()->second->returnObject();
        for (auto i = product->begin(); i != product->end(); i++)
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
        auto root = std::make_shared<json::JSONNode>(json::JSONNode::Type::OBJECT);
        auto object = new json::JSONObject();

        ((*object)["id"] = std::make_shared<json::JSONNode>(json::JSONNode::Type::NUMBER))->setNumber(id);
        ((*object)["name"] = std::make_shared<json::JSONNode>(json::JSONNode::Type::STRING))->setString(&name);
        ((*object)["available"] = std::make_shared<json::JSONNode>(json::JSONNode::Type::BOOLEAN))->setBoolean(available);
        ((*object)["price"] = std::make_shared<json::JSONNode>(json::JSONNode::Type::NUMBER))->setNumber(price);
        root->setObject(object);

        return root;
    }
} // namespace model
} // namespace shop
