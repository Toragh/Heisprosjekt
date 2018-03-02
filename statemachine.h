#ifndef __INCLUDE_IO_H__
#define __INCLUDE_IO_H__

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

#endif // #ifndef __INCLUDE_IO_H__
