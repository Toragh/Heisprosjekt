#include "statemachine.h"
#include "io.h"

#include <stdlib.h>

 Mystate state = IDLE; 

void orders_in_queue(void){
	switch(state){
		case (IDLE):
		//set direction
		//start motor
		//state = MOVING
			break;
		case (MOVING):
		//state = MOVING
			break;
		case (DOOR_OPEN):
		//state = DOOR_OPEN	
			break;
		case (EM_STOP):				
		//state = EM_STOP
		default:
			break;
	}
}

void arrive_floor_with_order(void){
	switch(state){
		case (IDLE):
		//delete order
		//update lights
		//door open - sett på timer
		//state = DOOR_OPEN
			break;
		case (MOVING):
		//stop motor
		//delete order
		//update lights
		//door open - sett på timer
		//state = DOOR_OPEN
			break;
		case (DOOR_OPEN):
		//delete order
		//update lights
		//door open - sett på timer
		//state = DOOR_OPEN	
			break;
		case (EM_STOP):				
		//state = EM_STOP
		default:
			break;
	}
}



void emergency_stop(void){
switch(state){
	case (IDLE):
	//door open
	//queue delete	
	//update lights
	//stop light
	//state = EM_STOP
		break;
	case (MOVING):
	//stop motor
	//queue delete	
	//update lights
	//stop light
	//state = EM_STOP
		break;
	case (DOOR_OPEN):
	//queue delete	
	//update lights
	//stop light
	//state = EM_STOP	
		break;
	case (EM_STOP):				
	//state = EM_STOP
	default:
		break;
}
}

void emergency_stop_released(void){
	switch(state){
		case (IDLE):
		
		//state = 
			break;
		case (MOVING):

		//state = 
			break;
		case (DOOR_OPEN):

		//state = 	
			break;
		case (EM_STOP):
		//if floor_sensor: 				
			//state = DOOR_OPEN
		//else:
			//state: IDLE
		default:
			break;
	}
}


void time_out(void){
	switch(state){
		case (IDLE):
		//door closed
		//state = IDLE
			break;
		case (MOVING):
		//state = MOVING
			break;
		case (DOOR_OPEN):
		//door close
		//state = IDLE	
			break;
		case (EM_STOP):
		//door close
		//state = IDLE
		default:
			break;
	}
}



