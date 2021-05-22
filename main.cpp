#include <iostream>

#include "lexer/Lexer.hpp"
#include <boost/foreach.hpp>

int main() {
  auto lexer = make_shared<Lexer>("let a = fn (a, b) => a + b;");
  auto token = lexer->next_token();
  while (!token->end()) {
    token = lexer->next_token();
    cout << (boost::format("[%1%]") % token->get_literal()).str() << endl;
  }
}
