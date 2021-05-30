#pragma once

#include <memory>
#include <vector>

#include <boost/format.hpp>

#include "../Expression.hpp"
#include "../Statement.hpp"

#include "../class/Member.hpp"

namespace S {
class Class : public Statement {
private:
  const string without_inherences_format = "%1% %2% { %3% %4% }";
  const string with_inherences_format = "%1% %2% : %3% { %4% %5% }";

  using inherence_t = expression_t;
  using identifier_t = expression_t;
  using inherences_t = vector<inherence_t>;

  identifier_t name;
  inherences_t inherences;
  vector<member_t> fields;
  vector<member_t> methods;

public:
  Class(const token_t &token) : Statement(token) {}

  void set_name(const identifier_t &identifier) { name = identifier; }

  void add_inherence(const inherence_t &expression) {
    inherences.push_back(expression);
  }

  void add_field(const member_t &expression) { fields.push_back(expression); }

  void add_method(const member_t &expression) { methods.push_back(expression); }

  string source() const override {
    vector<string> members;
    if (inherences.empty()) {
      return (fmt(without_inherences_format) % get_literal() %
              name->source())
          .str();
    }
    return (fmt(with_inherences_format) % get_literal() %
            name->source())
        .str();
  }
};
} // namespace S
