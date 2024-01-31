#pragma once

#include "json_node.h"
#include <memory>

namespace json
{
class Serializable
{
  public:
    Serializable()
    {
    }

    Serializable(const Serializable& other) = delete;

    virtual ~Serializable()
    {
    }

    virtual void deserialize(std::shared_ptr<json::JSONNode> node) = 0;
    virtual std::shared_ptr<json::JSONNode> serialize() = 0;
};
} // namespace json
