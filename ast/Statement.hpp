#pragma once

#include "Node.hpp"
#include <memory>

class Statement : public Node {
public:
  enum class Type { Single, Array, Cortege };

  string source() const override { return this->get_literal(); }

protected:
  Statement(const shared_ptr<Token> token) : Node(token) {}
};
