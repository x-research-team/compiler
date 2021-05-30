#pragma once

#include <memory>
#include <string>

using namespace std;

/**
 * @brief INode is a interface of AST node
 */
class INode {
public:
  using expression_t = shared_ptr<INode>;
  using statement_t = shared_ptr<INode>;
  /**
   * @brief Return reconstructed source code from constructed AST
   *
   * @return string Pure source code
   */
  virtual string source() const = 0;
};
