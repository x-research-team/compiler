#pragma once

#include "FlipMap.hpp"
#include "Token.hpp"
#include <string>

using namespace std;

namespace operators {

static const map<Token::Type, string> literals = {
    {Token::Type::Assign, "="},       {Token::Type::SpaceShip, "<=>"},
    {Token::Type::Plus, "+"},         {Token::Type::Inc, "++"},
    {Token::Type::Dec, "--"},         {Token::Type::PlusAssign, "+="},
    {Token::Type::MinusAssign, "-="}, {Token::Type::AsteriskAssign, "*="},
    {Token::Type::SlashAssign, "/="}, {Token::Type::PercentAssign, "%="},
    {Token::Type::Percent, "%"},      {Token::Type::Minus, "-"},
    {Token::Type::Asterisk, "*"},     {Token::Type::Slash, "/"},
    {Token::Type::Semicolon, ";"},    {Token::Type::Dot, "."},
    {Token::Type::Diapason, ".."},    {Token::Type::Etc, "..."},
    {Token::Type::Comma, ","},        {Token::Type::Arrow, "=>"},
    {Token::Type::Colon, ":"},
};

static const map<string, Token::Type> tokens = flip_map(literals);

} // namespace operators
