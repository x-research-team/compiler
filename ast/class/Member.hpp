#pragma once

#include <map>
#include <memory>
#include <vector>

#include "../Statement.hpp"

#include "../../token/Keyword.hpp"

namespace C {
class Member : public Statement {
public:
  enum class Qualifier {
    None,
    Public,
    Private,
    Protected,
    Const,
    Static,
    Async
  };

  const map<Qualifier, Token::Type> qualifiers = {
      {Qualifier::Public, Token::Type::Public},
      {Qualifier::Private, Token::Type::Private},
      {Qualifier::Protected, Token::Type::Protected},
      {Qualifier::Const, Token::Type::Const},
      {Qualifier::Static, Token::Type::Static},
      {Qualifier::Async, Token::Type::Async},
  };

  Member(const token_t &token) : Statement(token) {}
  string source() const override {
    vector<string> list_qualifiers;
    if (qualifiers.contains(protection_qualifier)) {
      list_qualifiers.push_back(
          keyword::literals.at(qualifiers.at(protection_qualifier)));
    }
    if (qualifiers.contains(const_qualifier)) {
      list_qualifiers.push_back(
          keyword::literals.at(qualifiers.at(const_qualifier)));
    }
    if (qualifiers.contains(static_qualifier)) {
      list_qualifiers.push_back(
          keyword::literals.at(qualifiers.at(static_qualifier)));
    }
    if (qualifiers.contains(async_qualifier)) {
      list_qualifiers.push_back(
          keyword::literals.at(qualifiers.at(async_qualifier)));
    }
    return !list_qualifiers.empty()
               ? (fmt("%1% %2") % join(list_qualifiers, " ") %
                  statement->source())
                     .str()
               : (fmt("%1%") % statement->source()).str();
  }

  void set_statement(const statement_t &statement) {
    this->statement = statement;
  }

  void set_qualifier(const Qualifier qualifier) {
    switch (qualifier) {
    case Qualifier::Public:
    case Qualifier::Private:
    case Qualifier::Protected:
      protection_qualifier = qualifier;
      break;
    case Qualifier::Const:
      const_qualifier = qualifier;
      break;
    case Qualifier::Static:
      static_qualifier = qualifier;
      break;
    case Qualifier::Async:
      async_qualifier = qualifier;
      break;
    case Qualifier::None:
      break;
    }
  }

  void reset_qualifiers() {
    protection_qualifier = Qualifier::None;
    static_qualifier = Qualifier::None;
    const_qualifier = Qualifier::None;
    async_qualifier = Qualifier::None;
  }

private:
  statement_t statement;
  Qualifier protection_qualifier = Qualifier::None;
  Qualifier static_qualifier = Qualifier::None;
  Qualifier const_qualifier = Qualifier::None;
  Qualifier async_qualifier = Qualifier::None;
};
} // namespace C

using member_t = shared_ptr<C::Member>;
