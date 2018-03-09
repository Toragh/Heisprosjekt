#include "elev.h"
#include "queue.h"
#include "statemachine.h"
#include <stdio.h>
#include <stdbool.h>

///////////////////////////////
/////MAIN (EVENT HANDLER)//////
///////////////////////////////

int main()
{
    // Initialize hardware
    if (!elev_init())
    {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    // Initialize direction for engine
    while (elev_get_floor_sensor_signal() == -1)
    {
        elev_set_motor_direction(DIRN_UP);
    }
    elev_set_motor_direction(DIRN_STOP);

    while (1)
    {
        // Keeps current_floor updated
        state_update_current_floor();

        // Set indicator lights, shows in which floor the elevator cabin is or last was.
        if (elev_get_floor_sensor_signal() != -1)
        {
            elev_set_floor_indicator(elev_get_floor_sensor_signal());
        }

        // Keeps queue updated
        queue_update_queue_with_orders();
        queue_print();

        // Event: Timer is done. Jumps to function state_timer_done() in statemachine.c
        if (get_timer_function())
        {
            state_timer_done();
        }

        // Event: Pending orders, buttons are pushed. Jumps to orders_in_queue() in statemachine.c
        if (queue_check_if_orders_exists())
        {
            state_orders_in_queue();
        }

        //Event: Elevator arrives at floor with order. Jumps to arrive_floor_with_order() in statemachine.c
        if (state_should_stop())
        {
            state_arrive_floor_with_order();
        }

        // Event: Emergency stop button is pressed or released. Jumps to eather state_emergency_stop_pushed() or state_emergency_stop_released() in statemachine.c
        if (elev_get_stop_signal())
        {
            while (elev_get_stop_signal() == 1)
            {
                state_emergency_stop_pushed();
            }
            state_emergency_stop_released();
        }

        if (elev_get_obstruction_signal())
        {
            break;
        }
    }

    return 0;
}
