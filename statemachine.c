#include "statemachine.h"
#include <stdlib.h>
#include <stdio.h>

///////////////////////////////
//////////STATEMACHINE/////////
///////////////////////////////


static Mystate state = IDLE;
static int current_dir = DIRN_STOP; 
static int next_dir;
static int current_floor;

void lights_off(void)
{
	
	elev_set_button_lamp(BUTTON_CALL_UP, 0, 0);
	elev_set_button_lamp(BUTTON_COMMAND, 0, 0);
	elev_set_button_lamp(BUTTON_COMMAND, 1, 0);
	elev_set_button_lamp(BUTTON_CALL_UP, 1, 0);
	elev_set_button_lamp(BUTTON_CALL_DOWN, 1, 0);
	elev_set_button_lamp(BUTTON_COMMAND, 2, 0);
	elev_set_button_lamp(BUTTON_CALL_UP, 2, 0);
	elev_set_button_lamp(BUTTON_CALL_DOWN, 2, 0);
	elev_set_button_lamp(BUTTON_CALL_DOWN, 3, 0);
	elev_set_button_lamp(BUTTON_COMMAND, 3, 0);
}

/*
void update_lights(void)
{
	if (current_floor == 0)
	{
		elev_set_button_lamp(BUTTON_CALL_UP, current_floor, 0);
		elev_set_button_lamp(BUTTON_COMMAND, current_floor, 0);
	}
	else if (current_floor == 3)
	{
		elev_set_button_lamp(BUTTON_CALL_DOWN, current_floor, 0);
		elev_set_button_lamp(BUTTON_COMMAND, current_floor, 0);
	}
	else if (current_floor > 0 && current_floor < 3)
	{
		elev_set_button_lamp(BUTTON_CALL_UP, current_floor, 0);
		elev_set_button_lamp(BUTTON_CALL_DOWN, current_floor, 0);
		elev_set_button_lamp(BUTTON_COMMAND, current_floor, 0);
	}
}
*/

bool should_stop_in_state(void)
{
	/*
	if(elev_get_floor_sensor_signal() != -1)
	{
		update_current_floor;
		return should_stop(current_floor, current_dir);
	}
	return false;
	*/
	return should_stop(current_floor, current_dir);

}

void update_current_floor(void)
{
	if (elev_get_floor_sensor_signal() != -1)
   	{
        	current_floor = elev_get_floor_sensor_signal();
    	}
	//printf("current floor: %d", current_floor);
}




//Statemachine

void orders_in_queue(void)
{
	switch(state)
	{
		case (IDLE):
		//start motor & set direction
		next_dir = get_next_dir(current_dir, current_floor);
		current_dir = next_dir;
		elev_set_motor_direction(current_dir); 		
		state = MOVING;
		printf("1");
			break;

		case (MOVING):
		printf("2");		
			break;
		
		case (DOOR_OPEN):
		printf("3");
			break;
		

		case (EM_STOP):				
		printf("4");
		default:
			break;
	}
}

void arrive_floor_with_order(void)
{
	switch(state)
	{
		case (IDLE):
		//delete order
		delete_order(current_floor);

		//door open - sett på timer - kjør timerfunksjon
		elev_set_door_open_lamp(1);
		set_timer();
		state = DOOR_OPEN;
		printf("5");
			break;

		case (MOVING):
		//stop motor
		current_dir = 0;
		elev_set_motor_direction(current_dir);
		//delete order
		delete_order(current_floor);

		//door open - sett på timer - kjør timerfunksjon
		elev_set_door_open_lamp(1);
		set_timer();
		state = DOOR_OPEN;
		printf("6");
			break;

		case (DOOR_OPEN):
		//delete order
		delete_order(current_floor);

		//door open - sett på timer
		elev_set_door_open_lamp(1);
		set_timer();
		state = DOOR_OPEN;	
		printf("7");
			break;

		case (EM_STOP):				
		printf("8");
		default:
			break;
	}
}



void emergency_stop_pushed(void)
{
	switch(state)
	{
		case (IDLE):
		//door open
		elev_set_door_open_lamp(1);
		//queue delete
		clear_queue();
		//update lights
		lights_off();
		//stop light
		elev_set_stop_lamp(1);
		state = EM_STOP;
			break;

		case (MOVING):
		//stop motor
		elev_set_motor_direction(DIRN_STOP);
		//queue delete
		clear_queue();	
		//update lights
		lights_off();
		//stop light
		elev_set_stop_lamp(1);
		state = EM_STOP;
			break;
		case (DOOR_OPEN):
		//queue delete
		clear_queue();	
		//update lights
		lights_off();
		//stop light
		elev_set_stop_lamp(1);
		state = EM_STOP;	
			break;
		case (EM_STOP):				
		default:
			break;
	}
}

void emergency_stop_released(void)
{
	switch(state)
	{
		case (IDLE):
			break;

		case (MOVING):
			break;

		case (DOOR_OPEN):	
			break;

		case (EM_STOP):
		//if floor_sensor: 				
			//state = DOOR_OPEN
		//else:
			//state: IDLE
		elev_set_stop_lamp(0);
		if(elev_get_floor_sensor_signal() != -1)
		{
			elev_set_door_open_lamp(1);
			//kjør timer
			set_timer();
			state = DOOR_OPEN;
		}
		else
		{
			state = IDLE;
		}
			
		default:
			break;
	}
}


void time_out(void)
{
	switch(state)
	{
		case (IDLE):
		//door closed
		elev_set_door_open_lamp(0);
		state = IDLE;
		printf("9");
			break;
		case (MOVING):
		printf("10");
			break;
		case (DOOR_OPEN):
		//door close
		elev_set_door_open_lamp(0);	
		state = IDLE;
		printf("11");
			break;
		case (EM_STOP):
		//door close
		elev_set_door_open_lamp(0);
		state = IDLE;
		printf("12");
		default:
			break;
	}
}



Mystate printState(void)
{
	return state;
}


