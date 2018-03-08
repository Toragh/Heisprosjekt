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
static bool queue[N_FLOORS][N_BUTTONS]= {0};


// Clears queue, fills it with zeros
void clear_queue(void)
{
    for (int i = 0; i < N_FLOORS;i++)
    {
        for (int j = 0; j < N_BUTTONS; j++)
        {
            queue[i][j] = 0;
        }
    }
    
}

// Delete all orders(all types of buttons pushed) at the current floor. 
// Turns off the lights at the current floor.
void delete_order(int current_floor)
{
    for (int i = 0; i <= N_BUTTONS; i++)
    {
        queue[current_floor][i] = 0;
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
	else if (current_floor > 0 && current_floor < 3)
	{
		elev_set_button_lamp(BUTTON_CALL_UP, current_floor, 0);
		elev_set_button_lamp(BUTTON_CALL_DOWN, current_floor, 0);
		elev_set_button_lamp(BUTTON_COMMAND, current_floor, 0);
	}
}

// Checks if there are orders below the current floor. Returns true if there is.
bool order_below(int current_floor)
{
    for (int i = 0; i < current_floor; i++)
    {
        for (int j = 0; j < N_BUTTONS; j++)
        {
            if(queue[i][j]== 1)
            {
                return true;
            }
        }
    }
    return false;
}

// Checks if there are orders above the current floor. Returns true if there is.
bool order_above(int current_floor)
{
    for (int i = N_FLOORS; i > current_floor; i--)
    {
        for (int j = 0; j < N_BUTTONS; j++)
        {
            if(queue[i][j]== 1)
            {
                return true;
            }
        }
    }
    return false;
}

// Decides the next directon by comparing current directon, current floor and buttons pushed.
int get_next_dir(int current_dir, int current_floor)
{
    if (current_dir == DIRN_UP)
    {
        if (order_above(current_floor))
        {
            return DIRN_UP;
        }
        else if (order_below(current_floor))
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
        if (order_below(current_floor))
        {
            return DIRN_DOWN;
        }
        else if (order_above(current_floor))
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
        if (order_above(current_floor))
        {
            return DIRN_UP;
        }
        else if (order_below(current_floor))
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
bool check_orders(void)
{
    for (int i = 0; i < N_FLOORS; ++i) 
    {
        for (int j = 0; j < N_BUTTONS; ++j)
        {
            if (queue[i][j] == 1)
            {
                return true;
            }
        }
    }
    return false;
}

// Iterates through all different types of buttons and fills the queue when buttons are pushed.
void update_queue(void)
{
    for (int i = 0; i < N_FLOORS; i++)
    {
		if(i == 0)
		{	
			if(elev_get_button_signal(BUTTON_CALL_UP,i))
			{
				queue[i][BUTTON_CALL_UP]= 1;
				elev_set_button_lamp(BUTTON_CALL_UP, i, 1);
			}
			if(elev_get_button_signal(BUTTON_COMMAND,i))
			{
				queue[i][BUTTON_COMMAND]= 1;
				elev_set_button_lamp(BUTTON_COMMAND, i, 1);
			}
		
            		
		}
		else if (i == 3)
		{
			if(elev_get_button_signal(BUTTON_CALL_DOWN,i))
			{
				queue[i][BUTTON_CALL_DOWN]= 1;
				elev_set_button_lamp(BUTTON_CALL_DOWN, i, 1);
			}
			if(elev_get_button_signal(2,i))
			{
				queue[i][BUTTON_COMMAND]= 1;
				elev_set_button_lamp(BUTTON_COMMAND, i, 1);
			}
			
		}
		else
		{
			for (int j = 0; j < N_BUTTONS; ++j)
        		{
				if(elev_get_button_signal(j,i))
				{
					queue[i][j]= 1;
					elev_set_button_lamp(j, i, 1);
				}
		
            		}
		}
        }
}

// Checks if the elevator should stop in the current floor by comparing current direction, current floor and the queue.
bool should_stop(int current_floor, int current_dir){	
	if(current_dir == DIRN_UP)
	{
		if(queue[current_floor][BUTTON_CALL_UP] || queue[current_floor][BUTTON_COMMAND] || queue[3][BUTTON_CALL_DOWN])
		{
			return true;
		}	
	}
	else if(current_dir == DIRN_DOWN)
	{
		if(queue[current_floor][BUTTON_CALL_DOWN] || queue[current_floor][BUTTON_COMMAND]|| queue[0][BUTTON_CALL_UP])
			return true;
	}
	else if(current_dir == DIRN_STOP)
	{
		if(queue[current_floor][BUTTON_CALL_UP] || queue[current_floor][BUTTON_CALL_DOWN]|| queue[current_floor][BUTTON_COMMAND])
			return true;
	}
	else if (current_dir == DIRN_DOWN && queue[current_floor][BUTTON_CALL_UP] && !order_below(current_floor)) {
		return true;
	}
	else if (current_dir == DIRN_UP && queue[current_floor][BUTTON_CALL_DOWN] && !order_above(current_floor)) {
		return true;
	}
	return false;
	

}

// To track which buttons that are pushed. To find bugs.
void print_queue(void)
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


