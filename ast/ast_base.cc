#include "ast_base.h"

#include <functional>
#include <memory>
#include <map>
#include <utility>

#include "tree_sitter/api.h"
#include "src/base/check.h"

namespace Kaleis {
namespace AST {

Node::Node(TSNode node): node_(node) {}


InternalNode::InternalNode(TSNode node): Node(node) {}

void InternalNode::push_back(std::unique_ptr<Node>&& node) {
  children_.push_back(std::move(node));
}

void InternalNode::pop_back() {
  children_.pop_back();
}

Leaf::Leaf(TSNode node, ASTContext& ctx):
  Node(node), ctx_(ctx), literal_{} {}
std::string Leaf::GetLiteral() {
  if (literal_.has_value()) {
    return literal_.value();
  } else {
    uint32_t start_byte = ts_node_start_byte(node_),
      end_byte = ts_node_end_byte(node_);

    literal_ = ctx_.source.substr(start_byte, end_byte - start_byte);
    return literal_.value();
  }
}

template<Context T>
AST<T>::AST(std::string source): node_{}, context_{source} {}

namespace {

std::optional<TSNode> PreorderIterate(TSTreeCursor* cursor, TSNode root) {
  if (!ts_tree_cursor_goto_first_child(cursor)) {
    if (!ts_tree_cursor_goto_next_sibling(cursor)) {
      if (ts_node_eq(ts_tree_cursor_current_node(cursor), root)) {
        return std::nullopt;
      }
      while (true) {
        ts_tree_cursor_goto_parent(cursor);
        if (ts_node_eq(ts_tree_cursor_current_node(cursor), root)) {
          return std::nullopt;
        }
        if (ts_tree_cursor_goto_next_sibling(cursor)) {
          break;
        }
      }
    }
  }

  return ts_tree_cursor_current_node(cursor);
}

template<typename T>
[[nodiscard]]
MaybeNodeUniquePtr MapTSNodeToNode(TSNode node, AST<T>* ast, T& ctx) {

  TSNode root = node;
  std::optional<TSNode> current = root;
  TSTreeCursor cursor = ts_tree_cursor_new(node);

  /* Build Current AST node */
  MaybeNodeUniquePtr current_ast_node_maybe = ctx(current.value(), ast->context_);
  if (!current_ast_node_maybe.has_value()) {
    return std::nullopt;
  }

  std::unique_ptr<Node> current_ast_node =
    std::move(current_ast_node_maybe.value());
  if (ts_node_child_count(current.value()) > 0) { // InternalNode
    CHECK(typeid(InternalNode) == typeid(*current_ast_node));

    InternalNode* internal_node =
      static_cast<InternalNode*>(current_ast_node.get());
    std::optional<TSNode> child = PreorderIterate(&cursor, root);

    while (child.has_value()) {
      if (!ts_node_eq(ts_node_parent(child.value()), current.value())) {
        break;
      }

      MaybeNodeUniquePtr child_ast_node = MapTSNodeToNode(child.value(), ast, ctx);
      CHECK(child_ast_node.has_value());
      internal_node->push_back(std::move(child_ast_node.value()));

      child = PreorderIterate(&cursor, root);
    }
  } else { // Leaf
    /* Do nothing */
  }

  return current_ast_node;
}

}

template<Context T>
[[nodiscard]]
AST<T>::MaybeASTUniquePtr AST<T>::BuildAST(std::string source, TSTree* tree, T& ctx) {

  std::unique_ptr<AST<T>> ast = std::make_unique<AST<T>>(source);

  TSNode root_ts_node = ts_tree_root_node(tree);
  MaybeNodeUniquePtr root_node = MapTSNodeToNode<T>(root_ts_node, ast, ctx);
  if (!root_node.has_value()) {
    return std::nullopt;
  }

  ast->node_ = std::move(root_node.value());

  return ast;
}

} // AST
} // Kaleis
