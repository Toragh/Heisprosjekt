#include "timer.h"
#include "io.h"
#include "channels.h"
#include <stdio.h>
#include <sys/time.h>

// Initializes a variable to set in set_timer()
double timer_end = 0.0;


// Returns the accurate time since 1 January 1970 im seconds and microseconds
double get_wall_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

// Starts the timer
int set_timer(void)
{
	timer_end = get_wall_time() + 3.00;
}

// Returns 1 when timer_end is a larger number than get_wall_time(). This means after 3 sec.
int get_timer_function(void)
{  
	return (get_wall_time() >= timer_end);
}


