#pragma once

#include "../lexer/Lexer.hpp"
#include "../token/Token.hpp"
#include <map>
#include <memory>

class Parser {
private:
  shared_ptr<Lexer> lexer;

  shared_ptr<Token> current_token;
  shared_ptr<Token> peeked_token;
};
