#ifndef KALEIS_AST_AST_BASE_H_
#define KALEIS_AST_AST_BASE_H_

#include <optional>
#include <concepts>
#include <string>
#include <memory>
#include <vector>

#include "tree_sitter/api.h"

#include "src/base/check.h"
#include "src/base/assert.h"

namespace Kaleis {
namespace AST {

struct ASTContext {
  std::string source;
};


enum NodeType {
  LeafNode,
  InteriorNode,
};

class Node {
public:
  Node(TSNode node, NodeType type);
  virtual ~Node();

  bool IsLeaf() const;
  bool IsInterior() const;

  virtual std::string GetLiteral() = 0;
protected:
  const TSNode node_;
  const NodeType type_;
};

class InternalNode : public Node {
public:
  InternalNode(TSNode node);
  ~InternalNode() {}

  void push_back(std::unique_ptr<Node>&& node);
  void pop_back();

  Node* front() const;
  Node* back() const;

  auto begin()        { return children_.begin(); }
  auto end()          { return children_.end(); }
  auto cbegin() const { return children_.cbegin(); }
  auto cend() const   { return children_.cend(); }

  std::string GetLiteral() override;

private:
  std::vector<std::unique_ptr<Node>> children_;
};
class Leaf : public Node {
public:
  Leaf(TSNode node, ASTContext& ctx);
  ~Leaf() {}
  std::string GetLiteral() override;
private:
  ASTContext& ctx_;
  std::optional<std::string> literal_;
};

using MaybeNodeUniquePtr = std::optional<std::unique_ptr<Node>>;
template<typename T>
concept Context =
  requires(T ctx, TSNode node, ASTContext& context) {
    { ctx(node, context) } -> std::convertible_to<MaybeNodeUniquePtr>;
  };

template<Context T>
class AST {
public:
  using MaybeASTUniquePtr = std::optional<std::unique_ptr<AST>>;
  AST(std::string source): node_{}, context_{source} {}

  [[nodiscard]]
  static MaybeASTUniquePtr BuildAST(std::string source, TSTree* tree, T& ctx) {

    std::unique_ptr<AST<T>> ast = std::make_unique<AST<T>>(source);

    TSNode root_ts_node = ts_tree_root_node(tree);
    MaybeNodeUniquePtr root_node = MapTSNodeToNode(root_ts_node, ast.get(), ctx);
    if (!root_node.has_value()) {
      return std::nullopt;
    }

    ast->node_ = std::move(root_node.value());

    return ast;
  }

  std::string ToString() {
    return node_->GetLiteral();
  }

private:
  static std::optional<TSNode> PreorderIterate(TSTreeCursor* cursor, TSNode root) {
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

  [[nodiscard]]
  static MaybeNodeUniquePtr MapTSNodeToNode(TSNode node, AST<T>* ast, T& ctx) {
    ASSERT(ast != nullptr);

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
      CHECK(current_ast_node->IsInterior());
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
      CHECK(current_ast_node->IsLeaf());
    }

    return current_ast_node;
  }

  std::unique_ptr<Node> node_;

  ASTContext context_;
  TSTree* tree_;
};

} // AST
} // Kaleis

#endif /* KALEIS_AST_AST_BASE_H_ */
