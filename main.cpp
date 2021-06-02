#include <iostream>

#include <memory>

#include "lexer/Lexer.hpp"
#include "parser/Parser.hpp"

int main() {
  auto lexer = make_shared<Lexer>(
      "let A = class : B, C { fn f(a, b, c) { return a + b + c + 1; }; }");
  auto parser = make_shared<Parser>(lexer);
  cout << parser->parse()->source() << endl;
}
