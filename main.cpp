#include <iostream>

#include <memory>

#include "lexer/Lexer.hpp"
#include "parser/Parser.hpp"

int main() {
  auto lexer = make_shared<Lexer>("let a = fn (a, b) => a + b;");
  auto parser = make_shared<Parser>(lexer);
  cout << parser->parse()->source() << endl;
}
