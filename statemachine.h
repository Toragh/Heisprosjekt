#ifndef __INCLUDE_STATE_H__
#define __INCLUDE_STATE_H__
#include "elev.h"
#include "io.h"
#include "timer.h"
#include "queue.h"
#include "channels.h"

///////////////////////////////
//////////STATEMACHINE/////////
///////////////////////////////


// The elevator can be in 4 different states
typedef enum state
{
	IDLE,
	MOVING,
	DOOR_OPEN,
	EM_STOP,
}Mystate;



bool state_should_stop(void);
void state_turn_all_lights_off(void);
//void update_lights(void);
void update_current_floor(void);
void orders_in_queue(void);
void arrive_floor_with_order(void);
void emergency_stop_pushed(void);
void emergency_stop_released(void);
void time_out(void);
Mystate printState(void);

#endif // #ifndef __INCLUDE_STATE_H__
