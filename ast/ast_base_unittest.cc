#include "gtest/gtest.h"
#include "rapidcheck/gtest.h"

#include <functional>
#include <map>
#include <memory>

#include "tree_sitter/api.h"
#include "bindings/c/tree-sitter-typescript.h"

#include "ast_base.h"

namespace Kaleis {
namespace AST {


// InternalNodes
struct Program : public InternalNode {
  Program(TSNode node): InternalNode(node) {}
};
struct Variable_declaration : public InternalNode {
  Variable_declaration(TSNode node): InternalNode(node) {}
};
struct Variable_declarator : public InternalNode {
  Variable_declarator(TSNode node): InternalNode(node) {}
};

// Leaf
struct Var : public Leaf {
  Var(TSNode node, ASTContext& ctx):
    Leaf(node, ctx) {}
};
struct Identifier : public Leaf {
  Identifier(TSNode node, ASTContext& ctx):
    Leaf(node, ctx) {}
};
struct EqualOP : public Leaf {
  EqualOP(TSNode node, ASTContext& ctx):
    Leaf(node, ctx) {}
};
struct Number : public Leaf {
  Number(TSNode node, ASTContext& ctx):
    Leaf(node, ctx) {}
};


struct ASTBaseTester : public ::testing::Test {
  TSTree* GetTSTree(std::string source) {
    TSParser* parser = ts_parser_new();

    ts_parser_set_language(parser, tree_sitter_typescript());
    return ts_parser_parse_string(parser, NULL, source.c_str(), source.size());

  }

  using Context =
    std::function<MaybeNodeUniquePtr(TSNode, ASTContext&)>;
};


RC_GTEST_FIXTURE_PROP(ASTBaseTester, Basics, ()) {
  std::string source = "var a = 4;";
  TSTree* tree = GetTSTree(source);

  Context ctx = [](TSNode node, ASTContext& ctx) -> MaybeNodeUniquePtr {
    if (std::string(ts_node_type(node)) == "program") {
      return std::make_unique<Program>(node);
    } else if (std::string(ts_node_type(node)) == "variable_declaration") {
      return std::make_unique<Variable_declaration>(node);
    } else if (std::string(ts_node_type(node)) == "var") {
      return std::make_unique<Var>(node, ctx);
    } else if (std::string(ts_node_type(node)) == "variable_declarator") {
      return std::make_unique<Variable_declarator>(node);
    } else if (std::string(ts_node_type(node)) == "identifier") {
      return std::make_unique<Identifier>(node,ctx);
    } else if (std::string(ts_node_type(node)) == "=") {
      return std::make_unique<EqualOP>(node,ctx);
    } else if (std::string(ts_node_type(node)) == "number") {
      return std::make_unique<Number>(node,ctx);
    }
    return std::nullopt;
  };

  AST<Context>::MaybeASTUniquePtr ast =
    AST<Context>::BuildAST(source, tree, ctx);

  source.erase(std::remove(source.begin(), source.end(), ' '), source.end());
  source.erase(std::remove(source.begin(), source.end(), ';'), source.end());
  RC_ASSERT(ast.value()->ToString() == source);
}


} // AST
} // Kaleis
