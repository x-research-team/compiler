#pragma once

#include <memory>

#include <boost/format.hpp>

#include "../Expression.hpp"

class BinaryOperation : public Expression {
private:
  shared_ptr<Expression> left;
  shared_ptr<Expression> right;

public:
  BinaryOperation(const shared_ptr<Token> &token) : Expression(token) {}

  void set_left(const shared_ptr<Expression> &expression) {
    this->left = expression;
  }

  void set_right(const shared_ptr<Expression> &expression) {
    this->right = expression;
  }

  string source() const override {
    return (boost::format("%1% %2% %3%") % left->source() % get_literal() %
            right->source())
        .str();
  }
};
