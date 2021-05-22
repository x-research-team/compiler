#pragma once

#include "FlipMap.hpp"
#include "Token.hpp"
#include <string>

using namespace std;

class Blocks : public FlipMap {
public:
  const map<Token::Type, string> literals = {
      {Token::Type::LeftBrace, "{"},    {Token::Type::RightBrace, "}"},
      {Token::Type::LeftParen, "("},    {Token::Type::RightParen, ")"},
      {Token::Type::LeftBracket, "["},  {Token::Type::RightBracket, "]"},
      {Token::Type::DoubleQuote, "\""}, {Token::Type::Quote, "'"},
  };
  const map<string, Token::Type> tokens = flip_map(literals);
};
