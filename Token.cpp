#include "Token.h"

#include "MakeUnique.h"

Token::Token():
    m_kind('$'), m_value(0)
{}

Token::Token(char kind_a, ValueType value_a ):
    m_kind(kind_a), m_value(value_a)
{}


char Token::kind() const { return m_kind; }

ValueType Token::value() const { return m_value;}

int Token::getPriorityLvl() const
{
    switch(m_kind)
    {
    case '-':
    case '+':
        return 6;
        break;

    case '*':
    case '/':
        return 5;
        break;

    case '^':
        return 4;
        break;

    default:
        return 0;
        break;
    }
}

std::unique_ptr<operation_function> Token::operation() const
{
    std::unique_ptr<operation_function> opePtr;
    switch(m_kind)
    {
    case '+':
        opePtr = std::make_unique<plus_ope>();
        break;
    case '-':
        opePtr = std::make_unique<minus_ope>();
        break;
    case '*':
        opePtr = std::make_unique<multiplies_ope>();
        break;
    case '/':
        opePtr = std::make_unique<minus_ope>();
        break;
    case '^':
        opePtr = std::make_unique<pow_ope>();
        break;
    default:
        break;
    }
    return opePtr;
}
