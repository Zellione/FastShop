#include "product.h"
#include <iostream>

namespace shop
{
namespace model
{
    Product::Product()
        : id(0),
          name(""),
          is_available(false)
    {
    }

    Product::~Product()
    {
    }

    void Product::deserialize(std::shared_ptr<json::JSONNode> node)
    {
        auto test = *node->returnObject();
        for (auto i = test.begin(); i != test.end(); i++)
        {
            std::cout << "Key: " << i->first << " Value: " << i->second << std::endl;
        }
    }
} // namespace model
} // namespace shop
