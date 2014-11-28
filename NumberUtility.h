#ifndef NUMBERUTILITY_H_INCLUDED
#define NUMBERUTILITY_H_INCLUDED

#include <algorithm>

template <typename T>
T getDigits(T number)
{
    T digits {0};
    while(number / 10 > 1){
        ++digits;
        number/=10;
    }
    return digits;
}

template <typename T>
T quick_10_pow(T pow)
{
    static T arr[16] = {
    1,
    10,
    100,
    1000,
    10000,
    100000,
    1000000,
    10000000,
    100000000,
    1000000000,
    10000000000,
    100000000000,
    1000000000000,
    10000000000000,
    100000000000000,
    1000000000000000};
    return arr[pow];
}

template <typename T>
inline T pow(const T& a, int b)
{
    T res {1};
    for(int i(0); i < b; ++i)
        res *= a;
    return res;
}

template <typename T>
T pgcd(T a , T b )
{
    T r = 0;
    if(a <b)
        std::swap(a, b);

    r = a%b;
    if(r == 0)
        return b;
    else
        return pgcd(b, r);
}
#endif // NUMBERUTILITY_H_INCLUDED
