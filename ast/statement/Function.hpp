#pragma once

#include <memory>

#include "../Expression.hpp"
#include "../Statement.hpp"

namespace S {
class Function : public Statement {
private:
  expression_t name;
  vector<expression_t> arguments;
  vector<statement_t> statements;

public:
  Function(const token_t &token) : Statement(token) {}

  void set_name(const expression_t &identifier) { this->name = identifier; }

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

    return (fmt("%1% %2%(%3%) { %4% }") % get_literal() %
            name->source() % join(args, ", ") % join(body, " "))
        .str();
  }
};
} // namespace S
