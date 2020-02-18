#ifndef FIXED_ITERATION_H
#define FIXED_ITERATION_H
#include "helper_functions.h"

typedef struct fixed_pt_parameters
{
  interval_s interval;
  float q;
  float r;
  float p_0;
} fixed_pt_param;



// Prototype for the fixed point method. Pass a function to solve and interval for the root.
iter_result fixed_pt(param_func_node *function_node, interval_s interval, float precision, f_data_t f_x, fixed_pt_param parameters);

// Get parameters to (hopefully) make the algorithm converge.
fixed_pt_param get_fixed_pt_param(param_func_node *function_node, interval_s interval, f_data_t f_x);

#endif
