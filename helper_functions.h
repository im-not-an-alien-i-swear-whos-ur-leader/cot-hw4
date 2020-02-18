#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include "generic_functions.h"


// This struct is used to define the interval used in the iterative method.
typedef struct interval
{
  float start;
  float end;
} interval_s;

// This is the result of any of the iterative methods.
typedef struct iterative_method_result
{
  f_data_t root;
  // num_iterations is negative for failure where the absolute value is how many were performed.
  int num_iterations;
  interval_s interval;
} iter_result;


typedef struct coordinate_linked_list coord_l_list;


typedef struct coordinate
{
  float x;
  float y;
} coord_s;

struct coordinate_linked_list
{
  coord_s coord;
  coord_l_list *next;
};


coord_l_list *create_coord_list_node(float x, float y, coord_l_list *next);
void destroy_coord_list_node(coord_l_list *node);
void destroy_coord_list(coord_l_list *head);



int is_bracket(f_data_t f_start, f_data_t f_end);
interval_s sort_endpoints(interval_s interval);
int same_sign(float a, float b);
float calculate_mid(float start, float end);
f_data_t calculate_intercept(coord_s a, coord_s b);

#endif
