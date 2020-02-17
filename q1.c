// Homework 4 - Question 1
// COP4500 - Spring 2020

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "generic_functions.h"

// As requested, the commenting is done very liberally on this assignment.


// This struct is used to define the interval used in the bisection method.
typedef struct interval
{
  float start;
  float end;
} interval_s;

typedef struct bisection_result
{
  float root;
  // num_iterations is negative for failure where the absolute value is how many were performed.
  int num_iterations;
} bisect_res;

// Prototype for the bisection method. Pass a function to solve and interval for the root.
bisect_res bisect(param_func_node *function_node, interval_s interval, float precision);

// This is the function "x^3 - x^2 + 2" defined in the hw4_function.c file.
extern param_func_s hw4_function;


// When compiling, I have option to either run test code, or to compile the main
// function to be submitted for this question (q1) of the assignment.
#ifndef TEST

// Solution for question 1
int main(int argc, char **argv)
{
  interval_s interval_q1={-200.0, 300.0};
  float precision=1.0E-2;
  
  bisect_res result=bisect(hw4_function.node, interval_q1, precision);

  // NaN is returned if the intermediate value theorem does not apply because
  // f(start) and f(end) are the same sign. In C, NaN!=NaN
  if(result.num_iterations<0 || result.root!=result.root)
  {
    fprintf(stderr, "The method failed after %d iterations.\n", abs(result.num_iterations));
    exit(-1);
  }
  else
  {
    printf("The procedure was successful.\nThe value of root is: %f\n", result.root);
  }
  return(0);
}

#endif

int same_sign(float a, float b)
{
  // Check if two numbers have the same "sign"
  // This uses 3 different "signs" of 0, +, -
  // I.e. 0 has a different sign from both positive and negative numbers.
  
  if(a==0.0 || b==0.0)
    return(a==b);

  // != is xor in c
  return(!((a>0.0)!=(b>0.0)));
}

float calculate_mid(float start, float end)
{
  // Uses the midpoint formula for the middle of an interval.
  return((start+end)/2);
}

bisect_res bisect(param_func_node *function_node, interval_s interval, float precision)
{
  bisect_res result;
  result.num_iterations=0;

  parametric_function function=function_node->function;
  
  if(interval.start>interval.end)
  {
    // Swap the interval endpoints if they're out of order.
    float temp=interval.start;
    interval.start=interval.end;
    interval.end=temp;
  }

  // Calculate the function at both endpoints
  float f_start=function(interval.start, NULL);
  float f_end=function(interval.end, NULL);

  // Check if we already have the answer at one of the interval endpoints.
  // If we already have f(start)==0 or if f(a)*f(a+precision) < 0 return answer.
  if(f_start==0.0 || ! same_sign(f_start, function(interval.start+precision, NULL)))
  {
    result.root=interval.start;
    return(result);
  }

  // Same as above, but use f(end) and f(end-precision)
  if(f_end==0.0 || ! same_sign(f_end, function(interval.end-precision, NULL)))
  {
    result.root=interval.end;
    return(result);
  }
  
  // If the endpoints have the same sign, intermediate value theorem doesn't apply.
  // This also covers the case where start==end since they must have the same sign.
  if(same_sign(f_start, f_end))
  {
    // Return NaN for the root and 0 iterations. NaN implies there is no number
    // where a root occurs.
    result.root=0.0/0.0;
    return(result);
  }

  float start=interval.start;
  float end=interval.end;

  float mid=calculate_mid(start, end);
  float y;
  float interval_len=end-start;

  // Run until the max possible error is not greater than our specified error.
  // I choose to keep dividing the starting length by 2 instead of the condition
  // (end-start)>=precision because if end and start are very large compared to
  // the precision, there will be a significant error due to the machine epsilon
  // when subtracting. I.e. a small difference between large numbers is a bad idea.
  while(interval_len>=precision)
  {
    // Calculate the start and mid values.
    y=function(mid, NULL);
    f_start=function(start, NULL);

    // Compare sign of start and midpoint.
    if(same_sign(y, f_start))
    {
      // If start and mid have the same sign, a root is only guaranteed in the
      // interval (mid, end) because of intermediate value theorem.
      start=mid;
    }
    else
    {
      // If start and end have opposite signs, there is a guarantee that a
      // root exists in the interval (start, mid). There may also be a root
      // in (mid, end) if f(mid)*f(end)<0, but I can choose only one root
      // to calculate at a given time.
      end=mid;
    }

    // Recalculate the new midpoint from the new interval
    mid=calculate_mid(start, end);

    // count another iteration.
    result.num_iterations++;

    // Update the length of the interval.
    interval_len/=2.0;
  }

  // Use our current midpoint as the answer of x where f(x)=0. x is the root.
  result.root=mid;
  return(result);
}



//###############################################################################
// Run test code instead of the assignment submission
#ifdef TEST

#include "test_functions.h"

int main(int argc, char ** argv)
{
  
  return(0);
}


#endif
//###############################################################################
