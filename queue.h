#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


///////////////////////////////
////////////QUEUE//////////////
///////////////////////////////


void queue_delete_all_orders(void);
void queue_delete_order_at_floor(int current_floor);
bool queue_order_below(int current_floor);
bool queue_order_above(int current_floor);
int queue_get_next_dir(int current_dir, int current_floor);
bool queue_check_if_orders_exists(void); 
void queue_update_queue_with_orders(void);
bool queue_should_stop(int current_floor, int current_dir);
void print_queue(void);


#endif

