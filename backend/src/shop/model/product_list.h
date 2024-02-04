#pragma once

#include "../../../lib/json/include/serializable.h"
#include "product.h"
#include <string>
#include <vector>

namespace shop
{
namespace model
{
    class ProductList : public json::Serializable
    {
      public:
        ProductList();
        ProductList(const ProductList& other) = delete;
        ~ProductList();

        void deserialize(std::shared_ptr<json::JSONNode> node) override;
        std::shared_ptr<json::JSONNode> serialize() override;
      private:
        std::vector<Product> products;
    };
} // namespace model
} // namespace shop
