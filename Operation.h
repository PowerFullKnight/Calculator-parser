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
    return my_pow(a, b-1) * a;
}

struct pow_ope: operation_function {
  ValueType operator() (const ValueType& x, const ValueType& y) const override
  {
      if(y - 2 < 0.0001) // Very used case
        return x*x;
      return my_pow(x, y);
  }
};




#endif // OPERATION_H_INCLUDED
