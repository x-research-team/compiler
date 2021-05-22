#pragma once

#include <boost/algorithm/string/trim.hpp>
#include <boost/format.hpp>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include "../token/Blocks.hpp"
#include "../token/Keyword.hpp"
#include "../token/Operators.hpp"
#include "../token/Token.hpp"

using namespace std;

class Lexer {
public:
private:
  struct Comparator {
  private:
    char character;

    bool is_digit(const char c) const { return c >= '0' || c <= '9'; }

  public:
    Comparator(const char character) { this->character = character; }

    bool whitespace() const {
      return character == '\n' || character == '\t' || character == '\r' ||
             character == ' ';
    }

    bool digit() const { return is_digit(character); }

    /**
     * @brief Check character to kind of letter
     *
     * @param character
     * @return true if character in diapason from a-z or A-Z
     * @return false
     */
    bool letter() const {
      return character >= 'a' || character <= 'z' || character >= 'A' ||
             character <= 'Z' || character == '_';
    }

    /**
     * @brief Check character to kind of string
     *
     * @param character
     * @return true if is "|'
     * @return false otherwise
     */
    bool string() const { return character == '"' || character == '\''; }

    /**
     * @brief Check to character is block kind
     *
     * @param character
     * @return true
     * @return false
     */
    bool block() const {
      return character == '{' || character == '(' || character == '[' ||
             character == ']' || character == ')' || character == '}';
    }

    bool op() const {
      return !letter() && !digit() && !whitespace() && !block() &&
             character != 0;
    }

    bool signed_digit(const char next) {
      return character == '-' && is_digit(next);
    };
  };

  enum class Reader { String, Number, Identifier, Literal };

  string source;
  uint64_t position;
  uint64_t read_position;
  char character;

  Comparator is(const char character) { return Comparator(character); }

  char peek(const uint64_t step = 1) const {
    return read_position >= source.size() ? 0
                                          : source[read_position + step - 1];
  }

  /**
   * @brief Switch to next character in source
   *
   * @param step
   */
  void next(const uint64_t step = 1) {
    for (size_t i = 0; i < step; i++) {
      this->character = peek(1);
      this->position = this->read_position;
      ++this->read_position;
    }
  }

  /**
   * @brief Skip whitespaces
   */
  void skip() {
    while (is(this->character).whitespace()) {
      next();
    }
  }

  /**
   * @brief Skip whitespaces with addition condition
   *
   * @param condition
   */
  void skip(const bool condition) {
    if (condition) {
      skip();
    }
  }

  static map<string, function<shared_ptr<Token>()>> tokens;

  /**
   * @brief Read token literal
   *
   * @param reader type of reader Identifier|String|Number|Literal
   * @return string Literal of token
   */
  string read(const Reader reader = Reader::Identifier) {
    auto position = this->position;
    switch (reader) {
    case Reader::Identifier:
      while (is(this->character).letter()) {
        next();
      }
      break;
    case Reader::String:
      do {
        next();
      } while (is(this->character).string() && this->character != 0);
      break;
    case Reader::Number:
      if (this->character == '-') {
        next(); // Skip sign
      }
      if (this->character == '0') {
        switch (peek()) {
        case 'b':
        case 'x':
          next(2);
          while (is(this->character).digit()) {
            next(); // Fill Secand part of number
          }
          return this->source.substr(position, this->position - 1);
        }
      }
      while (is(this->character).digit()) {
        this->source.substr(position, this->position - 1);
      }
      if (this->character == '.') {
        next(); // Skip dot for float
        while (is(this->character).digit()) {
          next(); // Fill Secand part of number
        }
      }
      if (this->character == 'E' || this->character == 'e') {
        next(2); // e+|E+ skipping
        while (is(this->character).digit()) {
          next(); // Fill Secand part of number
        }
      }
      break;
    case Reader::Literal:
      auto character = this->character;
      next();
      auto next = this->character != 0 ? string(1, this->character) : "";
      auto literal =
          (string(1, character) + (is(this->character).block() ? "" : next));
      boost::algorithm::trim(literal);
      return literal;
    }
    return this->source.substr(position, this->position - 1);
  }

  shared_ptr<Token> make_token(const string &literal, const uint64_t skip = 0) {
    next(skip);
    return make_shared<Token>(tokens.contains(literal) ? tokens.at(literal)()
                                                       : make_shared<Token>());
  }

  shared_ptr<Token> make_token(const char character, const uint64_t skip = 0) {
    next(skip);
    auto literal = string(1, character);
    return make_shared<Token>(tokens.contains(literal) ? tokens.at(literal)()
                                                       : make_shared<Token>());
  }

public:
  Lexer(const string &source) {
    this->source = source;
    for (const auto op : operators::literals) {
      auto literal = op.second;
      switch (auto token = op.first) {
      case Token::Type::Minus:
        tokens.insert(
            make_pair(literal, [this, literal]() -> shared_ptr<Token> {
              if (this->character == '-' && is(peek()).digit()) {
                return make_shared<Token>(Token::Type::Number,
                                          read(Reader::Number));
              }
              return make_shared<Token>(Token::Type::Minus, literal);
            }));
        continue;
      default:
        tokens.insert(
            make_pair(literal, [this, literal]() -> shared_ptr<Token> {
              return make_shared<Token>(operators::tokens.at(literal), literal);
            }));
        continue;
      }
    }

    for (const auto block : blocks::literals) {
      auto literal = block.second;
      switch (auto token = block.first) {
      case Token::Type::Quote:
      case Token::Type::DoubleQuote:
        tokens.insert(
            make_pair(literal, [this, literal]() -> shared_ptr<Token> {
              next(); // skip start quote
              auto token = make_shared<Token>(
                  Token::Type::String, (boost::format("%1%%2%%3%") % literal %
                                        read(Reader::String) % literal)
                                           .str());
              next(); // skip end quote
              return token;
            }));
        continue;
      default:
        tokens.insert(
            make_pair(literal, [this, literal]() -> shared_ptr<Token> {
              return make_shared<Token>(blocks::tokens.at(literal), literal);
            }));
        continue;
      }
    }

    next();
  }

  /**
   * @brief Move to next token in source
   *
   * @return shared_ptr<Token>
   */
  shared_ptr<Token> next_token() {
    skip();

    if (this->character == 0) {
      return make_token(this->character);
    }

    string literal;

    if (is(this->character).letter()) {
      literal.append(read(Reader::Identifier));
      auto type = keyword::tokens.contains(literal)
                      ? keyword::tokens.at(literal)
                      : Token::Type::Identifier;
      return make_shared<Token>(type, type != Token::Type::Identifier
                                          ? keyword::literals.at(type)
                                          : literal);
    }

    if (is(this->character).digit()) {
      return make_shared<Token>(Token::Type::Number, read(Reader::Number));
    }

    auto character = string(1, this->character);

    if (is(this->character).string()) {
      return make_token(character);
    }

    if (is(this->character).block()) {
      return make_token(character, 1);
    }

    while (is(this->character).op()) {
      auto peeked = peek();
      if (is(this->character).signed_digit(peeked)) {
        break; // hack for signed digit
      }
      literal.append(read(Reader::Literal));
      if (!is(peeked).op()) {
        break;
      }
      next();
    }

    return make_token(literal != "" ? literal : character);
  }
};
