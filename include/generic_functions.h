#ifndef GENERIC_FUNCTIONS_H
#define GENERIC_FUNCTIONS_H




typedef float f_data_t;


//####################################### parametric_function ##################################


typedef struct multivalued_result
{
  int num_vals;
  f_data_t *vals;
} multival_data_t;

typedef multival_data_t(*multivalued_function)(f_data_t var, f_data_t *params);


typedef f_data_t (*parametric_function)(f_data_t var, f_data_t *params);


typedef struct param_node param_func_node;

struct param_node
{
  parametric_function function;
  multivalued_function *inverse;
  param_func_node *derivative;
};


typedef struct parametric_function_struct
{
  char *name;
  int num_param;
  param_func_node *node;
} param_func_s;


typedef struct parameterized_function_entry_list
{
  int num_entries;
  param_func_s **entries;

} param_func_list;



//####################################### multivariable_function ###############################

typedef struct function_derivative
{
  int dn;
  int *wrt;
} f_derivative;

typedef f_data_t (*multivariable_function)(int num_inputs, f_data_t *input, f_derivative derivative);

typedef struct function_definition
{
  char *name;
  multivariable_function function;
  
} multi_func_s;


typedef struct multivariable_function_entry_list
{
  int num_entries;
  multi_func_s **entries;

} multi_func_list;



//######################################## stuff ###############################################

param_func_s *get_param_function_entry(char *name, param_func_list functions);
multi_func_s *get_multi_function_entry(char *name, multi_func_list functions);



#endif
