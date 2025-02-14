#ifndef KALEIS_AST_AST_BASE_H_
#define KALEIS_AST_AST_BASE_H_

#include "tree_sitter/api.h"

namespace Kaleis {
namespace AST {

struct Node {
  Node(TSNode* node_): node(node_) {}
  const TSNode* node;
};

struct InternalNode: public Node {};
struct Leaf : public Node {};

} // AST
} // Kaleis

#endif /* KALEIS_AST_AST_BASE_H_ */
