#ifndef KALEIS_AST_AST_GENERATOR_H_
#define KALEIS_AST_AST_GENERATOR_H_

#include <string>
#include <optional>

#include <nlohmann/json.hpp>

namespace Kaleis {
namespace AST {


struct ASTGeneratorTester;

class ASTGenerator {
public:
  void GenAST(std::string path, std::string opath) const;
private:
  friend ASTGeneratorTester;

  std::optional<std::string> TransJSONToAST(std::string json_source) const;
};

} // AST
} // Kaleis

#endif /* KALEIS_AST_AST_GENERATOR_H_ */
