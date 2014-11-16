#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <memory>

#include "Operation.h"
#include "General.h"

class Token
{
public:

    Token();

    Token(char kind_a, ValueType value_a = 0);

    char kind() const;
    ValueType value() const;

    int getPriorityLvl() const;

    std::unique_ptr<operation_function> operation() const;

    bool isNumber() const noexcept { return m_kind == 'n'; }
    bool isOperator() const noexcept { return (m_kind == '*' || m_kind == '/' || m_kind == '+' || m_kind == '-' || m_kind == '^');}
    bool isOpenBracket() const noexcept { return (m_kind=='{' || m_kind =='[' || m_kind == '('); }
    bool isCloseBracket() const noexcept { return (m_kind=='}' || m_kind ==']' || m_kind == ')'); }

    bool isValid() const noexcept { return isNumber() || isOperator() || isOpenBracket() || isCloseBracket(); }

private:
    char m_kind;
    ValueType m_value;
};

#endif // TOKEN_H_INCLUDED
