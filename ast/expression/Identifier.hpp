#pragma once

#include <memory>

#include "../Expression.hpp"

class Identifier : public Expression {
private:
  string value;

public:
  Identifier(const shared_ptr<Token> &token) : Expression(token) {
    value = token->get_literal();
  }

  string source() const override { return value; }
};
