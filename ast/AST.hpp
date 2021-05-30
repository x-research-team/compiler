#pragma once

#include <memory>
#include <vector>

#include "INode.hpp"
#include "Statement.hpp"

class AST : public INode {
private:
  vector<statement_t> statements;

public:
  /**
   * @brief Add new statement to AST
   *
   * @param statement Source statement
   */
  void add_statement(const statement_t statement) {
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
