#include "InfiniteNumber.h"

#include "CharUtility.h"

#include <iostream>

InfiniteNumber::InfiniteNumber():
    m_intDigits(),
    m_decDigits()
{

}

InfiniteNumber::InfiniteNumber(const std::string& str):
    InfiniteNumber()
{
    fromStringImpl(str);
}

// STATIC

InfiniteNumber InfiniteNumber::fromString(const std::string& str)
{
    return InfiniteNumber(str);
}

std::ostream& InfiniteNumber::writeToStream(std::ostream& stream) const
{
    for(auto dig : m_intDigits)
    {
        stream << digitToChar(dig);
    }
    if(!m_decDigits.empty())
    {
        stream << '.';
        for(auto dig : m_decDigits)
            stream << digitToChar(dig);
    }
    return stream;
}

// PRIVATE
void InfiniteNumber::fromStringImpl(const std::string& str)
{
    auto commaPos = str.find('.');
    bool isComma = (commaPos != std::string::npos);

    if(isComma)
    {
        std::string intPart = str.substr(0, commaPos);
        std::string decPart = str.substr(commaPos+1);

        for(auto itInt = intPart.begin(); itInt != intPart.end(); ++itInt)
        {
            m_intDigits.push_back(charToDigit(*itInt));
        }
        for(auto itDec = decPart.begin(); itDec != decPart.end(); ++itDec)
        {
            m_decDigits.push_back(charToDigit(*itDec));
        }
    }
    else
    {
        for(auto itInt = str.rbegin(); itInt != str.rend(); ++itInt)
        {
            m_intDigits.push_back(charToDigit(*itInt));
        }
    }
}
