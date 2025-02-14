#ifndef KALEIS_AST_AST_GENERATOR_H_
#define KALEIS_AST_AST_GENERATOR_H_

#include <memory>
#include <map>
#include <string>
#include <optional>
#include <vector>

#include <nlohmann/json.hpp>

namespace Kaleis {
namespace AST {

namespace TreeSitter {

struct NodeInfo {
  std::string type;
  bool named;
};
struct ChildInfo {
  bool required;
  bool multiple;
  std::vector<NodeInfo> types;
};

class TreeSitterNode {
public:
  [[nodiscard]]
  std::string NodeType() const;

  [[nodiscard]]
  bool IsNamed() const;
private:
  NodeInfo info_;
};
class InternalNode : public TreeSitterNode {
public:
  [[nodiscard]]
  inline size_t NumOfFields() const {
    return fields.size();
  }

  [[nodiscard]]
  inline size_t NumOfChildren() const {
    return children.types.size();
  }

  [[nodiscard]]
  inline bool IsMultipleChildren() const {
    return children.multiple;
  }

  [[nodiscard]]
  inline bool IsRequiredChildren() const {
    return children.required;
  }

  [[nodiscard]]
  inline auto BeginOfFields() const {
    return fields.cbegin();
  }

  [[nodiscard]]
  inline auto EndOfFields() const {
    return fields.cend();
  }

  auto begin() {
    return children.types.begin();
  }

  auto end() {
    return children.types.end();
  }

  auto cbegin() const {
    return children.types.cbegin();
  }

  auto cend() const {
    return children.types.cend();
  }

private:
  std::map<std::string, ChildInfo> fields;
  ChildInfo children;
};
class Leaf : public TreeSitterNode {};

[[nodiscard]]
std::unique_ptr<TreeSitterNode>
BuildTreeSitterNodeFromJSON(nlohmann::json& source);

} // TreeSitter

struct ASTGeneratorTester;

class ASTGenerator {
public:
  void GenAST(std::string path, std::string opath);
private:
  friend ASTGeneratorTester;

  [[nodiscard]]
  std::optional<std::string> TransJSONToAST(std::string json_source) const;
};

} // AST
} // Kaleis

#endif /* KALEIS_AST_AST_GENERATOR_H_ */
