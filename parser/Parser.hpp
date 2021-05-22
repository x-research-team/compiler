#pragma once

#include <cstddef>
#include <functional>
#include <map>
#include <memory>

#include "../ast/AST.hpp"
#include "../ast/Expression.hpp"
#include "../ast/ExpressionStatement.hpp"
#include "../ast/Statement.hpp"
#include "../ast/statement/LetStatement.hpp"

#include "../lexer/Lexer.hpp"
#include "../token/Token.hpp"

using namespace std;

class Parser {
private:
  shared_ptr<Lexer> lexer;

  shared_ptr<Token> current_token;
  shared_ptr<Token> peeked_token;

  enum class OperationPriority {
    Minimal,
    Assign,
    Add = 2,
    Substract = Add,
    Multiplication = 3,
    Division = Multiplication,
    PartlesDivision = Division,
    Power,
    Call,
    Index,
  };

  const map<Token::Type, OperationPriority> priorities = {
      {Token::Type::Plus, OperationPriority::Add},
      {Token::Type::Minus, OperationPriority::Substract},
      {Token::Type::Asterisk, OperationPriority::Multiplication},
      {Token::Type::Slash, OperationPriority::Division},
      {Token::Type::Assign, OperationPriority::Assign},
  };

  OperationPriority priority(Token::Type type) {
    return priorities.contains(type) ? priorities.at(type)
                                     : OperationPriority::Minimal;
  }

  /**
   * @brief Switch tokens pair
   *
   * @param step number of steps to switch
   */
  void next(const int step = 1) {
    for (auto i = 0; i < step; ++i) {
      this->current_token = this->peeked_token;
      this->peeked_token = lexer->next_token();
    }
  }

  using statement_parser_fn = function<shared_ptr<Statement>()>;
  using literal_parser_fn = function<shared_ptr<Expression>()>;
  using expression_parser_fn =
      function<shared_ptr<Expression>(shared_ptr<Expression>)>;

  map<Token::Type, statement_parser_fn> statement_parser;
  map<Token::Type, literal_parser_fn> literal_parser;
  map<Token::Type, expression_parser_fn> expression_parser;

  shared_ptr<Statement> parser_statement() {
    auto type = current_token->get_type();
    return statement_parser.contains(type) ? statement_parser.at(type)()
                                           : nullptr;
  }

  shared_ptr<Expression>
  parse_expression(const OperationPriority rank = OperationPriority::Minimal) {
    auto type = current_token->get_type();
    if (!literal_parser.contains(type)) {
      return nullptr;
    }
    auto expression = literal_parser.at(type)();
    if (current_token->is(Token::Type::Semicolon) &&
        rank < priority(peeked_token->get_type())) {
      type = peeked_token->get_type();
      return expression_parser.contains(type)
                 ? expression_parser.at(type)(expression)
                 : expression;
    }
    return expression;
  }

  shared_ptr<Statement> parser_expression_statement() {
    if (current_token->is(Token::Type::Semicolon)) {
      return nullptr;
    }

    auto statement = make_shared<ExpressionStatement>(current_token);
    statement->set_expression(parse_expression());

    if (peeked_token->is(Token::Type::Semicolon)) {
      next();
    }

    return statement;
  }

public:
  Parser(const shared_ptr<Lexer> lexer) {
    this->lexer = lexer;

    next(2);

    statement_parser.insert(
        pair(Token::Type::Let, [this]() -> shared_ptr<Statement> {
          auto statement = make_shared<LetStatement>(current_token);
          next();
          if (current_token->is(Token::Type::Identifier)) {
          }
          return statement;
        }));
  }

  shared_ptr<INode> parse() {
    auto ast = make_shared<AST>();
    while (!current_token->end()) {
      auto statement = parser_statement();
      if (statement == nullptr) {
        statement = parser_expression_statement();
      }
      if (statement != nullptr) {
        ast->add(statement);
      }
      next();
    }
    return ast;
  }
};
