#pragma once

#include "../../../lib/json/include/serializable.h"
#include "../../service/orm.h"
#include <string>

namespace shop
{
namespace model
{
    class Product : public json::Serializable, public service::ORM
    {
      public:
        Product();
        Product(const Product& other);
        ~Product();

        void deserialize(std::shared_ptr<json::JSONNode> node) override;
        std::shared_ptr<json::JSONNode> serialize() override;
        std::string createTable() override;
        std::string tableName() override;

      private:
        int id;
        std::string name;
        bool available;
        float price;
    };
} // namespace model
} // namespace shop
