#include "gtest/gtest.h"
#include "rapidcheck/gtest.h"
#include "ast_generator.h"

namespace Kaleis::AST {

struct ASTGeneratorTester: public ::testing::Test {

  std::optional<std::string>
  trans(std::string source_json) {
    return g.TransJSONToAST(source_json);
  }

  ASTGenerator g;
};


RC_GTEST_FIXTURE_PROP(ASTGeneratorTester, JSONTransform, ()) {
  std::string source_json =
    "[{ \"type\": \"declaration\" }, { \"type\": \"statement\" }]";

  const auto ast = trans(source_json);
  RC_ASSERT(ast.has_value());
}

} // Kaleis::AST
