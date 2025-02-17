#include "ast_base.h"

#include <memory>
#include <utility>

#include "tree_sitter/api.h"

namespace Kaleis {
namespace AST {

Node::Node(TSNode node, NodeType type): node_(node), type_(type) {}
Node::~Node() {}
bool Node::IsLeaf() const {
  return type_ == NodeType::LeafNode;
}

bool Node::IsInterior() const {
  return !IsLeaf();
}


InternalNode::InternalNode(TSNode node): Node(node, NodeType::InteriorNode) {}

std::string InternalNode::GetLiteral() {
  std::string literal{};
  for (auto& node : *this) {
    literal += node->GetLiteral();
  }

  return literal;
}

void InternalNode::push_back(std::unique_ptr<Node>&& node) {
  children_.push_back(std::move(node));
}

void InternalNode::pop_back() {
  children_.pop_back();
}

Leaf::Leaf(TSNode node, ASTContext& ctx):
  Node(node, NodeType::LeafNode), ctx_(ctx), literal_{} {}
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


} // AST
} // Kaleis
