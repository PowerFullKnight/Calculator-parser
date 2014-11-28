#ifndef INFINITENUMBER_H_INCLUDED
#define INFINITENUMBER_H_INCLUDED

#include <string>
#include <vector>
#include <ostream>

class InfiniteNumber
{
public:
    InfiniteNumber();
    InfiniteNumber(const std::string &str);

    static InfiniteNumber fromString(const std::string& str);

    std::ostream& writeToStream(std::ostream& stream) const;

private :
    void fromStringImpl(const std::string& str);

    std::vector<char> m_intDigits;
    std::vector<char> m_decDigits;
};

#endif // INFINITENUMBER_H_INCLUDED
