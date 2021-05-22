#pragma once

#include <memory>

#include "../Statement.hpp"
#include "../expression/Identifier.hpp"

class LetStatement : public Statement {
  shared_ptr<Identifier> identifier;
};
