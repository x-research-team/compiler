#pragma once

#include <memory>
#include <vector>

#include "../Expression.hpp"
#include "../class/Member.hpp"

namespace L {
class Class : public Expression {
private:
  vector<member_t> fields;
  vector<member_t> methods;

public:
  Class(const token_t &token) : Expression(token) {}

  string source() const override { return ""; }
};
} // namespace L
