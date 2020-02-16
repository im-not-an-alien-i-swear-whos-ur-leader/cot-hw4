#include "test_functions.h"


float test_0(float x)
{
  return(sin(x));
}

float test_1(float x)
{
  return(tanh(x+5.0)-0.4);
}

float test_2(float x)
{
  return((x+1.0)*(x-1.0)*(x)*(x+10.0)*(x-10000.0)*(x));
}

float test_3(float x)
{
  return(1.0/x);
}

float test_4(float x)
{
  return(ln(x));
}

float test_5(float x)
{
  return(pow(x, x));
}
