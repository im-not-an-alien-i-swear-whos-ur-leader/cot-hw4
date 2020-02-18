#include "newton.h"
#include <stdlib.h>
#include <math.h>


iter_result newton(param_func_node *function_node, interval_s interval, float precision, f_data_t f_x)
{
  iter_result result;
  result.num_iterations=0;

  float start=interval.start;
  float end=interval.end;
  

  parametric_function function=function_node->function;

  // Make sure the endpoints are in order.
  interval=sort_endpoints(interval);

  // Calculate the function at both endpoints
  float f_a=function(start, NULL);
  float f_b=function(end, NULL);

  // Check if we already have the answer at one of the interval endpoints.
  // If f(a) is 0 or a and a+precision bracket a root, a is a solution
  if(is_bracket(f_a-f_x, function(start+precision, NULL)-f_x))
  {
    result.root=start;
    return(result);
  }

  // Same as above, but use f(b) and f(b-precision)
  if(is_bracket(f_b-f_x, function(end-precision, NULL)-f_x))
  {
    result.root=end;
    return(result);
  }


  param_func_node *derivative=function_node->derivative;
  
  f_data_t a=interval.start;
  f_data_t b=interval.end;

  f_a=function(a, NULL);
  f_b=function(b, NULL);

  int i;

  //##################################################################
  // For this section I look at the endpoints, midpoint, 0, intercept
  // of the line joining the endpoints, and zeros of the derivative.
  // They are put into a list to be selected from later.
  
  coord_l_list *head=create_coord_list_node(a, f_a, NULL);
  head=create_coord_list_node(b, f_b, head);
  
  f_data_t midpoint=calculate_mid(a, b);

  head=create_coord_list_node(midpoint, function(midpoint, NULL), head);

  if(! same_sign(f_a, f_b))
  {
    coord_s first={a, f_a};
    coord_s last={b, f_b};
    f_data_t intercept=calculate_intercept(first, last);
    head=create_coord_list_node(intercept, function(intercept, NULL), head);
  }

  if(a<=0.0 && b>=0.0)
  {
    head=create_coord_list_node(0.0, function(0.0, NULL), head);
  }

  multival_data_t *derivative_zeros=NULL;
  
  if(derivative!=NULL)
  {
    if(derivative->inverse !=NULL)
    {
      derivative_zeros=derivative->inverse(0.0, NULL);

      for(i=0; i<derivative_zeros->num_vals; i++)
      {
	f_data_t x=derivative_zeros->vals[i];
	f_data_t y=function(x, NULL);
	head=create_coord_list_node(x, y, head);
      }
    }
  }

  //##################################################################

  // Here I look for the closest y value of any of the points so far.
  coord_l_list *current=head;
  coord_s smallest=current->coord;
  
  while(current->next!=NULL)
  {
    current=current->next;
    if(derivative->function(current->coord.x, NULL)>1.0E-3)
    {
      smallest=current->coord;
    }
  }

  current=head;
  
  while(current->next!=NULL)
  {
    current=current->next;
    if(fabs(current->coord.y-f_x)<fabs(smallest.y-f_x))
    {
      if(derivative->function(current->coord.x, NULL)>1.0E-3)
      {
	smallest=current->coord;
      }
    }
  }

  f_data_t p=smallest.x;
  
  destroy_coord_list(head);

  if(derivative->function(p, NULL)==0)
  {
    result.root=0.0/0.0;
    return(result);
  }

  int max_iter=5000;
  
  while(result.num_iterations<max_iter && fabs(function(p, NULL)-f_x)>precision)
  {
    p=p- (function(p, NULL)-f_x)/derivative->function(p, NULL);

    if(fabs(p)>1.0E+12)
    {
      result.num_iterations*=-1;
      return(result);
    }
  }
  
  result.root=p;

  return(result);
  
}

