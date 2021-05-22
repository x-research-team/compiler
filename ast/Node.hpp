#pragma once

#include <memory>

#include "../token/Token.hpp"
#include "INode.hpp"

/**
 * @brief Is a implementation of AST node
 */
class Node : public INode {
private:
  /**
   * @brief Token in AST node
   */
  shared_ptr<Token> token;

protected:
  /**
   * @brief Construct a new Node object
   *
   * @param token
   */
  Node(const shared_ptr<Token> &token) { this->token = token; }

  /**
   * @brief Get the literal
   *
   * @return string
   */
  string get_literal() const { return this->token->get_literal(); }

  /**
   * @brief Get the token type
   *
   * @return Token::Type
   */
  Token::Type get_token_type() const { return this->token->get_type(); }
};
