#include "channels.h"
#include "elev.h"
#include "elev.c"
#include "io.h"

#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>


// Number of signals and lamps on a per-floor basis (excl sensor)
#define N_BUTTONS 3

//HUSK Å DEFINERE DENNE ETTERPÅ!!
int current_floor;
int current_dir;


void initialize_matrix(bool matrix[N_FLOORS][N_BUTTONS])
{
    for (int i = 0; i < N_FLOORS; ++i) // iterer denne riktig??
    {
        for (int j = 0; j < N_BUTTONS; ++j)
        {
            matrix[i][j] = 0;
        }
    }
    
}


void delete_item_in_matrix(bool matrix[N_FLOORS][N_BUTTONS], int current_floor)
{
    for (int i = 0; i < N_BUTTONS; ++i)
    {
        matrix[current_floor][i] = 0;
    }
}


bool get_order_below(bool matrix[N_FLOORS][N_BUTTONS])
{
    for (int i = 0; i < current_floor; i++)
    {
        for (int j = 0; j < N_BUTTONS; j++)
        {
            if(matrix[i][j]== 1)
            {
                return true;
            }
        }
    }
    return false;
}


bool get_order_above(bool matrix[N_FLOORS][N_BUTTONS])
{
    for (int i = N_FLOORS; i < current_floor; i--)
    {
        for (int j = 0; j < N_BUTTONS; j++)
        {
            if(matrix[i][j]== 1)
            {
                return true;
            }
        }
    }
    return false;
}


int get_next_dir(bool matrix[N_FLOORS][N_BUTTONS])
{
    if (current_dir == 1)
    {
        if (get_order_above(matrix))
        {
            return 1;
        }
        else if (get_order_below(matrix))
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
    else if (current_dir == -1)
    {
        if (get_order_below(matrix))
        {
            return -1;
        }
        else if (get_order_above(matrix))
        {
            return 1;
        }
        else
        {
            return 0;
        }
        
    }
    else
    {
        if (get_order_above(matrix))
        {
            return 1;
        }
        else if (get_order_below(matrix))
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
}







