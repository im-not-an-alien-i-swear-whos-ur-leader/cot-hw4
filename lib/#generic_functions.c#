#include "generic_functions.h"
#include <string.h>
#include <stdlib.h>


param_func_s unknown_param_function=
{
  "unknown",
  0,
  NULL
};


multi_func_s unknown_multi_function=
{
  "unknown",
  NULL
};


param_func_s *get_param_function_entry(char *name, param_func_list functions)
{
  int i;


  for(i=0; i<functions.num_entries; i++)
  {
    if(strcmp(name, functions.entries[i]->name)==0)
    {
      return(functions.entries[i]);
    }
  }

  return(&unknown_param_function);
}


multi_func_s *get_multi_function_entry(char *name, multi_func_list functions)
{
  int i;


  for(i=0; i<functions.num_entries; i++)
  {
    if(strcmp(name, functions.entries[i]->name)==0)
    {
      return(functions.entries[i]);
    }
  }

  return(&unknown_multi_function);
}