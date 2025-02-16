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

RC_GTEST_FIXTURE_PROP(ASTGeneratorTester, LeafOnlyTransform, ()) {
  std::string source_json =
    "[{ \"type\": \"declaration\" }, { \"type\": \"statement\" }]";

  const auto ast = trans(source_json);

  /*
   * Expected Generated AST Node in CPP Type:
   *
   * class Declaration : public
   * class Statement   : public Leaf {};
   *
   * using CTOR = std::optional<std::unique_ptr<Node>>(TSNode, ASTContext&);
   * std::map<std::string, std::function<CTOR> context = {
   *   {"declaration", [](TSNode node, ASTContext& context) { ... } },
   *   {"statement"  , [](TSNode node, ASTContext& context) { ... } }
   * };
   *
   */
  RC_ASSERT(ast.has_value());
}

} // Kaleis::AST
