#pragma once

#include "FlipMap.hpp"
#include "Token.hpp"
#include <map>
#include <string>

using namespace std;
namespace keyword {
static const map<Token::Type, string> literals = {
    {Token::Type::Let, "let"},
    {Token::Type::Const, "const"},
    {Token::Type::Static, "static"},
    {Token::Type::Field, "field"},
    {Token::Type::Virtual, "virtual"},
    {Token::Type::Override, "override"},
    {Token::Type::Property, "property"},
    {Token::Type::Set, "set"},
    {Token::Type::Get, "get"},
    {Token::Type::Class, "class"},
    {Token::Type::Interface, "interface"},
    {Token::Type::Struct, "struct"},
    {Token::Type::Type, "type"},
    {Token::Type::Enum, "enum"},
    {Token::Type::For, "for"},
    {Token::Type::Case, "case"},
    {Token::Type::In, "in"},
    {Token::Type::If, "if"},
    {Token::Type::Else, "else"},
    {Token::Type::Is, "is"},
    {Token::Type::Of, "of"},
    {Token::Type::Continue, "continue"},
    {Token::Type::Break, "break"},
    {Token::Type::Return, "return"},
    {Token::Type::Private, "private"},
    {Token::Type::Public, "public"},
    {Token::Type::Protected, "protected"},
    {Token::Type::Sealed, "sealed"},
    {Token::Type::Internal, "internal"},
    {Token::Type::ReadOnly, "readonly"},
    {Token::Type::Mutable, "mutable"},
    {Token::Type::Service, "service"},
    {Token::Type::True, "true"},
    {Token::Type::False, "false"},
    {Token::Type::Try, "try"},
    {Token::Type::Catch, "catch"},
    {Token::Type::Finally, "finally"},
    {Token::Type::New, "new"},
    {Token::Type::Throw, "throw"},
    {Token::Type::Thread, "thread"},
    {Token::Type::Async, "async"},
    {Token::Type::Await, "await"},
    {Token::Type::Sync, "sync"},
    {Token::Type::Function, "fn"},
};

static const map<string, Token::Type> tokens = flip_map(literals);
} // namespace keyword
