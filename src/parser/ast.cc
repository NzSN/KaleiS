#ifndef KALEIS_PARSER_AST_H_
#define KALEIS_PARSER_AST_H_

#include "ast_base.h"

namespace Kaleis {
namespace Parser {

class Specification : public Node {
public:
  explicit Specification(TSNode *ts_node) ;
};


} // Parser
} // Kaleis

#endif /* KALEIS_PARSER_AST_H_ */
