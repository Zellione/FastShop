#pragma once

#include "json_node.h"

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
};
} // namespace json
