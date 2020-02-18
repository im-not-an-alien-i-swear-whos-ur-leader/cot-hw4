#include "fixed_iteration.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

fixed_pt_param get_fixed_pt_param(param_func_node *function_node, interval_s interval, f_data_t f_x)
{
  // function_node contains function and derivatives, etc.
  // interval is the current interval to search.
  // f_x is the value we want for f(x). Fixed point will solve for x such that f(x)=f_x
  
  // This function attempts to figure out scaling and shifting of the function used in the
  // recurrence relation "p_{n}=p_{n-1}-q*g(x-r)" and figure out a good initial value p_{0}
  // In the case where the intermediate value theorem does not apply, this function can
  // really only give a best guess for p_{0}. In other scenarios, if the derivative, its
  // inverse, and maybe even the second derivative are known, this function will adjust
  // scaling and shifting such that g(x) is in [a, b] when x is in [a, b]
  // and also scaling will be applied to keep abs(g'(x)) < 1 when x is in [a, b].

  parametric_function function=function_node->function;
  param_func_node *derivative=function_node->derivative;
  
  f_data_t a=interval.start;
  f_data_t b=interval.end;

  f_data_t f_a=function(a, NULL);
  f_data_t f_b=function(b, NULL);

  fixed_pt_param result;
  
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
    if(fabs(current->coord.y-f_x)<fabs(smallest.y-f_x))
    {
      smallest=current->coord;
    }
  }

  // Next, the smallest point having the opposite sign of the closest y value is selected.
  current=head;
  coord_s other=head->coord;
  if(other.x==smallest.x)
  {
    current=current->next;
    other=current->coord;
  }
  
  while(current!=NULL)
  {
    if(! same_sign(fabs(smallest.y-f_x), fabs(current->coord.y-f_x)))
    {
      if(fabs(current->coord.y-f_x)<fabs(other.y-f_x))
      {
	other=current->coord;
      }
    }
    current=current->next;
  }

  // Check to see if we have points f(x) on different sides of the val f_x
  if( same_sign(smallest.y-f_x, other.y-f_x))
  {
    // OPPOSING SIGN NOT FOUND!
    result.p_0=smallest.x;
    result.q=1.0;
    result.r=0.0;
    result.interval.start=smallest.x;
    result.interval.end=smallest.x;

    destroy_coord_list(head);

    destroy_multival_data(derivative_zeros);
    
    // This is kind of a worst case scenario where the intermediate value theorem
    // does not apply. There are no known points with opposite signs that can be used.
    // In this case, use the closest point so far and hope for the best.
    return(result);
  }

  interval.start=smallest.x;
  interval.end=other.x;
  interval=sort_endpoints(interval);

  a=interval.start;
  b=interval.end;
  f_a=function(a, NULL);
  f_b=function(b, NULL);

  f_data_t x;
  f_data_t y;
  f_data_t dy_dx;

  // Find the min and max on the endpoints
  // BTW, MAX() and MIN are not always well defined in C lang

  coord_s tempa={a, f_a};
  coord_s tempb={b, f_b};
  coord_s max=(f_a>f_b)?tempa:tempb;
  coord_s min=(f_a<f_b)?tempa:tempb;


  
  if(derivative_zeros!=NULL)
  {
    // Iterate through all the zeros in the derivative (if they are known) and find
    // the max and min values of the function in the interval we've selected.
    // If derivative not found, .num_vals will be 0.
    for(i=0; i<derivative_zeros->num_vals; i++)
    {
      x=derivative_zeros->vals[i];
      y=function(x, NULL);

      // If the derivative is within our interval:
      if((x>a)&&(x<b))
      {
	if(y>max.y)
	{
	  max.x=x;
	  max.y=y;
	}

	if(y<min.y)
	{
	  min.x=x;
	  min.y=y;
	}
      }
    }

  }

  f_data_t scaling=((interval.end-interval.start)/(max.y-min.y));
  f_data_t shift;
  
  f_data_t d_a=derivative->function(a, NULL);
  f_data_t d_b=derivative->function(b, NULL);


  if(derivative!=NULL && derivative->derivative!=NULL)
  {


    f_data_t max_d=(d_a>d_b)?d_a:d_b;
    f_data_t min_d=(d_a<d_b)?d_a:d_b;
    
    param_func_node *second_derivative=derivative->derivative;
  
    if(second_derivative->inverse!=NULL)
    {
      multival_data_t *d_derivative_zeros=second_derivative->inverse(0, NULL);

      for(i=0; i<d_derivative_zeros->num_vals; i++)
      {
	x=d_derivative_zeros->vals[i];
	y=derivative->function(x, NULL);
	if((x>a) && (x<b))
	{
	  if(y>max_d)
	  {
	    max_d=y;
	  }
	  if(y<min_d)
	  {
	    min_d=y;
	  }
	}

	destroy_multival_data(d_derivative_zeros);
	
      }// end loop


      // See if we need to adjust scaling to keep derivative between +-1;
      if(fabs(max_d)>1)
      {
	scaling=(fabs(max_d)>1.0/scaling)?1.0/fabs(max_d):scaling;
      }

      if(fabs(min_d)>1)
      {
      	scaling=(fabs(min_d)>1.0/scaling)?1.0/fabs(min_d):scaling;
      }
      
    }//end if
  }// end if(derivative!=NULL)

  shift=a-f_a*scaling;

  result.interval=interval;
  result.q=scaling;
  result.r=shift;
  result.p_0=calculate_mid(a, b);

  if(fabs(f_a-f_x)<fabs(function(result.p_0, NULL)-f_x))
  {
    result.p_0=a;
  }
  if(fabs(f_b-f_x)<fabs(function(result.p_0, NULL)-f_x))
  {
    result.p_0=b;
  }

  destroy_multival_data(derivative_zeros);
  
  return(result);
}


