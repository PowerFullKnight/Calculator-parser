#ifndef TOKENLIST_H
#define TOKENLIST_H

#include <string>
#include  <vector>

#include "General.h"
#include "Token.h"


class TokenList
{
    public:
        TokenList(const std::string& expression);
        TokenList(const std::vector<Token> list);

        ValueType eval();

        bool canCalculate() const;
        ValueType calculate() const;

        void checkExpression() const;

    public:
        void tokenise(const std::string& expression);
        bool isEnclaveInBracket() const;

        std::vector<Token> m_list;
};

#endif // TOKENLIST_H
