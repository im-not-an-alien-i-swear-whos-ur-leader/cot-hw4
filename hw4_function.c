// This is a library for generic functions I've already written for other projects.
#include "generic_functions.h"
#include <stdlib.h>
#include <math.h>

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
f_data_t d_dx_hw4_func(f_data_t x, f_data_t *params)
{

  // 3*x^2 - 2*x
  // can be rewritten as: (3*x-2)*x
  
  return((3.0*x-2.0)*x);
}

multival_data_t *d_dx_inv_hw4_func(f_data_t y, f_data_t *params)
{
  multival_data_t *result=malloc(sizeof(multival_data_t));
  result->vals=malloc(2*sizeof(f_data_t));
  
  // (2+- sqrt(2* + 4*3*y) )/ (2*3)

  f_data_t radical=sqrt(4.0 + 12.0*y);

  result->vals[0]=0;
  result->vals[1]=(2.0+radical)/6.0;
  result->num_vals=2;
  
  return(result);
}

f_data_t d2_dx2_hw4_func(f_data_t x, f_data_t *params)
{
  return(6.0*x-2.0);
}

multival_data_t *d2_dx2_inv_hw4_func(f_data_t y, f_data_t *params)
{
  multival_data_t *result=malloc(sizeof(multival_data_t));
  result->vals=malloc(sizeof(f_data_t));

  result->vals[0]=((y+2.0)/6.0);
  result->num_vals=1;

  return(result);
}

//############################[helper data structures]##########################

param_func_node hw4_d2_dx2_node=
{
  &d2_dx2_hw4_func,
  &d2_dx2_inv_hw4_func,
  NULL
};

// Helper struct containing the derivative
param_func_node hw4_d_dx_node=
{
  &d_dx_hw4_func,
  &d_dx_inv_hw4_func,
  &hw4_d2_dx2_node // Derivative of this derivative. Not used.
};

// Helper struct containing the function.
param_func_node hw4_func_node=
{
  hw4_func, // Actual function itself.
  NULL,
  &hw4_d_dx_node // Derivative function node.
};

// This is just a container struct containing information about
// the number of parameters, and the name of the function. It's not really used.
param_func_s hw4_function=
{
  "hw4_function",
  0, // No parameters used.
  &hw4_func_node
};
