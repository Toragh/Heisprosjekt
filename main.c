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
    while(elev_get_floor_sensor_signal() == -1)
    {
        elev_set_motor_direction(DIRN_UP);
    }
	elev_set_motor_direction(DIRN_STOP);
	
    

    while (1)
    {
	// Prints state to keep track of the code.
	printf("state: %d ",printState());

        // Keeps current_floor updated
        update_current_floor();	
        
        // Set indicator lights, shows in which floor the elevator cabin is or last was.
        if (elev_get_floor_sensor_signal()!= -1)
        {
            elev_set_floor_indicator(elev_get_floor_sensor_signal());
        }
	
	// Keeps queue updated				
        update_queue();
	print_queue();
	printf(" ");	

	

	// Event: Timer is done. Jumps to function time_out() in statemachine.c
	if(get_timer_function())
	{
		time_out();
	}
        
        
        // Event: Pending orders, buttons are pushed. Jumps to orders_in_queue() in statemachine.c
        if (check_orders())
        {	
		orders_in_queue();
        }

	
	//Event: Elevator arrives at floor with order. Jumps to arrive_floor_with_order() in statemachine.c
	if (should_stop_in_state())
	{
		arrive_floor_with_order(); 
	}
	
	
	
	// Event: Stop button is pressed or released. Jumps to eather emergency_stop_pushed() or emergency_stop_released() in statemachine.c
        if (elev_get_stop_signal())
        {
		while(elev_get_stop_signal() == 1)
			{
				emergency_stop_pushed();
			}
		emergency_stop_released();
        }

	if (elev_get_obstruction_signal())
	{
		break;
	}
	
	
    }

    return 0;

}

