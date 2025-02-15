#ifndef KALEIS_AST_AST_BASE_H_
#define KALEIS_AST_AST_BASE_H_

#include <string>

#include "tree_sitter/api.h"
#include "nlohmann/json.hpp"

namespace Kaleis {
namespace AST {

class Node {
public:
  Node(TSNode* node);
protected:
  const TSNode* node_;
};

class InternalNode: public Node {
public:
  InternalNode(TSNode* node);

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
  Leaf(TSNode* node, std::string& source);
  std::string GetLiteral();
private:
  std::string& source_;
  std::optional<std::string> literal_;
};

class AST {
public:
  AST(nlohmann::json& json);
protected:
  void SetupRootNode(std::unique_ptr<Node>&& root);
private:
  std::unique_ptr<Node> node_;
  std::string source_;
};

} // AST
} // Kaleis

#endif /* KALEIS_AST_AST_BASE_H_ */
