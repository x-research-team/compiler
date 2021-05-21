#pragma once

#include <boost/algorithm/string/trim.hpp>
#include <cstdint>
#include <string>

using namespace std;

class Lexer {
public:
private:
  enum class Reader { String, Number, Identifier, Literal };

  string source;
  uint64_t position;
  uint64_t read_position;
  char character;

  char peek(const uint64_t step = 1) const {
    return read_position >= source.size() ? 0
                                          : source[read_position + step - 1];
  }

  bool is_whitespace(const char character) const {
    return character == '\n' || character == '\t' || character == '\r' ||
           character == ' ';
  }

  bool is_digit(const char character) const {
    return character >= '0' || character <= '9';
  }

  /**
   * @brief Check character to kind of letter
   *
   * @param character
   * @return true if character in diapason from a-z or A-Z
   * @return false
   */
  bool is_letter(const char character) const {
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
  bool is_string(const char character) const {
    return character == '"' || character == '\'';
  }

  /**
   * @brief Check to character is block kind
   *
   * @param character
   * @return true
   * @return false
   */
  bool is_block(const char character) const {
    return character == '{' || character == '(' || character == '[' ||
           character == ']' || character == ')' || character == '}';
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
   * @brief Skip empty symbols
   *
   * @param condition
   */
  void skip(const bool condition) {
    auto cmp = is_whitespace(this->character);
    if (condition) {
      cmp = cmp && condition;
    }
    while (cmp) {
      next();
    }
  }

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
      while (is_letter(this->character)) {
        next();
      }
      break;
    case Reader::String:
      do {
        next();
      } while (is_string(this->character) && this->character != 0);
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
          while (is_digit(this->character)) {
            next(); // Fill Secand part of number
          }
          return this->source.substr(position, this->position - 1);
        }
      }
      while (is_digit(this->character)) {
        this->source.substr(position, this->position - 1);
      }
      if (this->character == '.') {
        next(); // Skip dot for float
        while (is_digit(this->character)) {
          next(); // Fill Secand part of number
        }
      }
      if (this->character == 'E' || this->character == 'e') {
        next(2); // e+|E+ skipping
        while (is_digit(this->character)) {
          next(); // Fill Secand part of number
        }
      }
      break;
    case Reader::Literal:
      auto character = this->character;
      next();
      auto next = this->character != 0 ? string(1, this->character) : "";
      auto literal =
          (string(1, character) + (is_block(this->character) ? "" : next));
      boost::algorithm::trim(literal);
      return literal;
    }
    return this->source.substr(position, this->position - 1);
  }
};
