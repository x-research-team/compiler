#pragma once

#include <memory>

#include "Node.hpp"

class Expression : public Node {
public:
  string source() const override { return this->get_literal(); }

protected:
  Expression(const shared_ptr<Token> token) : Node(token) {}
};
