#pragma once

#include <memory>

#include <boost/format.hpp>

#include "../Expression.hpp"
#include "../Statement.hpp"

namespace S {
class Return : public Statement {
private:
  shared_ptr<Expression> value;

public:
  Return(const shared_ptr<Token> &token) : Statement(token) {}

  /**
   * @brief Set the value for return
   *
   * @param value
   */
  void set_value(const shared_ptr<Expression> &value) { this->value = value; }

  string source() const override {
    return (boost::format("%1% %2%;") % get_literal() % value->source()).str();
  }
};
} // namespace S
