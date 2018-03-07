#include "elev.h"
#include "queue.h"
#include "statemachine.h"
#include <stdio.h>
#include <stdbool.h>

int main()
{   
    // Initialize hardware
    if (!elev_init())
    {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    //printf("Press STOP button to stop elevator and exit program.\n");
    
    
    // Initialize engine
    while(elev_get_floor_sensor_signal() == -1)
    {
        elev_set_motor_direction(DIRN_UP);
    }
	elev_set_motor_direction(DIRN_STOP);
    

    while (1)
    {
	if (elev_get_stop_signal())
	{
		break;
	}




        // keep current_floor updated
        update_current_floor();		//nok å kjøre denne en gang i løpet av while??
        
        // Set indicator lights
        if (elev_get_floor_sensor_signal()!= -1)
        {
            elev_set_floor_indicator(elev_get_floor_sensor_signal());
        }
        
        // Update queue					//nok å kjøre denne en gang i løpet av while??
        update_queue();
        
        // If there are pending orders run orders_in_queue
        if (check_orders())
        {
            orders_in_queue();
        }

        // Stop elevator if the stop button is pressed
        /*if (elev_get_stop_signal())
        {
		while(elev_get_stop_signal() == 1)
			{
				emergency_stop();
			}
		emergency_stop_released();
        }
	*/
	//arrive in floor with order
	if (should_stop_IN_STATE())
	{
		arrive_floor_with_order();
	}
	

	//timer
	if(get_timer_function())
	{
		time_out();
	}


	// Change direction when we reach top/bottom floor
        //if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
          //  elev_set_motor_direction(DIRN_DOWN);
        //} else if (elev_get_floor_sensor_signal() == 0) {
           // elev_set_motor_direction(DIRN_UP);
        //}
    }

    return 0;
}
