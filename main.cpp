#include <iostream>

#include "token/Token.hpp"

int main(int, char **) {
  Token token(Token::Type::Identifier, 'a');
  std::cout << token.get_literal();
}
