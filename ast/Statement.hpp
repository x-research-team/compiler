#pragma once

#include <memory>

#include "Node.hpp"

class Statement : public Node {
public:
  enum class Type { Single, Array, Cortege };

  string source() const override { return this->get_literal(); }

protected:
  Statement(const token_t &token) : Node(token) {}
};
