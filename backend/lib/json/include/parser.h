#pragma once

#include "json_node.h"
#include "serializable.h"
#include "tokenizer.h"
#include <fstream>
#include <memory>
#include <string>

namespace json
{
class Parser
{
  public:
      Parser(const std::string filename);
      Parser(const Parser &other) = delete;
      ~Parser();

      void parse(Serializable* obj);
      std::shared_ptr<JSONNode> parseObject();
      std::shared_ptr<JSONNode> parseString();
      std::shared_ptr<JSONNode> parseNumber();
      std::shared_ptr<JSONNode> parseList();
      std::shared_ptr<JSONNode> parseBoolean();
      std::shared_ptr<JSONNode> parseNull();
  private:
    std::fstream file;
    std::shared_ptr<JSONNode> root;
    std::unique_ptr<JSONNode> current;
    Tokenizer tokenizer;
};
} // namespace json
