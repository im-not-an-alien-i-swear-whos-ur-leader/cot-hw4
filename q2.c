// Homework 4 - Question 2
// COP4500 - Spring 2020

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "generic_functions.h"
#include "helper_functions.h"
#include "fixed_iteration.h"

#include "bisection.h"

// As requested, the commenting is done very liberally on this assignment.


// This is the function "x^3 - x^2 + 2" defined in the hw4_function.c file.
extern param_func_s hw4_function;


// When compiling, I have option to either run test code, or to compile the main function to be submitted
// for nnthis question (q2) of the assignment.
#ifndef TEST
// Solution for question 2
int main(int argc, char **argv)
{
  interval_s interval_q2={-200.0, 300.0};
  float precision=1.0E-2;

  iter_result result=bisect(hw4_function.node, interval_q2, 5.0E+0, 0.0);// Very low accuracy, just for initial guess

  interval_q2.start=result.interval.start;
  interval_q2.end=result.interval.end;
  
  fixed_pt_param f_p_param=get_fixed_pt_param(hw4_function.node, interval_q2, 0.0);
  
  // Call fixed point iteration function. The ".node" member is a struct
  // containing the function itself, derivatives, and its inverse. 
  result=fixed_pt(hw4_function.node, interval_q2, precision, 0.0, f_p_param);

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
