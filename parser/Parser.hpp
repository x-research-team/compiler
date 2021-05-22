#pragma once

#include <functional>
#include <map>
#include <memory>

#include "../ast/Expression.hpp"
#include "../ast/Statement.hpp"
#include "../lexer/Lexer.hpp"
#include "../token/Token.hpp"

class Parser {
private:
  shared_ptr<Lexer> lexer;

  shared_ptr<Token> current_token;
  shared_ptr<Token> peeked_token;

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

  using statement_parser_fn = function<shared_ptr<Statement>>;
  using literal_parser_fn = function<shared_ptr<Expression>>;
  using expression_parser_fn =
      function<shared_ptr<Expression(shared_ptr<Expression>)>>;

  map<Token::Type, statement_parser_fn> statement_parser;
  map<Token::Type, literal_parser_fn> literals_parser;
  map<Token::Type, expression_parser_fn> expressions_parser;

public:
  Parser(const shared_ptr<Lexer> lexer) {
    this->lexer = lexer;

    next(2);
  }
};
