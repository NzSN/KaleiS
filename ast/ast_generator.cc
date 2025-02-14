#include <iostream>
#include <algorithm>
#include <optional>

#include "ast_generator.h"

using json = nlohmann::json;

namespace Kaleis {
namespace AST {

[[nodiscard]]
std::optional<std::string>
ASTGenerator::TransJSONToAST(std::string json_source) const {
  json obj = json::parse(json_source);

  std::for_each(obj.cbegin(), obj.cend(),
                [](const json& item) {
                  std::cout << item.dump() << std::endl;
                });

  return std::nullopt;
}

} // AST
} // Kaleis
