// Homework 4 - Question 1
// COP4500 - Spring 2020

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "generic_functions.h"
#include "helper_functions.h"
#include "bisection.h"

// As requested, the commenting is done very liberally on this assignment.


// This is the function "x^3 - x^2 + 2" defined in the hw4_function.c file.
extern param_func_s hw4_function;


// When compiling, I have option to either run test code, or to compile the main
// function to be submitted for this question (q1) of the assignment.
#ifndef TEST

// Solution for question 1
int main(int argc, char **argv)
{
  interval_s interval_q1={-200.0, 300.0};
  float precision=1.0E-2;

  // Call bisection function. The ".node" member is a struct containing
  // the function itself, derivatives, and its inverse. For bisection,
  // only the function is used.
  iter_result result=bisect(hw4_function.node, interval_q1, precision, 0.0);

  // NaN is returned if the intermediate value theorem does not apply because
  // f(start) and f(end) are the same sign. In C lang, NaN!=NaN (For gnu runtime at least)
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
