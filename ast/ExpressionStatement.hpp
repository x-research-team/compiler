#pragma once

#include <memory>

#include "Expression.hpp"
#include "Statement.hpp"

class ExpressionStatement : public Statement {
private:
  shared_ptr<Expression> expression;

public:
  ExpressionStatement(const shared_ptr<Token> &token) : Statement(token) {}

  void set_expression(const shared_ptr<Expression> &expression) {
    this->expression = expression;
  }

  string source() const override { return this->expression->source(); }
};
