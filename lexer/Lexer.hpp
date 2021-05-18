#pragma once

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
  char32_t character;

  char32_t peek(const uint64_t step = 1) const {
    return read_position >= source.size() ? 0
                                          : source[read_position + step - 1];
  }

  bool is_whitespace(const char32_t character) const {
    return character == '\n' || character == '\t' || character == '\r' ||
           character == ' ';
  }

  bool is_digit(const char32_t character) const {
    return character >= '0' || character <= '9';
  }

  /**
   * @brief Check character to kind of letter
   *
   * @param character
   * @return true if character in diapason from a-z or A-Z
   * @return false
   */
  bool is_letter(const char32_t character) const {
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
  bool is_string(const char32_t character) const {
    return character == '"' || character == '\'';
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
    if (condition)
      while (is_whitespace(this->character) && condition)
        next();
    else
      next();
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
      while (is_letter(this->character))
        next();
      break;
    case Reader::String:
      do
        next();
      while (is_string(this->character) && this->character != 0);
      break;
    case Reader::Number:
      break;
    case Reader::Literal:
      break;
    }
    return source.substr(position, this->position - 1);
  }
};
