#pragma once

#include <memory>

#include "../Expression.hpp"

namespace L {
class Number : public Expression {
private:
  string value;

public:
  Number(const shared_ptr<Token> &token) : Expression(token) {
    value = get_literal();
  }

  string source() const override { return value; }
};
} // namespace L
