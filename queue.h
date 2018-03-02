#ifndef __INCLUDE_DRIVER_H__
#define __INCLUDE_DRIVER_H__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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


void initialize_matrix(bool matrix[N_FLOORS][N_BUTTONS]);
void delete_item_in_matrix(bool matrix[N_FLOORS][N_BUTTONS], int current_floor);
//void check_matrix(bool matrix[N_FLOORS][N_BUTTONS]);
bool get_order_below(bool matrix[N_FLOORS][N_BUTTONS]);
bool get_order_above(bool matrix[N_FLOORS][N_BUTTONS]);
void get_next_dir(bool matrix[N_FLOORS][N_BUTTONS]);


void empty_matrix(bool matrix[N_FLOORS][N_BUTTONS]); // er ikke dette initialize?

#endif // #ifndef __INCLUDE_DRIVER_H__

