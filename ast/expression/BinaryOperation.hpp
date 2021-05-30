#pragma once

#include <memory>

#include <boost/format.hpp>

#include "../Expression.hpp"

namespace E {
class BinaryOperation : public Expression {
private:
  expression_t left;
  expression_t right;

public:
  BinaryOperation(const token_t &token) : Expression(token) {}

  void set_left(const expression_t &expression) { this->left = expression; }

  void set_right(const expression_t &expression) { this->right = expression; }

  string source() const override {
    return (fmt("%1% %2% %3%") % left->source() % get_literal() %
            right->source())
        .str();
  }
};
} // namespace E
