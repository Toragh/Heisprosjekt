#ifndef __INCLUDE_DRIVER_H__
#define __INCLUDE_DRIVER_H__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


/*
Trenger:
4x3 matrise til å holde styr på hvilke kapper som er trykket inn
empty for em_stop

Order matrix


 Motor direction for function elev_set_motor_direction().

typedef enum tag_elev_motor_direction {
    DIRN_DOWN = -1,
    DIRN_STOP = 0,
    DIRN_UP = 1
} elev_motor_direction_t;




 Sets the motor direction of the elevator.
 @param dirn New direction of the elevator.

void elev_set_motor_direction(elev_motor_direction_t dirn);




typedef struct Order {
    int floor;
    elev_button_type_t buttontype;
    //long int*    matrix;
} Order;

 */


void clear_queue(void);
void delete_item_in_queue(int current_floor);
bool get_order_below(int current_floor);
bool get_order_above(int current_floor);
void get_next_dir(int current_dir);
bool check_orders(void); // returns false if matrix is empty
void update_queue(void);
bool should_stop(int current_floor, int current_dir);


#endif // #ifndef __INCLUDE_DRIVER_H__

