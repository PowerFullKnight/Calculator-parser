#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

#include "General.h"
#include "NumberUtility.h"
#include <cmath>

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

struct pow_ope: operation_function {
  ValueType operator() (const ValueType& x, const ValueType& y) const override
  {
      return pow(x.toValue<double>(), y.toValue<double>());
  }
};




#endif // OPERATION_H_INCLUDED
