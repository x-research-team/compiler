#include <iostream>

#include "token/Token.hpp"

int main(int, char **) {
  Token::Token token(Token::Token::Type::Identifier, 'a');
  std::cout << token.get_literal();
}
