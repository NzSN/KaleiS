#ifndef KALEIS_PARSER_PARSER_H_
#define KALEIS_PARSER_PARSER_H_

#include <memory>
#include <string>
#include "tree_sitter/api.h"
#include "ast.h"

namespace Kaleis {
namespace Parser {

class Parser final {
public:
  Parser();
  ~Parser();

  [[nodiscard]]
  std::unique_ptr<Ast> Parse(std::string source);

private:
  TSParser *parser;
};

} // Parser
} // Kaleis

#endif /* KALEIS_PARSER_PARSER_H_ */
