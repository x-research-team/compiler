#pragma once

#include <cstddef>
#include <functional>
#include <map>
#include <memory>

#include "../ast/AST.hpp"
#include "../ast/Expression.hpp"
#include "../ast/ExpressionStatement.hpp"
#include "../ast/Statement.hpp"

#include "../ast/expression/BinaryOperation.hpp"

#include "../ast/statement/Let.hpp"
#include "../ast/statement/Return.hpp"

#include "../ast/literal/Bool.hpp"
#include "../ast/literal/Function.hpp"
#include "../ast/literal/Identifier.hpp"
#include "../ast/literal/Number.hpp"

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
   * @brief Switch tokens make_pair
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

  shared_ptr<Statement> parse_statement() {
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
    if (!current_token->is(Token::Type::Semicolon) &&
        rank < priority(peeked_token->get_type())) {
      type = peeked_token->get_type();
      return expression_parser.contains(type)
                 ? expression_parser.at(type)(expression)
                 : expression;
    }
    return expression;
  }

  shared_ptr<Statement> parse_expression_statement() {
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

  /**
   * @brief Make AST node and skip current token
   *
   * @tparam T = Statement | Expression
   * @return shared_ptr<Statement | Expression>
   */
  template <typename T> shared_ptr<T> make(const bool skip = true) {
    auto statement = make_shared<T>(current_token);
    if (skip) {
      next();
    }
    return statement;
  }

  bool current_token_is(const Token::Type type) {
    if (!current_token->is(type)) {
      return false;
    }
    next();
    return true;
  }

  bool peeked_token_is(const Token::Type type) {
    if (!peeked_token->is(type)) {
      return false;
    }
    next();
    return true;
  }

public:
  Parser(const shared_ptr<Lexer> lexer) {
    this->lexer = lexer;

    next(2);

    statement_parser.insert(
        make_pair(Token::Type::Let, [this]() -> shared_ptr<Statement> {
          auto statement = make<Let>();
          while (!current_token->is(Token::Type::Semicolon)) {
            if (current_token->is(Token::Type::Identifier)) {
              statement->set_identifier(parse_expression());
              next();
            }
            if (!current_token_is(Token::Type::Assign)) {
              return nullptr;
            }
            statement->set_value(parse_expression());
          }
          return statement;
        }));
    statement_parser.insert(
        make_pair(Token::Type::Return, [this]() -> shared_ptr<Statement> {
          auto statement = make<Return>();
          statement->set_value(parse_expression());
          next();
          return statement;
        }));

    literal_parser.insert(
        make_pair(Token::Type::Identifier, [this]() -> shared_ptr<Expression> {
          return make<Identifier>(false);
        }));
    literal_parser.insert(
        make_pair(Token::Type::Number, [this]() -> shared_ptr<Expression> {
          return make<Number>(false);
        }));
    literal_parser.insert(
        make_pair(Token::Type::True, [this]() -> shared_ptr<Expression> {
          return make<Bool>(false);
        }));
    literal_parser.insert(
        make_pair(Token::Type::False, [this]() -> shared_ptr<Expression> {
          return make<Bool>(false);
        }));
    literal_parser.insert(
        make_pair(Token::Type::Function, [this]() -> shared_ptr<Expression> {
          auto literal = make<Function>();
          if (current_token_is(Token::Type::LeftParen)) {
            while (!current_token->is(Token::Type::RightParen)) {
              if (current_token_is(Token::Type::Comma)) {
                continue;
              }
              if (current_token->is(Token::Type::Identifier)) {
                literal->add_paramenter(parse_expression());
                next();
                continue;
              }
            }
            next();
          }

          if (current_token_is(Token::Type::LeftBrace)) {
            while (!current_token->is(Token::Type::RightBrace)) {
              literal->add_statement(parse_statement());
              next();
              continue;
            }
            next();
          }

          return literal;
        }));

    expression_parser.insert(make_pair(
        Token::Type::Plus,
        [this](const shared_ptr<Expression> &left) -> shared_ptr<Expression> {
          next();
          auto expression = make<BinaryOperation>();
          expression->set_left(left);
          expression->set_right(parse_expression());
          return expression;
        }));
  }

  shared_ptr<INode> parse() {
    auto ast = make_shared<AST>();
    while (!current_token->end()) {
      auto statement = parse_statement();
      if (statement == nullptr) {
        statement = parse_expression_statement();
      }
      if (statement != nullptr) {
        ast->add_statement(statement);
      }
      next();
    }
    return ast;
  }
};
