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

AST::AST(json& j): node_{}, source_{j.dump()} {}

void AST::SetupRootNode(std::unique_ptr<Node>&& root) {
  node_ = std::move(root);
}

} // AST
} // Kaleis