iter_result fixed_pt(param_func_node *function_node, interval_s interval, float precision, f_data_t f_x, fixed_pt_param parameters)
{
  iter_result result;
  result.num_iterations=0;

  float start=interval.start;
  float end=interval.end;

  result.interval=interval;
  
  parametric_function function=function_node->function;

  // Make sure the endpoints are in order.
  interval=sort_endpoints(interval);

  // Calculate the function at both endpoints
  float f_a=function(start, NULL);
  float f_b=function(end, NULL);

  // Check if we already have the answer at one of the interval endpoints.
  // If f(a) is 0 or a and a+precision bracket a root, a is a solution
  if(is_bracket(f_a, function(start+precision, NULL)))
  {
    result.root=start;
    return(result);
  }

  // Same as above, but use f(b) and f(b-precision)
  if(is_bracket(f_b, function(end-precision, NULL)))
  {
    result.root=end;
    return(result);
  }
  
  // If the endpoints have the same sign, intermediate value theorem doesn't apply.
  // This also covers the case where a==b since they must have the same sign.
  if(! is_bracket(f_a, f_b))
  {
    // Return NaN for the root and 0 iterations. NaN implies there is no number
    // where a root occurs.
    result.root=0.0/0.0;
    return(result);
  }

  f_data_t q=parameters.q;
  f_data_t r=parameters.r;

  // p_{n}=p_{n-1}-q*(f(p_{n-1}+r)-f_y)

  f_data_t p=parameters.p_0;//calculate_mid(start, end);

  int max_iter=50;
  
  while(result.num_iterations<max_iter)
  {
    printf("P: %f\n", p);
    
    p=p-q*(function(p+r, NULL)-f_x);

    // If abs(p) > 1.0*10^12 assume overflow and just give up...
    if(((p<0.0?-p:p)>1.0E+12))
    {
      result.num_iterations*=-1;
      return(result);
    }
    result.num_iterations++;
    
  }
  
  result.root=(p+r);

  return(result);
  
}

