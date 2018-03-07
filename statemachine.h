#ifndef __INCLUDE_STATE_H__
#define __INCLUDE_STATE_H__
#include "elev.h"
#include "io.h"
#include "timer.h"
#include "queue.h"
#include "channels.h"

bool should_stop_IN_STATE(void);
void update_lights(void);

typedef enum state
{
	IDLE,
	MOVING,
	DOOR_OPEN,
	EM_STOP,
}Mystate;

void update_current_floor(void);
void orders_in_queue(void);
void arrive_floor_with_order(void);
void emergency_stop(void);
void emergency_stop_released(void);
void time_out(void);

#endif // #ifndef __INCLUDE_STATE_H__
