#pragma once

#include <memory>

#include <boost/algorithm/string/join.hpp>
#include <boost/format.hpp>

#include "../Expression.hpp"
#include "../Statement.hpp"

class Function : public Expression {
private:
  shared_ptr<Expression> name;
  vector<shared_ptr<Expression>> arguments;
  vector<shared_ptr<Statement>> statements;

public:
  Function(const shared_ptr<Token> &token) : Expression(token) {}

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

    return (boost::format("%1% (%2%) { %3% }") % get_literal() %
            boost::algorithm::join(args, ", ") %
            boost::algorithm::join(body, " "))
        .str();
  }
};
