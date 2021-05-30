#pragma once

#include <map>
#include <memory>
#include <vector>

#include <boost/format.hpp>

#include "../Statement.hpp"

#include "../literal/Identifier.hpp"

/**
 * @brief let statetemt has 5 variants of present
 * 1. let <identifier> = <expression>;
 * 2. let (<identifier>...<identifier>) = (<expression>...<expression>);
 * 3. let [<identifier>...<identifier>] = [<expression>...<expression>];
 * 4. let (<identifier>...<identifier>) = <expression>;
 * 5. let [<identifier>...<identifier>] = <expression>;
 */
namespace S {
class Let : public Statement {
private:
  expression_t identifier;
  vector<expression_t> identifiers;
  expression_t value;
  map<expression_t, expression_t> values;

public:
  Let(const token_t &token) : Statement(token) {}

  /**
   * @brief Set the identifier
   *
   * @param identifier
   */
  void set_identifier(const expression_t &identifier) {
    this->identifier = identifier;
  }

  /**
   * @brief Set the value
   *
   * @param value
   */
  void set_value(const expression_t &value) { this->value = value; }

  string source() const override {
    return (fmt("%1% %2% = %3%;") % get_literal() %
            identifier->source() % value->source())
        .str();
  }
};
} // namespace S
