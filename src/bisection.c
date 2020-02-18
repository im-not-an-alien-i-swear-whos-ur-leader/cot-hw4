#include "bisection.h"
#include <stdlib.h>

iter_result bisect(param_func_node *function_node, interval_s interval, float precision)
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


  float f_start;
  
  float p=calculate_mid(start, end);// initialize p with p0
  float f_p;
  float interval_len=end-start;
  

  // Run until the max possible error is not greater than our specified error.
  // I choose to keep dividing the starting length by 2 instead of the condition
  // (end-start)>=precision because if end and start are very large compared to
  // the precision, there will be a significant error due to the machine epsilon
  // when subtracting. I.e. a small difference between large numbers is a bad idea.
  while(interval_len>=precision)
  {
    // Calculate the start and mid values.
    f_p=function(p, NULL);
    f_start=function(start, NULL);

    // See if start and p bracked a solution
    if(is_bracket(f_p, f_start))
    {
      // start and p bracket a solution. New interval is [start, p]
      // There may also be a root in (p, end) if f(mid)*f(end)<0, but
      // I can choose only one root to calculate at a given time.
      end=p;
    }
    else
    {
      // If start and p have the same sign, a root is only guaranteed in the
      // interval (p, end) because of intermediate value theorem.
      start=p;
    }

    // Recalculate the new midpoint from the new interval
    p=calculate_mid(start, end);

    // count another iteration.
    result.num_iterations++;

    // Update the length of the interval.
    interval_len/=2.0;
  }

  // This is a way of telling what the bounds for the answer are.
  result.interval.start=start;
  result.interval.end=end;
  
  // Use our current midpoint as the answer of x where f(x)=0. x is the root.
  result.root=p;
  return(result);
}

