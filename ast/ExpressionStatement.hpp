#pragma once

#include <memory>

#include "Expression.hpp"
#include "Statement.hpp"

class ExpressionStatement : public Statement {
private:
  expression_t expression;

public:
  ExpressionStatement(const token_t &token) : Statement(token) {}

  void set_expression(const expression_t &expression) {
    this->expression = expression;
  }

  string source() const override { return this->expression->source(); }
};
