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

bool should_stop_in_state(void)
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

	case (MOVING):
		state = MOVING;
		break;

	case (DOOR_OPEN):
		state = DOOR_OPEN;
		break;

	case (EM_STOP):
		state = EM_STOP;
	default:
		break;
	}
}

void arrive_floor_with_order(void)
{
	switch (state)
	{
	case (IDLE):
		queue_delete_order_at_floor(current_floor);
		elev_set_door_open_lamp(1);
		set_timer();
		state = DOOR_OPEN;
		break;

	case (MOVING):
		//stop motor
		//current_dir = 0;
		elev_set_motor_direction(0);
		queue_delete_order_at_floor(current_floor);
		elev_set_door_open_lamp(1);
		set_timer();
		state = DOOR_OPEN;
		break;

	case (DOOR_OPEN):
		elev_set_motor_direction(0);
		queue_delete_order_at_floor(current_floor);
		elev_set_door_open_lamp(1);
		set_timer();
		state = DOOR_OPEN;
		break;
	}
}

void emergency_stop_pushed(void)
{
	switch (state)
	{
	case (IDLE):
		elev_set_door_open_lamp(1);
		queue_delete_all_orders();
		lights_off();
		elev_set_stop_lamp(1);
		state = EM_STOP;
		break;

	case (MOVING):
		elev_set_motor_direction(DIRN_STOP);
		queue_delete_all_orders();
		lights_off();
		elev_set_stop_lamp(1);
		state = EM_STOP;
		break;
	case (DOOR_OPEN):
		queue_delete_all_orders();
		lights_off();
		elev_set_stop_lamp(1);
		state = EM_STOP;
		break;
	}
}

void emergency_stop_released(void)
{
	switch (state)
	{
	case (IDLE):
		state = IDLE;
		break;

	case (MOVING):
		state = MOVING;
		break;

	case (DOOR_OPEN):
		state = DOOR_OPEN;
		break;

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
	switch (state)
	{
	case (IDLE):
		elev_set_door_open_lamp(0);
		state = IDLE;
		break;
	case (MOVING):
		state = MOVING;
		break;
	case (DOOR_OPEN):
		elev_set_door_open_lamp(0);
		state = IDLE;
		break;
	case (EM_STOP):
		elev_set_door_open_lamp(0);
		state = IDLE;
	}
}

Mystate printState(void)
{
	return state;
}
