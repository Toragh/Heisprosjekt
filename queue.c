#include "queue.h"
#include "channels.h"
#include "elev.h"
#include "io.h"
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

///////////////////////////////
////////////QUEUE//////////////
///////////////////////////////

// Initialize queue matrix
static bool queue[N_FLOORS][N_BUTTONS]= {{0}};


// Clears queue, fills it with zeros
void queue_delete_all_orders(void)
{
    for (int floor = 0; floor < N_FLOORS;floor++)
    {
        for (int button = 0; button < N_BUTTONS; button++)
        {
            queue[floor][button] = 0;
        }
    }
    
}

// Delete all orders(all types of buttons pushed) at the current floor. 
// Turns off the lights at the current floor.
void queue_delete_order_at_floor(int current_floor)
{
    for (int button = 0; button < N_BUTTONS; button++)
    {
        queue[current_floor][button] = 0;
    }
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
	else if ((current_floor > 0) && (current_floor < 3))
	{
		elev_set_button_lamp(BUTTON_CALL_UP, current_floor, 0);
		elev_set_button_lamp(BUTTON_CALL_DOWN, current_floor, 0);
		elev_set_button_lamp(BUTTON_COMMAND, current_floor, 0);
	}
}

// Checks if there are orders below the current floor. Returns true if there is.
bool queue_order_below(int current_floor)
{
    for (int floor = 0; floor < current_floor; floor++)
    {
        for (int button = 0; button < N_BUTTONS; button++)
        {
            if(queue[floor][button]== 1)
            {
                return true;
            }
        }
    }
    return false;
}

// Checks if there are orders above the current floor. Returns true if there is.
bool queue_order_above(int current_floor)
{
    for (int floor = N_FLOORS; floor > current_floor; floor--)
    {
        for (int button = 0; button < N_BUTTONS; button++)
        {
            if(queue[floor][button]== 1)
            {
                return true;
            }
        }
    }
    return false;
}

// Decides the next directon by comparing current directon, current floor and buttons pushed.
int queue_get_next_dir(int current_dir, int current_floor)
{
    if (current_dir == DIRN_UP)
    {
        if (queue_order_above(current_floor))
        {
            return DIRN_UP;
        }
        else if (queue_order_below(current_floor + 1))
        {
            return DIRN_DOWN;
        }
        else
        {
            return DIRN_STOP;
        }
    }
    else if (current_dir == DIRN_DOWN)
    {
        if (queue_order_below(current_floor))
        {
            return DIRN_DOWN;
        }
        else if (queue_order_above(current_floor - 1))
        {
            return DIRN_UP;
        }
        else
        {
            return DIRN_STOP;
        }
        
    }
    else
    {
        if (queue_order_above(current_floor))
        {
            return DIRN_UP;
        }
        else if (queue_order_below(current_floor))
        {
            return DIRN_DOWN;
        }
        else
        {
            return DIRN_STOP;
        }
    }
}

// Checks if there are order(buttons pushed) at all in the queue.
bool queue_check_if_orders_exists(void)
{
    for (int floor = 0; floor < N_FLOORS; ++floor) 
    {
        for (int button = 0; button < N_BUTTONS; ++button)
        {
            if (queue[floor][button] == 1)
            {
                return true;
            }
        }
    }
    return false;
}

// Iterates through all different types of buttons and fills the queue when buttons are pushed.
void queue_update_queue_with_orders(void)
{
    for (int floor = 0; floor < N_FLOORS; floor++)
    {
		if(floor == 0)
		{	
			if(elev_get_button_signal(BUTTON_CALL_UP,floor))
			{
				queue[floor][BUTTON_CALL_UP]= 1;
				elev_set_button_lamp(BUTTON_CALL_UP, floor, 1);
			}
			if(elev_get_button_signal(BUTTON_COMMAND,floor))
			{
				queue[floor][BUTTON_COMMAND]= 1;
				elev_set_button_lamp(BUTTON_COMMAND, floor, 1);
			}
		
            		
		}
		else if (floor == 3)
		{
			if(elev_get_button_signal(BUTTON_CALL_DOWN,floor))
			{
				queue[floor][BUTTON_CALL_DOWN]= 1;
				elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 1);
			}
			if(elev_get_button_signal(2,floor))
			{
				queue[floor][BUTTON_COMMAND]= 1;
				elev_set_button_lamp(BUTTON_COMMAND, floor, 1);
			}
			
		}
		else
		{
			for (int button = 0; button < N_BUTTONS; ++button)
        		{
				if(elev_get_button_signal(button,floor))
				{
					queue[floor][button]= 1;
					elev_set_button_lamp(button, floor, 1);
				}
		
            		}
		}
        }
}

// Checks if the elevator should stop in the current floor by comparing current direction, current floor and the queue.
bool queue_should_stop(int current_floor, int current_dir)
{	
	if(current_dir == DIRN_UP)
	{
		if(queue[current_floor][BUTTON_CALL_UP] || queue[current_floor][BUTTON_COMMAND])
		{	
			return true;
		}	
	}
	else if(current_dir == DIRN_DOWN)
	{	
		if(queue[current_floor][BUTTON_CALL_DOWN] || queue[current_floor][BUTTON_COMMAND])
		{		
			return true;
		}
	}
	else if(current_dir == DIRN_STOP)
	{
		if(queue[current_floor][BUTTON_CALL_UP] || queue[current_floor][BUTTON_CALL_DOWN]|| queue[current_floor][BUTTON_COMMAND])
		{
			return true;
		}
	}
	if (current_dir == DIRN_DOWN && queue[current_floor][BUTTON_CALL_UP] && !queue_order_below(current_floor)) 
	{	
			return true;
	}
	else if (current_dir == DIRN_UP && queue[current_floor][BUTTON_CALL_DOWN] && !queue_order_above(current_floor)) 
	{
			return true;
	}
	return false;
	

}

// To track which buttons that are pushed. For debugging.
void queue_print(void)
{
	printf("\nqueue:");
	for(int i = 0; i < N_FLOORS; ++i)
	{
		printf("\n");	
		for (int j = 0; j < N_BUTTONS; ++j)
		{		
			printf(" %d", queue[i][j]);
		}
	}
	printf("\n");

}


