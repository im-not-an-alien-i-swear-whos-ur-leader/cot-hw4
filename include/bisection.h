#ifndef BISECTION_H
#define BISECTION_H
#include "helper_functions.h"

// Prototype for the bisection method. Pass a function to solve and interval for the root.
iter_result bisect(param_func_node *function_node, interval_s interval, float precision, f_data_t f_x);

#endif
