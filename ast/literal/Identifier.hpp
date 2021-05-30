#pragma once

#include <memory>

#include "../Expression.hpp"

namespace L {
class Identifier : public Expression {
private:
  string value;

public:
  Identifier(const token_t &token) : Expression(token) {
    value = token->get_literal();
  }

  string source() const override { return value; }
};
} // namespace L
