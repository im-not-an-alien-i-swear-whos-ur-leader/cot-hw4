// This is a library for generic functions I've already written for other projects.
#include "generic_functions.h"

/*
  This file defines the function to be used in the homework assignment.
  Since Newtons method uses the derivative of a function I used my
  "generic_functions" library because it has a data structure that
  allows passing functions and their derivatives.
 */


//############################[function and derivative]#########################

// Function used in the homework assignment questions. "params" isn't used.
f_data_t hw4_func(f_data_t x, f_data_t *params)
{
  // x^3 - x^2 + 2
  // can be rewritten as: (x-1)*x*x+2
  return((x-1)*x*x+2);
}

// Derivative of the homework function. "params" isn't used.
f_data_t d_dx_hw4_func(f_data_t x, f_data_t * params)
{

  // 3*x^2 - 2*x
  // can be rewritten as: (3*x-2)*x
  
  return((3*x-2)*x);
}

//############################[helper data structures]##########################

// Helper struct containing the derivative
param_func_node hw4_d_dx_node=
{
  d_dx_hw4_func,
  NULL, // Inverse. Not used
  NULL // Derivative of this derivative. Not used.
};

// Helper struct containing the function.
param_func_node hw4_func_node=
{
  hw4_func, // Actual function itself.
  NULL,
  hw4_d_dx_node // Derivative function node.
};

// This is just a container struct containing information about
// the number of parameters, and the name of the function. It's not really used.
param_func_s hw4_function=
{
  "hw4_function",
  0, // No parameters used.
  hw4_func_node
};
