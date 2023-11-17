#pragma once

#include "../../../lib/json/include/serializable.h"
#include <string>

namespace shop
{
namespace model
{
    class Product : public json::Serializable
    {
      public:
        Product();
        Product(const Product& other) = delete;
        ~Product();

        void deserialize(std::shared_ptr<json::JSONNode> node) override;
      private:
        int id;
        std::string name;
        bool available;
        float price;
    };
} // namespace model
} // namespace shop
