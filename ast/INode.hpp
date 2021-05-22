#pragma once

#include <string>

using namespace std;

/**
 * @brief INode is a interface of AST node
 */
class INode {
public:
  /**
   * @brief Return reconstructed source code from constructed AST
   *
   * @return string Pure source code
   */
  virtual string source() const = 0;
};
