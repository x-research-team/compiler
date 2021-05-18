#pragma once

#include <string>

using namespace std;

/**
 * @brief Token rules
 */
namespace Token {

/**
 * @brief Token
 */
class Token {
public:
  /**
   * @brief Type of token
   */
  enum class Type {
    Illegal,
    Arrow,
    EndOfFile,
    Identifier,
    UnsignedInt,
    SignedInt,
    Number,
    Float,
    Double,
    Real,
    Complex,
    String,
    Array,
    Object,
    Char,
    Byte,
    Assign,
    Plus,
    Minus,
    Bang,
    Asterisk,
    Slash,
    Lt,
    Gt,
    LtEq,
    GtEq,
    Equal,
    NotEqual,
    Comma,
    Semicolon,
    Colon,
    LeftParen,
    RightParen,
    LeftBrace,
    RightBrace,
    LeftBracket,
    Quote,
    DoubleQuote,
    RightBracket,
    Let,
    Class,
    Interface,
    Struct,
    Function,
    For,
    In,
    Case,
    True,
    False,
    If,
    Else,
    Return,
    Sync,
    Async,
    Await,
    Const,
    Thread,
    Inc,
    Dec,
    PlusAssign,
    MinusAssign,
    AsteriskAssign,
    SlashAssign,
    Percent,
    PercentAssign,
    Continue,
    Break,
    Dot,
    Type,
    Diapason,
    Etc,
    BitWiseLeft,
    BitWiseRight,
    BitAnd,
    BitOr,
    And,
    Or,
    SpaceShip,
    Pipe,
    Try,
    Catch,
    Finally,
    Throw,
    Is,
    Of,
    Enum,
    Field,
    Get,
    Set,
    Public,
    Private,
    Protected,
    Static,
    Sealed,
    Internal,
    ReadOnly,
    Mutable,
    Service,
    Property,
    Override,
    Virtual,
    New,
  };
  /**
   * @brief Construct a new Token object
   *
   * @param type
   * @param literal
   */
  Token(const Type type, const string &literal) {
    this->type = type;
    this->literal = literal;
  }

  /**
   * @brief Construct a new Token object
   *
   * @param type
   * @param literal
   */
  Token(const Type type, const char literal) {
    this->type = type;
    this->literal = literal;
  }

  /**
   * @brief Get the Type
   *
   * @return Type
   */
  Type get_type() const { return this->type; }

  /**
   * @brief Get the Literal
   *
   * @return string
   */
  string get_literal() const { return this->literal; }

  /**
   * @brief
   *
   * @param type
   * @return true
   * @return false
   */
  bool is(Type type) const { return this->type == type; }

  /**
   * @brief
   *
   * @param type
   * @return true
   * @return false
   */
  bool operator==(const Type &type) { return is(type); }

  /**
   * @brief
   *
   * @param type
   * @return true
   * @return false
   */
  bool operator!=(const Type &type) { return !is(type); }

private:
  /**
   * @brief Token type
   */
  Type type;

  /**
   * @brief Literal of token
   */
  string literal;
};
} // namespace Token
