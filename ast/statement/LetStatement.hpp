#pragma once

#include <memory>

#include "../Statement.hpp"
#include "../expression/Identifier.hpp"

class LetStatement : public Statement {
private:
  shared_ptr<Identifier> identifier;

public:
  LetStatement(const shared_ptr<Token> &token) : Statement(token) {}
};
