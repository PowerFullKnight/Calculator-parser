#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

#include <functional>

#include "General.h"

struct operation_function
{
    virtual ~operation_function(){}
    virtual ValueType operator() (const ValueType& x, const ValueType& y) const = 0;
};

struct plus_ope : operation_function {
   ValueType operator() (const ValueType& x, const ValueType& y) const override {return x+y;}
};

struct minus_ope : operation_function {
  ValueType operator() (const ValueType& x, const ValueType& y) const override {return x-y;}
};

struct multiplies_ope : operation_function {
  ValueType operator() (const ValueType& x, const ValueType& y) const override {return x*y;}
};

struct divides_ope: operation_function {
  ValueType operator() (const ValueType& x, const ValueType& y) const override {return x/y;}
};

inline ValueType my_pow(const ValueType& a, int b)
{
    ValueType res {1};
    for(int i(0); i < b; ++i)
        res *= a;
    return res;
}

struct pow_ope: operation_function {
  ValueType operator() (const ValueType& x, const ValueType& y) const override
  {
      return my_pow(x, static_cast<int>(y));
  }
};




#endif // OPERATION_H_INCLUDED
