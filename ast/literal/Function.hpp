#pragma once

#include <memory>

#include <boost/algorithm/string/join.hpp>
#include <boost/format.hpp>

#include "../Expression.hpp"
#include "../Statement.hpp"

namespace L {
class Function : public Expression {
private:
  expression_t name;
  vector<expression_t> arguments;
  vector<statement_t> statements;

public:
  Function(const token_t &token) : Expression(token) {}

  void add_paramenter(const expression_t &paramenter) {
    arguments.push_back(paramenter);
  }

  void add_statement(const statement_t &statement) {
    statements.push_back(statement);
  }

  string source() const override {
    vector<string> args;
    vector<string> body;

    for (const auto &argument : arguments) {
      args.push_back(argument->source());
    }

    for (const auto &statement : statements) {
      body.push_back(statement->source());
    }

    return (fmt("%1% (%2%) { %3% }") % get_literal() % join(args, ", ") %
            join(body, " "))
        .str();
  }
};
} // namespace L
