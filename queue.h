#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void clear_queue(void);
void delete_order(int current_floor);
bool order_below(int current_floor);
bool order_above(int current_floor);
int get_next_dir(int current_dir, int current_floor);
bool check_orders(void); 
void update_queue(void);
bool should_stop(int current_floor, int current_dir);
void print_queue(void);


#endif

