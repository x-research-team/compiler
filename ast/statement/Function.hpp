#pragma once

#include <memory>

#include <boost/algorithm/string/join.hpp>
#include <boost/format.hpp>

#include "../Expression.hpp"
#include "../Statement.hpp"

namespace S {
class Function : public Statement {
private:
  shared_ptr<Expression> name;
  vector<shared_ptr<Expression>> arguments;
  vector<shared_ptr<Statement>> statements;

public:
  Function(const shared_ptr<Token> &token) : Statement(token) {}

  void set_name(const shared_ptr<Expression> &identifier) {
    this->name = identifier;
  }

  void add_paramenter(const shared_ptr<Expression> &paramenter) {
    arguments.push_back(paramenter);
  }

  void add_statement(const shared_ptr<Statement> &statement) {
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

    return (boost::format("%1% %2%(%3%) { %4% }") % get_literal() %
            name->source() % boost::algorithm::join(args, ", ") %
            boost::algorithm::join(body, " "))
        .str();
  }
};
} // namespace S
