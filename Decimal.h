#ifndef DECIMAL_H
#define DECIMAL_H

#include <string>

typedef unsigned long long decimalValueType;

class Decimal
{
public:
    Decimal();
    explicit Decimal(const std::string &strNumber);
    Decimal(decimalValueType numerator, decimalValueType denominator = 1);

    static Decimal fromString (const std::string &strNumber);
    void forceSimplify();

    decimalValueType numerator() const noexcept { return m_numerator; }
    decimalValueType denominator() const noexcept { return m_denominator; }

    // OPERATOR
    Decimal& operator+=(const Decimal& lhs);
    Decimal& operator-=(const Decimal& lhs);
    Decimal& operator*=(const Decimal& lhs);
    Decimal& operator/=(const Decimal& lhs);

    Decimal operator+(const Decimal& lhs) const;
    Decimal operator-(const Decimal& lhs) const;
    Decimal operator*(const Decimal& lhs) const;
    Decimal operator/(const Decimal& lhs) const;

    bool operator==(const Decimal& lhs) const;
    bool operator<(const Decimal& lhs) const;
    bool operator>(const Decimal& lhs) const;
    bool operator<=(const Decimal& lhs) const;
    bool operator>=(const Decimal& lhs) const;


protected:
    void fromStringImplement (const std::string &strNumber);


    void simplify();

    bool m_minus;
    decimalValueType m_numerator;
    decimalValueType m_denominator;

};

#endif // DECIMAL_H
