#ifndef NEWTON_H
#define NEWTON_H
#include "helper_functions.h"

iter_result newton(param_func_node *function_node, interval_s interval, float precision, f_data_t f_x);

#endif
