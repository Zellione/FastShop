#pragma once

#include "json_node.h"
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

      void parse();
      std::shared_ptr<json::JSONNode> parseObject();
      std::shared_ptr<json::JSONNode> parseString();
      std::shared_ptr<json::JSONNode> parseNumber();
      std::shared_ptr<json::JSONNode> parseList();
      std::shared_ptr<json::JSONNode> parseBoolean();
      std::shared_ptr<json::JSONNode> parseNull();
  private:
    std::fstream file;
    std::shared_ptr<json::JSONNode> root;
    std::unique_ptr<json::JSONNode> current;
    Tokenizer tokenizer;
};
} // namespace json
