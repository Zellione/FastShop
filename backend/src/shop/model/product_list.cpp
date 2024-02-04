#include "product_list.h"
#include <memory>

namespace shop
{
namespace model
{
    ProductList::ProductList()
        : products()
    {
    }

    ProductList::~ProductList()
    {
    }

    void ProductList::deserialize(std::shared_ptr<json::JSONNode> node)
    {
        auto root = node->returnObject();
        auto product = root->begin()->second->returnList();
        for (auto i = product->begin(); i != product->end(); i++)
        {
            products.push_back(Product());
            products.back().deserialize(*i);
        }
    }

    std::shared_ptr<json::JSONNode> ProductList::serialize()
    {
        auto root = std::make_shared<json::JSONNode>(json::JSONNode::Type::LIST);

        json::JSONList* list = new json::JSONList();
        for (auto i = products.begin(); i != products.end(); i++)
        {
            list->emplace_back(i->serialize());
        }

        root->setList(list);

        return root;
    }
} // namespace model
} // namespace shop
