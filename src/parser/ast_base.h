#ifndef KALEIS_PARSER_AST_BASE_H_
#define KALEIS_PARSER_AST_BASE_H_

#include "tree_sitter/api.h"
#include <cassert>

namespace Kaleis {
namespace Parser {


template<typename x>
struct Functor {

};

class Node {
public:
  explicit Node();
  explicit Node(TSNode *ts_node);
  virtual ~Node();

  const TSNode* GetUnderlying() const;

private:
  TSNode *underlying;
};

class Ast final {
public:
  Ast(TSTree *tree);
  ~Ast();

private:
  TSTree *ts_tree;
};

} // Parser
} // Kaleis

#endif /* KALEIS_PARSER_AST_BASE_H_ */
