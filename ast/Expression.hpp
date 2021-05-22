#pragma once

#include "Node.hpp"
#include <memory>

class Expression : public Node {
public:
  string source() const override { return this->get_literal(); }

protected:
  Expression(const shared_ptr<Token> token) : Node(token) {}
};
