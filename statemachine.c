#include "statemachine.h"
#include "io.h"
#include "timer.h"
#include "queue.h"

#include <stdlib.h>

static Mystate state = IDLE; 
static int current_dir = DIRN_STOP; 
static int next_dir;


void orders_in_queue(){
	switch(state){
		case (IDLE):
		//start motor & set direction
		next_dir = get_next_dir(current_dir);	//RETNING BESTEMMES
		current_dir = next_dir;
		elev_set_motor_direction(current_dir); 		
		//state = MOVING
		state = MOVING;
			break;

		case (MOVING):s
		//state = MOVING
		state = MOVING;
			break;

		case (DOOR_OPEN):
		//state = DOOR_OPEN
		state = DOOR_OPEN;
			break;

		case (EM_STOP):				
		//state = EM_STOP
		state = EM_STOP;
		default:
			break;
	}
}

void arrive_floor_with_order(void){
	switch(state){
		case (IDLE):
		//delete order
		delete_item_in_queue(current_floor);
		//update lights
		elev_set_button_lamp(BUTTON_CALL_UP, current_floor, 0);
		elev_set_button_lamp(BUTTON_CALL_DOWN, current_floor, 0);
		elev_set_button_lamp(BUTTOn_COMMAND, current_floor, 0);
		//door open - sett på timer - kjør timerfunksjon
		elev_set_door_open_lamp(1);
		timer_function_3sec();
		//state = DOOR_OPEN
		state = DOOR_OPEN;
			break;

		case (MOVING):
		//stop motor
		elev_set_motor_direction(0);
		//delete order
		delete_item_in_queue(current_floor);
		//update lights
		elev_set_button_lamp(BUTTON_CALL_UP, current_floor, 0);
		elev_set_button_lamp(BUTTON_CALL_DOWN, current_floor, 0);
		elev_set_button_lamp(BUTTOn_COMMAND, current_floor, 0);
		//door open - sett på timer - kjør timerfunksjon
		elev_set_door_open_lamp(1);
		timer_function_3sec();
		//state = DOOR_OPEN
		state = DOOR_OPEN;
			break;

		case (DOOR_OPEN):
		//delete order
		delete_item_in_queue(current_floor);
		//update lights
		elev_set_button_lamp(BUTTON_CALL_UP, current_floor, 0);
		elev_set_button_lamp(BUTTON_CALL_DOWN, current_floor, 0);
		elev_set_button_lamp(BUTTOn_COMMAND, current_floor, 0);
		//door open - sett på timer
		elev_set_door_open_lamp(1);
		timer_function_3sec();
		//state = DOOR_OPEN
		state = DOOR_OPEN;	
			break;

		case (EM_STOP):				
		//state = EM_STOP
		state = EM_STOP;
		default:
			break;
	}
}



void emergency_stop(void){
	switch(state){
	case (IDLE):
	//door open
	elev_set_door_open_lamp(1);
	//queue delete
	clear_queue();
	//update lights
	elev_set_button_lamp(BUTTON_CALL_UP, current_floor, 0);
	elev_set_button_lamp(BUTTON_CALL_DOWN, current_floor, 0);
	elev_set_button_lamp(BUTTOn_COMMAND, current_floor, 0);
	//stop light
	elev_set_stop_lamp(1);
	//state = EM_STOP
	state = EM_STOP;
		break;

	case (MOVING):
	//stop motor
	elev_set_motor_direction(0);
	//queue delete
	clear_queue();	
	//update lights
	elev_set_button_lamp(BUTTON_CALL_UP, current_floor, 0);
	elev_set_button_lamp(BUTTON_CALL_DOWN, current_floor, 0);
	elev_set_button_lamp(BUTTOn_COMMAND, current_floor, 0);
	//stop light
	elev_set_stop_lamp(1);
	//state = EM_STOP
	state = EM_STOP;
		break;
	case (DOOR_OPEN):
	//queue delete
	clear_queue();	
	//update lights
	elev_set_button_lamp(BUTTON_CALL_UP, current_floor, 0);
	elev_set_button_lamp(BUTTON_CALL_DOWN, current_floor, 0);
	elev_set_button_lamp(BUTTOn_COMMAND, current_floor, 0);
	//stop light
	elev_set_stop_lamp(1);
	//state = EM_STOP
	state = EM_STOP;	
		break;
	case (EM_STOP):				
	//state = EM_STOP
	state = EM_STOP;
	default:
		break;
}
}

void emergency_stop_released(void){
	switch(state){
		case (IDLE):
		//state = IDLE
		state = IDLE;
			break;

		case (MOVING):
		//state = MOVING
		state = MOVING;
			break;

		case (DOOR_OPEN):

		//state = DOOR_OPEN
		state = DOOR_OPEN;	
			break;

		case (EM_STOP):
		//if floor_sensor: 				
			//state = DOOR_OPEN
		//else:
			//state: IDLE

		if(elev_get_floor_sensor_signal() != -1){
			elev_set_door_open_lamp(1);
			//kjør timer
			timer_function_3sec();
			state = DOOR_OPEN;
		}
		else{
			state = IDLE;
		}
			
		default:
			break;
	}
}


void time_out(void){
	switch(state){
		case (IDLE):
		//door closed
		elev_set_door_open_lamp(0);
		//state = IDLE
		state = IDLE:
			break;
		case (MOVING):
		//state = MOVING
		state = MOVING;
			break;
		case (DOOR_OPEN):
		//door close
		elev_set_door_open_lamp(0);
		//state = IDLE	
		state = IDLE;
			break;
		case (EM_STOP):
		//door close
		elev_set_door_open_lamp(0);
		//state = IDLE
		state = IDLE;
		default:
			break;
	}
}



