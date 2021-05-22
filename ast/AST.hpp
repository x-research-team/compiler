#pragma once

#include "INode.hpp"
#include "Statement.hpp"
#include <memory>
#include <vector>

class AST : public INode {
private:
  vector<shared_ptr<Statement>> statements;

public:
  /**
   * @brief Add new statement to AST
   *
   * @param statement Source statement
   */
  void add(const shared_ptr<Statement> statement) {
    this->statements.push_back(statement);
  }

  /**
   * @brief Return source of statements of AST
   *
   * @return string
   */
  string source() const override {
    string source;
    for (const auto statement : this->statements) {
      source.append(statement->source());
    }
    return source;
  }
};
