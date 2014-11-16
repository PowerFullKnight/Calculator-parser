#include "TokenList.h"

#include <stdexcept>

#include "CharUtility.h"
#include "Error.h"

TokenList::TokenList(const std::string& expression):
    m_list()
{
    tokenise(expression);
}

TokenList::TokenList(const std::vector<Token> list):
    m_list(list)
{}

ValueType TokenList::eval()
{

    if(canCalculate()){
        return calculate();
    }
    else{
        if(isEnclaveInBracket()) // On supprime les parenthèses
        {
            m_list.erase(m_list.begin(), m_list.begin()+1);
            m_list.pop_back();
        }

        auto sepIter = findHighestPrecedence(m_list.begin(), m_list.end());
        if(sepIter == m_list.end()){
            throw Error(Error::OperatorError, -1);
        }

        char op = sepIter->kind();
        TokenList left { std::vector<Token>(m_list.begin(), sepIter) };
        TokenList right { std::vector<Token>(sepIter+1, m_list.end()) };

        m_list.clear();
        m_list.push_back(Token('n', left.eval()));
        m_list.push_back(Token(op));
        m_list.push_back(Token('n', right.eval()));

        return calculate();
    }
}

bool TokenList::canCalculate() const
{
    return ((m_list.size() == 3 && m_list[0].isNumber() && m_list[1].isOperator() && m_list[2].isNumber()) ||
            (m_list.size() == 1 && m_list[0].isNumber()));
}


ValueType TokenList::calculate() const
{
    if(m_list.size() == 1 && m_list[0].isNumber()){
        return m_list[0].value();
    }

    auto operation = m_list[1].operation();
    const ValueType v1 = m_list[0].value();
    const ValueType v2 = m_list[2].value();


    if(!operation){
        throw Error(Error::NoKnowToken);
    }else{
        return operation.get()->operator()(v1, v2);
    }
}

void TokenList::tokenise(const std::string& expression)
{
    m_list.reserve(expression.size());
    for(std::size_t i(0); i < expression.size();)
    {
        const char ch = expression[i];
        if(!isValidOperation(ch)){
            ++i;
            continue;
        }
        else if(!isdigit(ch)){
            m_list.push_back(getTokenFor(ch));
            ++i;
        }
        else
        {
            std::string digitStr;
            while(i < expression.size() && isdigit(expression[i]))
            {
                digitStr += expression[i];
                ++i;
                if(expression[i] == '.'){
                    digitStr += expression[i];
                    ++i;
                }
            }
            m_list.push_back(Token('n', stringTo<ValueType>(digitStr)));
        }
    }
}

void TokenList::checkExpression() const
{
    if(m_list.empty())
        throw Error(Error::ExpressionEmpty);

    const auto sz = m_list.size();
    int bracket {0};

    for(std::size_t i = 0; i < sz; ++i)
    {
        const Token tok = m_list[i];
        if(!tok.isValid()){
            throw Error(Error::NoKnowToken, i);
        }
        if(tok.isOperator())
        {
            if(i+1 < sz && m_list[i+1].isOperator()){
                throw Error(Error::TooManyOperator, i+1);
            }
        }
        if(tok.isOpenBracket()){
            ++bracket;
        }
        if(tok.isCloseBracket()){
            if(bracket == 0){
                throw Error(Error::MissingBeginBracket, i);
            }
            --bracket;
        }
    }

    if(bracket != 0)
        throw Error(Error::MissingCloseBracket, m_list.size());
}

bool TokenList::isEnclaveInBracket() const
{
    if( (m_list.size() >= 1 && !m_list[0].isOpenBracket()) || (m_list.size() >= 1 && !m_list[m_list.size() - 1].isCloseBracket()) )
        return false;

    unsigned bracket {1};
    for(std::size_t i(1); i < m_list.size()-1; ++i) // On sait deja que le premier token est une parenthèse ainsi que le dernier
    {
        const Token tok = m_list[i];
        if(tok.isOpenBracket())
            ++bracket;
        else if(tok.isCloseBracket())
            --bracket;
        if(bracket == 0)
            return false;
    }
    return true;
}
