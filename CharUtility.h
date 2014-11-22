#ifndef CHARUTILITY_H_INCLUDED
#define CHARUTILITY_H_INCLUDED


#include <string>
#include <sstream>


#include "Token.h"


Token getTokenFor(const char c) noexcept;

inline bool isDigKind(const char c) noexcept { return (c=='n'); }
inline bool isMul(const char c) noexcept { return (c=='*'); }
inline bool isDiv(const char c) noexcept { return (c=='/'); }
inline bool isAdd(const char c) noexcept { return (c=='+'); }
inline bool isMin(const char c) noexcept { return (c=='-'); }
inline bool isPow(const char c) noexcept { return (c=='^'); }

inline bool isHighOperator(const char c) noexcept { return (isMul(c) || isDiv(c)); }
inline bool isLowOperator(const char c) noexcept  { return (isAdd(c) || isMin(c)); }
inline bool isOperator(const char c) noexcept { return (isMul(c) || isDiv(c) || isAdd(c) || isMin(c));}

inline bool isOpenBracket(const char c) noexcept { return (c=='{' || c =='[' || c == '('); }
inline bool isCloseBracket(const char c) noexcept { return (c=='}' || c ==']' || c == ')'); }

inline bool isValidOperation(const char c) noexcept { return (c!=' ' && c!='\n'); }
inline bool isValidToken(const char c) noexcept { return (isDigKind(c) || isOperator(c) || isOpenBracket(c) || isCloseBracket(c)); }

inline int charToDigit(const char c) noexcept { return static_cast<int>(c-'0');  }

template <typename T>
std::string toString(T value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

template <typename T>
T stringTo(const std::string &to, bool *ok = nullptr)
{
    std::istringstream iss(to);
    T val;
    if((iss >> val)){
        if(ok != nullptr)
            *ok = true;
        return val;
    }
    else{
        if(ok != nullptr)
            *ok = false;
       return T();
    }
}


template <typename Iter>
Iter findHighestPrecedence(Iter beg, Iter end)
{
    Iter endCopy = end;
    int bracket {0};
    int actualPriority{6};

    while(actualPriority >= 0)
    {
        while(end != beg)
        {
            --end;
            const Token tok = *end;
            if(tok.isOpenBracket())
                ++bracket;
            else if(tok.isCloseBracket())
                --bracket;
            else if(tok.getPriorityLvl() == actualPriority && bracket == 0){
                return end;
            }
        }

        bracket = 0;
        end = endCopy;
        --actualPriority;
    }

    return endCopy;
}

#endif // CHARUTILITY_H_INCLUDED
