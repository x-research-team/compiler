#pragma once

#include <memory>

#include "../Expression.hpp"

namespace L {
class Bool : public Expression {
private:
  bool value;

public:
  Bool(const shared_ptr<Token> &token) : Expression(token) {
    auto literal = get_literal();
    value = literal == "true";
  }

  string source() const override { return value ? "true" : "false"; }
};
} // namespace L
