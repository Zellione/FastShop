#include "product.h"
#include <iostream>

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
} // namespace model
} // namespace shop
