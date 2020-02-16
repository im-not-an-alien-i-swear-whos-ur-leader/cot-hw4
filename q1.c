// Homework 4 - Question 1
// COP4500 - Spring 2020

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define a function pointer to be passed to the bisection method
typedef float (*function_ptr)(float x);

// This struct is used to define the interval used in the bisection method.
typedef struct interval
{
  float start;
  float end;
} interval_s;

typedef struct bisection_result
{
  float root;
  // num_iterations is negative for failure where the absolute value is how many were performed.
  int num_iterations;
} bisect_res;

// Prototype for the bisection method. Pass a function to solve and interval for the root.
bisect_res bisect(function_ptr function, interval_s interval, float precision);


float function_q1(float x)
{
  // x^3 - x^2 + 2
  // can be rewritten as: (x-1)*x*x+2
  return((x-1)*x*x+2);
}

// When compiling, I have option to either run test code, or to compile the main function to be submitted
// for this question (q1) of the assignment.
#ifndef TEST
// Solution for question 1
int main(int argc, char **argv)
{
  interval_s interval_q1={-200.0, 300.0};
  float precision=10.0E-2;
  
  bisect_res result=bisect(function_q1, interval_q1, precision);

  // NaN is returned if the intermediate value theorem does not apply because
  // f(start) and f(end) are the same sign. In C, NaN!=NaN
  if(result.num_iterations<0 || result.root!=result.root)
  {
    fprintf(stderr, "The method failed after %d iterations.\n", abs(result.num_iterations));
    exit(-1);
  }
  else
  {
    printf("The procedure was successful.\nThe value of root is: %f\n", result.root);
  }
  return(0);
}

#endif

int same_sign(float a, float b)
{
  // This uses 3 different "signs" of 0, +, -
  
  if(a==0.0 || b==0.0)
    return(a==b);

  // != is xor in c
  return(!((a>0.0)!=(b>0.0)));
}

float calculate_mid(float start, float end)
{
  return((start+end)/2);
}

bisect_res bisect(function_ptr function, interval_s interval, float precision)
{
  bisect_res result;
  result.num_iterations=0;

  if(interval.start>interval.end)
  {
    // Swap the interval endpoints if they're out of order.
    float temp=interval.start;
    interval.start=interval.end;
    interval.end=temp;
  }

  float f_start=function(interval.start);
  float f_end=function(interval.end);

  // Check if we already have the answer at one of the interval endpoints.
  if(f_start==0.0 || ! same_sign(f_start, function(interval.start+precision)))
  {
    result.root=interval.start;
    return(result);
  }

  if(f_end==0.0 || ! same_sign(f_end, function(interval.end-precision)))
  {
    result.root=interval.end;
    return(result);
  }
  
  // If the endpoints have the same sign, intermediate value theorem doesn't apply.
  // This also covers the case where start==end since they must have the same sign.
  if(same_sign(f_start, f_end))
  {
    // Return NaN for the root and 0 iterations.
    result.root=0.0/0.0;
    return(result);
  }

  float start=interval.start;
  float end=interval.end;

  float mid=calculate_mid(start, end);
  float y;
  float interval_len=end-start;
  
  while(interval_len>precision)
  {
    y=function(mid);
    f_start=function(start);

    if(same_sign(y, f_start))
    {
      start=mid;
    }
    else
    {
      end=mid;
    }

    mid=calculate_mid(start, end);
    result.num_iterations++;
    interval_len/=2.0;
  }
  result.root=mid;
  return(result);
}



//###############################################################################
// Run test code instead of the assignment submission
#ifdef TEST

#include "test_functions.h"

int main(int argc, char ** argv)
{
  
  return(0);
}


#endif
//###############################################################################
