#include "elev.h"
#include "queue.h"
#include "statemachine.h"
#include <stdio.h>
#include <stdbool.h>

#define N_BUTTONS 3
/*
HUSK Å DEFINERE DENNE ETTERPÅ!!
int current_floor;
int current_dir;
*/

int main()
{
    int current_floor;
    
    // Initialize hardware
    if (!elev_init())
    {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");
    
    
    // Initialize engine
    elev_set_motor_direction(DIRN_UP);
    if (elev_get_floor_sensor_signal() != -1)
    {
        elev_set_motor_direction(DIRN_STOP);
        current_floor = elev_get_floor_sensor_signal();
    }
    

    while (1)
    {
        // keep current_floor updated
        current_floor = elev_get_floor_sensor_signal();
        
        // Set indicator lights
        if (elev_get_floor_sensor_signal()!= -1)
        {
            elev_set_floor_indicator(elev_get_floor_sensor_signal());
        }
        
        // Update queue
        update_queue();
        
        // If there are pending orders run orders in queue
        if (check_orders())
        {
            orders_in_queue();
        }

       

        // Change direction when we reach top/bottom floor
        //if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
          //  elev_set_motor_direction(DIRN_DOWN);
        //} else if (elev_get_floor_sensor_signal() == 0) {
           // elev_set_motor_direction(DIRN_UP);
        //}

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal())
        {
	
            elev_set_motor_direction(DIRN_STOP);
		
            break;
        }
    }

    return 0;
}
