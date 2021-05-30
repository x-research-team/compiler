#pragma once

#include <memory>

#include "Node.hpp"

class Expression : public Node {
public:
  string source() const override { return this->get_literal(); }

protected:
  Expression(const token_t &token) : Node(token) {}
};
