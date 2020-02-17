// Homework 4 - Question 1
// COP4500 - Spring 2020

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define a function pointer to be passed to the fixed point method
typedef float (*function_ptr)(float x);

// This struct is used to define the interval used in the fixed point method.
typedef struct interval
{
  float start;
  float end;
} interval_s;

typedef struct fixed_pt_result
{
  float root;
  // num_iterations is negative for failure where the absolute value is how many were performed.
  int num_iterations;
} fixed_pt_res;

// Prototype for the fixed point method. Pass a function to solve and interval for the root.
bisect_res fixed_pt(function_ptr function, interval_s interval, float precision);


float function_q2(float x)
{
  // x^3 - x^2 + 2
  // can be rewritten as: (x-1)*x*x+2
  return((x-1)*x*x+2);
}

// When compiling, I have option to either run test code, or to compile the main function to be submitted
// for this question (q2) of the assignment.
#ifndef TEST
// Solution for question 2
int main(int argc, char **argv)
{
  interval_s interval_q2={-200.0, 300.0};
  float precision=1.0E-2;
  

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
