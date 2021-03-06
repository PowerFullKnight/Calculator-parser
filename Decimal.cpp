#include "Decimal.h"

#include "CharUtility.h"
#include "Error.h"

#include <iostream>

// PUBLIC
Decimal::Decimal():
    m_minus(false), m_numerator(0), m_denominator(1)
{
    //ctor
}

Decimal::Decimal(const std::string &strNumber):
    Decimal()
{
    fromStringImplement(strNumber);
}

Decimal::Decimal(decimalValueType numerator_a, decimalValueType denominator_a):
    m_minus(false), m_numerator(numerator_a), m_denominator(denominator_a)
{}

// PUBLIC & STATIC
Decimal Decimal::fromString (const std::string &strNumber)
{
    return Decimal(strNumber);
}

// PUBLIC
void Decimal::forceSimplify()
{
    simplify();
}

// OPERATOR
Decimal& Decimal::operator+=(const Decimal& lhs)
{
    m_numerator = m_numerator * lhs.m_denominator + lhs.m_numerator * m_denominator;
    m_denominator = m_denominator * lhs.m_denominator;

    m_minus = lhs.m_minus && m_minus;
    simplify();
    return *this;
}

Decimal& Decimal::operator-=(const Decimal& lhs)
{
    m_numerator = m_numerator * lhs.m_denominator - lhs.m_numerator * m_denominator;
    m_denominator = m_denominator * lhs.m_denominator;

    simplify();
    return *this;
}

Decimal& Decimal::operator*=(const Decimal& lhs)
{
    m_numerator *= lhs.m_numerator;
    m_denominator *= lhs.m_denominator;
    simplify();
    return *this;
}

Decimal& Decimal::operator/=(const Decimal& lhs)
{
    // We inverse fraction
    Decimal temp(lhs.m_denominator, lhs.m_numerator);

    operator*=(temp);
    simplify();
    return *this;
}

Decimal& Decimal::operator%=(const Decimal& lhs)
{
    if(!isInteger() || !lhs.isInteger())
        throw Error(Error::NumberError);
    m_numerator %= lhs.m_numerator;
    return *this;
}


Decimal Decimal::operator+(const Decimal& lhs) const
{
    Decimal temp(*this);
    temp += lhs;
    return temp;
}

Decimal Decimal::operator-(const Decimal& lhs) const
{
    Decimal temp(*this);
    temp -= lhs;
    return temp;
}

Decimal Decimal::operator*(const Decimal& lhs) const
{
    Decimal temp(*this);
    temp *= lhs;
    return temp;
}

Decimal Decimal::operator/(const Decimal& lhs) const
{
    Decimal temp(*this);
    temp /= lhs;
    return temp;
}

Decimal Decimal::operator%(const Decimal& lhs) const
{
    Decimal temp(*this);
    temp %= lhs;
    return temp;
}


bool Decimal::operator==(const Decimal& lhs) const
{
    return (m_denominator == lhs.m_denominator && m_numerator == lhs.m_numerator && m_minus == lhs.m_minus);
}

bool Decimal::operator<(const Decimal& lhs) const
{
    return (m_numerator * lhs.m_denominator < m_denominator * lhs.m_numerator);
}

bool Decimal::operator>(const Decimal& lhs) const
{
    return (lhs < *this);
}

bool Decimal::operator<=(const Decimal& lhs) const
{
    return !(lhs < *this);
}

bool Decimal::operator>=(const Decimal& lhs) const
{
    return !(*this < lhs);
}

// PRIVATE
void Decimal::fromStringImplement (const std::string &strNumber)
{
    if(strNumber == "0"){
        m_numerator = 0;
        return;
    }

    auto commaPosition = strNumber.find('.');
    bool isComma {true};
    if(commaPosition == std::string::npos){
        isComma = false;
    }

    if(isComma)
    {
        std::string integerPart = strNumber.substr(0, commaPosition);
        bool ok{false};
        decimalValueType integerPartNbr = stringTo<decimalValueType>(integerPart, &ok);
        if(!ok){
            throw Error(Error::NumberError);
            return;
        }
        std::string decimalPart = strNumber.substr(commaPosition);
        decimalPart.erase(0, 1);
        decimalValueType decimalPartNbr = stringTo<decimalValueType>(decimalPart, &ok);
        if(!ok){
            throw Error(Error::NumberError);
            return;
        }

        decimalValueType digits = decimalPart.size();

        decimalValueType pow10 {0};
        if(digits < 15){
            pow10 = quick_10_pow(digits);
        }
        else{
            pow10 = pow(10, digits);
        }
        integerPartNbr *= pow10;
        m_numerator = integerPartNbr + decimalPartNbr;
        m_denominator = pow10;
    }
    else
    {
        bool ok{false};
        decimalValueType integerPartNbr = stringTo<decimalValueType>(strNumber, &ok);
        if(!ok){
            throw Error(Error::NumberError);
            return;
        }
        m_numerator = integerPartNbr;
    }
    simplify();

}

void Decimal::simplify()
{
    const auto p = pgcd(m_numerator, m_denominator);
    if(p != 1){
        m_denominator /= p;
        m_numerator /= p;
    }
}

std::ostream& operator<<(std::ostream& stream, const Decimal& dec)
{
    if(dec.minus())
        stream << '-';
    stream << dec.numerator();
    if(dec.denominator() > 1)
    {
        stream << '/' << dec.denominator();
    }
    return stream;
}
