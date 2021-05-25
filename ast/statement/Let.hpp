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
  shared_ptr<Expression> identifier;
  vector<shared_ptr<Expression>> identifiers;
  shared_ptr<Expression> value;
  map<shared_ptr<Expression>, shared_ptr<Expression>> values;

public:
  Let(const shared_ptr<Token> &token) : Statement(token) {}

  /**
   * @brief Set the identifier
   *
   * @param identifier
   */
  void set_identifier(const shared_ptr<Expression> &identifier) {
    this->identifier = identifier;
  }

  /**
   * @brief Set the value
   *
   * @param value
   */
  void set_value(const shared_ptr<Expression> &value) { this->value = value; }

  string source() const override {
    return (boost::format("%1% %2% = %3%;") % get_literal() %
            identifier->source() % value->source())
        .str();
  }
};
} // namespace S
