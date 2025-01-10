#include <iostream>

#include "gtest/gtest.h"

#include <tree_sitter/api.h>
#include "bindings/c/tree-sitter-kaleis.h"

namespace Kaleis::Api {

TEST(Test, Basic) {
  TSParser *parser = ts_parser_new();
  ts_parser_set_language(parser, tree_sitter_kaleis());

  const char *source_code = "Plus(n :: Nat) :: Nat { return n + 1; }";
  TSTree *tree = ts_parser_parse_string(parser, NULL, source_code, strlen(source_code));

  ts_parser_delete(parser);

  TSNode root_node = ts_tree_root_node(tree);
  std::cout << ts_node_type(root_node) << std::endl;
}

} // Kaleis:Api
