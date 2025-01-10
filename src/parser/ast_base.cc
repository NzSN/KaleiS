#include "src/base/assert.h"

#include "ast_base.h"
#include <cstddef>

namespace Kaleis {
namespace Parser {

/* Implementation of Node */
Node::Node(): underlying(NULL) {}

Node::Node(TSNode *ts_node): underlying{ts_node} {
  ASSERT_WITH_MSG(
    this->underlying != NULL,
    "Error: Initialized Kaleis::Parser::Node with Null pointer");
}

Node::~Node() {}

const TSNode* Node::GetUnderlying() const {
  ASSERT_WITH_MSG(
    this->underlying != NULL,
    "Error: Kaleis::Parser::Node::GetUnderlying() should \
     returned an valid pointer but it's Null pointer");
  return const_cast<const TSNode*>(this->underlying);
}

/* Implementation of Ast */
Ast::Ast(TSTree *tree): ts_tree(tree) {
  ASSERT_WITH_MSG(
    ts_tree != NULL,
    "Error Initialized Kaleis::Parser::Ast with Null pointer explicitly is not allowed");
}

Ast::~Ast() {
  ts_tree_delete(this->ts_tree);
}

} // Parser
} // Kaleis
