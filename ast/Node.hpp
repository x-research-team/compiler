#pragma once

#include <memory>

#include <boost/algorithm/string/join.hpp>
#include <boost/format.hpp>

#include "../token/Token.hpp"
#include "INode.hpp"

using namespace boost::algorithm;

/**
 * @brief Is a implementation of AST node
 */
class Node : public INode {
protected:
  using fmt = boost::format;
  
  /**
   * @brief Construct a new Node object
   *
   * @param token
   */
  Node(const token_t &token) { this->token = token; }

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

private:
  /**
   * @brief Token in AST node
   */
  token_t token;
};
