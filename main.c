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

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
	

    printf("Press STOP button to stop elevator and exit program.\n");
    
    bool order_matrix[N_FLOORS][N_BUTTONS];
    initialize_matrix(order_matrix);
    

    elev_set_motor_direction(DIRN_UP);

    while (1) {

	// Initialize engine
	
	if (elev_get_floor_sensor_signal() != -1)
		{
		elev_set_motor_direction(DIRN_STOP);
		int current_floor = elev_get_floor_sensor_signal();
		}
    
    //Check if buttons pushed
        // i = floor
        // j = button type
        // er elev_get_button_signal langt nok til at 1ern registeres
        for (int i = 0; i < N_FLOORS; ++i)
        {
            for (int j = 0; j < N_BUTTONS; ++j)
            {
                if (elev_get_button_signal(j,i))
                {
                    order_matrix[i][j]= 1;
                }
            }
        }
        
        
        

	// Set indicator lights
	if (elev_get_floor_sensor_signal()!= -1)
		{
		elev_set_floor_indicator(elev_get_floor_sensor_signal());
		}

        // Change direction when we reach top/bottom floor
        //if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
          //  elev_set_motor_direction(DIRN_DOWN);
        //} else if (elev_get_floor_sensor_signal() == 0) {
           // elev_set_motor_direction(DIRN_UP);
        //}

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
	
            elev_set_motor_direction(DIRN_STOP);
		
            break;
        }
    }

    return 0;
}
