#pragma once

#include <string>

#include "FlipMap.hpp"
#include "Token.hpp"

using namespace std;

namespace blocks {

const map<Token::Type, string> literals = {
    {Token::Type::LeftBrace, "{"},    {Token::Type::RightBrace, "}"},
    {Token::Type::LeftParen, "("},    {Token::Type::RightParen, ")"},
    {Token::Type::LeftBracket, "["},  {Token::Type::RightBracket, "]"},
    {Token::Type::DoubleQuote, "\""}, {Token::Type::Quote, "'"},
};
const map<string, Token::Type> tokens = flip_map(literals);

} // namespace blocks
