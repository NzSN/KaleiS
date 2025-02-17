#include <iostream>
#include <algorithm>
#include <optional>

#include "ast_generator.h"

using json = nlohmann::json;

namespace Kaleis {
namespace AST {

namespace {

std::string TransStep(const json& item) {

}

}


std::optional<std::string>
ASTGenerator::TransJSONToAST(std::string json_source) const {
  json obj = json::parse(json_source);

  // Trans json objects to Typescript types
  std::for_each(obj.cbegin(), obj.cend(), TransStep);

  // Generate Parser that use above types to describe AST.


  return std::nullopt;
}

} // AST
} // Kaleis
