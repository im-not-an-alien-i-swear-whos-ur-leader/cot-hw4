#include "helper_functions.h"
#include <stdlib.h>

coord_l_list *create_coord_list_node(float x, float y, coord_l_list *next)
{
  coord_l_list *node=malloc(sizeof(coord_l_list));
  node->coord.x=x;
  node->coord.y=y;
  node->next=next;
  
  return(node);
}

void destroy_coord_list_node(coord_l_list *node)
{
  free(node);
}

void destroy_coord_list(coord_l_list *head)
{
  coord_l_list *current=head;
  coord_l_list *next;

  while(current!=NULL)
  {
    next=current->next;
    destroy_coord_list_node(current);
    current=next;
  }

  return;
}






int is_bracket(f_data_t f_start, f_data_t f_end)
{
  return(f_start==0.0 || ! same_sign(f_start, f_end));
}

interval_s sort_endpoints(interval_s interval)
{
  if(interval.start>interval.end)
  {
    // Swap the interval endpoints if they're out of order.
    float temp=interval.start;
    interval.start=interval.end;
    interval.end=temp;
  }

  return(interval);
}


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

f_data_t calculate_intercept(coord_s a, coord_s b)
{
  f_data_t height=a.y-b.y;
  f_data_t width=a.x-b.x;

  f_data_t result=-b.y/height*width+b.x;
}
