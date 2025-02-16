#ifndef KALEIS_AST_AST_BASE_H_
#define KALEIS_AST_AST_BASE_H_

#include <optional>
#include <concepts>
#include <string>
#include <memory>
#include <vector>

#include "tree_sitter/api.h"

namespace Kaleis {
namespace AST {

struct ASTContext {
  std::string source;
};

class Node {
public:
  Node(TSNode node);
protected:
  const TSNode node_;
};

class InternalNode: public Node {
public:
  InternalNode(TSNode node);

  void push_back(std::unique_ptr<Node>&& node);
  void pop_back();

  Node* front() const;
  Node* back() const;

  auto begin()        { return children_.begin(); }
  auto end()          { return children_.end(); }
  auto cbegin() const { return children_.cbegin(); }
  auto cend() const   { return children_.cend(); }

private:
  std::vector<std::unique_ptr<Node>> children_;
};
class Leaf : public Node {
public:
  Leaf(TSNode node, ASTContext& ctx);
  std::string GetLiteral();
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

  [[nodiscard]]
  static MaybeASTUniquePtr BuildAST(std::string source, TSTree* node, T& ctx);
private:
  AST(std::string source);

  std::unique_ptr<Node> node_;

  ASTContext context_;
  TSTree* tree_;
};

} // AST
} // Kaleis

#endif /* KALEIS_AST_AST_BASE_H_ */
