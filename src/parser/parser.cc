                                                \
#include "parser.h"

#include "src/base/assert.h"

#include "tree_sitter/api.h"
#include "bindings/c/tree-sitter-typescript.h"

namespace Kaleis {
namespace Parser {

Parser::Parser(): parser(ts_parser_new()) {
  ASSERT_WITH_MSG(
    this->parser != NULL,
    "Failed to create tree-sitter parser");

  [[maybe_unused]]
  auto rv = ts_parser_set_language(this->parser, tree_sitter_typescript());
  assert(rv);
}

Parser::~Parser() {
  if (this->parser) {
    ts_parser_delete(this->parser);
  }
}

std::unique_ptr<Ast> Parser::Parse(std::string source) {
  TSTree *tree = ts_parser_parse_string(
    this->parser, NULL, source.c_str(), source.size());

  return std::make_unique<Ast>(tree);
}

} // Parser
} // Kaleis
