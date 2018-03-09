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

void state_turn_all_lights_off(void)
{
	for(int floor = 0; floor < N_FLOORS; floor++)
	{
		for(int button = BUTTON_CALL_UP; button <= BUTTON_COMMAND; button++)
		{
			if(!((floor == 0 && button == BUTTON_CALL_DOWN) || (floor == 3 && button ==BUTTON_CALL_UP)))
			{
				elev_set_button_lamp(button, floor, 0);
			}
		}
	}
}

bool state_should_stop(void)
{

	if (elev_get_floor_sensor_signal() != -1)
	{
		update_current_floor();
		return queue_should_stop(current_floor, current_dir);
	}
	return false;
}

void update_current_floor(void)
{
	if (elev_get_floor_sensor_signal() != -1)
	{
		current_floor = elev_get_floor_sensor_signal();
	}
}

//Statemachine
void orders_in_queue(void)
{
	switch (state)
	{
	case (IDLE):

		next_dir = queue_get_next_dir(current_dir, current_floor);
		if (elev_get_floor_sensor_signal() != -1)
		{
			current_dir = next_dir;
		}

		elev_set_motor_direction(next_dir);
		state = MOVING;
		break;
	}
}

void arrive_floor_with_order(void)
{
	queue_delete_order_at_floor(current_floor);
	elev_set_door_open_lamp(1);
	set_timer();

	switch (state)
	{
	case (IDLE):
		state = DOOR_OPEN;
		break;

	case (MOVING):
		elev_set_motor_direction(0);
		state = DOOR_OPEN;
		break;

	case (DOOR_OPEN):
		elev_set_motor_direction(0);
		state = DOOR_OPEN;
		break;
	}
}

void emergency_stop_pushed(void)
{
	queue_delete_all_orders();
	state_turn_all_lights_off();
	elev_set_stop_lamp(1);

	switch (state)
	{
	case (IDLE):
		elev_set_door_open_lamp(1);
		state = EM_STOP;
		break;

	case (MOVING):
		elev_set_motor_direction(DIRN_STOP);
		state = EM_STOP;
		break;
		
	case (DOOR_OPEN):
		state = EM_STOP;
		break;
	}
}

void emergency_stop_released(void)
{
	switch (state)
	{
	/*	
	case (IDLE):
		state = IDLE;
		break;

	case (MOVING):
		state = MOVING;
		break;

	case (DOOR_OPEN):
		state = DOOR_OPEN;
		break;
	*/
	case (EM_STOP):
		elev_set_stop_lamp(0);
		if (elev_get_floor_sensor_signal() != -1)
		{
			elev_set_door_open_lamp(1);
			set_timer();
			state = DOOR_OPEN;
		}
		else
		{
			state = IDLE;
		}
	}
}

void time_out(void)
{
	elev_set_door_open_lamp(0);
	state = IDLE;
	/*
	switch (state)
	{
	case (IDLE):
		state = IDLE;
		break;

	case (DOOR_OPEN):
		state = IDLE;
		break;

	case (EM_STOP):
		state = IDLE;
		break;
	}*/
}

Mystate printState(void)
{
	return state;
}
