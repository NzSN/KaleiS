#include "ast_base.h"

#include "tree_sitter/api.h"
#include <memory>

namespace Kaleis {
namespace AST {

using json = nlohmann::json;

Node::Node(TSNode* node): node_(node) {}


InternalNode::InternalNode(TSNode* node): Node(node) {}

void InternalNode::push_back(std::unique_ptr<Node>&& node) {
  children_.push_back(std::move(node));
}

void InternalNode::pop_back() {
  children_.pop_back();
}

Leaf::Leaf(TSNode* node, std::string& source):
  Node(node), source_(source), literal_{} {}
std::string Leaf::GetLiteral() {
  if (literal_.has_value()) {
    return literal_.value();
  } else {
    uint32_t start_byte = ts_node_start_byte(*node_),
      end_byte = ts_node_end_byte(*node_);

    literal_ = source_.substr(start_byte, end_byte - start_byte);
    return literal_.value();
  }
}

template<Context T>
AST<T>::AST(json& j): node_{}, source_{j.dump()} {}

namespace {

std::optional<TSNode> PreorderIterate(TSTreeCursor* cursor) {
  if (!ts_tree_cursor_goto_first_child(cursor)) {
    if (!ts_tree_cursor_goto_next_sibling(cursor)) {
      bool has_parent = false;
      while ((has_parent = ts_tree_cursor_goto_parent(cursor)) &&
             !ts_tree_cursor_goto_next_sibling(cursor)) {}

      if (!has_parent) {
        return std::nullopt;
      }
    }
  }

  return ts_tree_cursor_current_node(cursor);
}

}

template<Context T>
[[nodiscard]]
AST<T>::MaybeASTUniquePtr AST<T>::BuildAST(TSNode node, T& ctx) {
  TSTreeCursor cursor = ts_tree_cursor_new(node);


}

} // AST
} // Kaleis
