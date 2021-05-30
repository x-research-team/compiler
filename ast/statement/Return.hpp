#pragma once

#include <memory>

#include <boost/format.hpp>

#include "../Expression.hpp"
#include "../Statement.hpp"

namespace S {
class Return : public Statement {
private:
  expression_t value;

public:
  Return(const token_t &token) : Statement(token) {}

  /**
   * @brief Set the value for return
   *
   * @param value
   */
  void set_value(const expression_t &value) { this->value = value; }

  string source() const override {
    return (fmt("%1% %2%;") % get_literal() % value->source()).str();
  }
};
} // namespace S
