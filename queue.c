#include "queue.h"
#include "channels.h"
#include "elev.h"
#include "io.h"

#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>


// Number of signals and lamps on a per-floor basis (excl sensor)

// Initialize queue matrix
static bool queue[N_FLOORS][N_BUTTONS]= {0};

void clear_queue(void)
{
    for (int i = 0; i < N_FLOORS;i++)	// iterer denne riktig??
    {
        for (int j = 0; j < N_BUTTONS; j++)
        {
            queue[i][j] = 0;
        }
    }
    
}


void delete_item_in_queue(int current_floor)
{
    for (int i = 0; i < N_BUTTONS; i++)
    {
        queue[current_floor][i] = 0;
    }
}


bool get_order_below(int current_floor)
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


bool get_order_above(int current_floor)
{
    for (int i = N_FLOORS; i < current_floor; i--)
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


int get_next_dir(int current_dir, int current_floor)
{
    if (current_dir == DIRN_UP)
    {
        if (get_order_above(current_floor))
        {
            return DIRN_UP;
        }
        else if (get_order_below(current_floor))
        {
            return DIRN_DOWN;
        }
        else
        {
            return DIRN_STOP;
        }
    }
    else if (current_dir == -1)
    {
        if (get_order_below(current_floor))
        {
            return DIRN_DOWN;
        }
        else if (get_order_above(current_floor))
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
        if (get_order_above(current_floor))
        {
            return DIRN_UP;
        }
        else if (get_order_below(current_floor))
        {
            return DIRN_DOWN;
        }
        else
        {
            return DIRN_STOP;
        }
    }
}

bool check_orders(void)
{
    for (int i = 0; i < N_FLOORS; ++i) // iterer denne riktig??
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

// Check if buttons pushed
// er elev_get_button_signal langt nok til at 1ern registeres
void update_queue(void)
{
    for (int i = 0; i < N_FLOORS; ++i)
    {
		if(i == 0)
		{
			queue[i][0]= elev_get_button_signal(0,i);
			queue[i][2]= elev_get_button_signal(2,i);
            		
		}
		else if (i == 3)
		{
			queue[i][1]= elev_get_button_signal(1,i);
			queue[i][2]= elev_get_button_signal(2,i);
		}
		else
		{
			for (int j = 0; j < N_BUTTONS; ++j)
        		{
			queue[i][j]= elev_get_button_signal(j,i);
            		}
		}
        }
}


bool should_stop(int current_floor, int current_dir){	
	if(current_dir == DIRN_UP)
	{
		if(queue[current_floor][0] || queue[current_floor][2])
		{
			return true;
		}	
	}
	else if(current_dir == DIRN_DOWN)
	{
		if(queue[current_floor][1] || queue[current_floor][2])
			return true;
	}
	return false;

}

void print_queue(void)
{
	printf("queue /n");
	for(int i = 0; i < N_FLOORS; ++i)
	{
		for (int j = 0; j < N_BUTTONS; ++j)
		{
			printf(queue[i][j]);
		}
	}


}


