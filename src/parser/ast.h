#ifndef KALEIS_PARSER_AST_H_
#define KALEIS_PARSER_AST_H_

#include <vector>

#include "ast_base.h"

namespace Kaleis {
namespace Parser {

class GlobalFunctionDecl : public Node {
public:
  explicit GlobalFunctionDecl(): Node() {}
  explicit GlobalFunctionDecl(TSNode *ts_node):
    Node(ts_node) {}
};
class StructDecl : public Node {
public:
  explicit StructDecl(): Node() {}
  explicit StructDecl(TSNode *ts_node):
    Node(ts_node) {}
};

class GlobalDecl : public Node {
public:
  explicit GlobalDecl(TSNode *ts_node):
    Node(ts_node) {}

private:
  GlobalFunctionDecl global_function_deccl;
  StructDecl struct_decl;
};

class Specification : public Node {
public:
  explicit Specification(TSNode *ts_node):
    Node(ts_node) {}

private:
  std::vector<GlobalDecl> global_decls;
};

} // Parser
} // Kaleis

#endif /* KALEIS_PARSER_AST_H_ */
