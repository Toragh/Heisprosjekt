#include "timer.h"
#include "io.h"
#include "channels.h"
#include <stdio.h>
#include <sys/time.h>

///////////////////////////////
//////////////TIMER////////////
///////////////////////////////



// Initializes a variable to set in timer_start_timer()
double timer_end = 0.0;


// Returns the accurate time since 1 January 1970 im seconds and microseconds
double timer_get_wall_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

// Starts the timer
void timer_start_timer(void)
{
	timer_end = timer_get_wall_time() + 3.00;
}

// Returns 1 when timer_end is a larger number than timer_get_wall_time(). This means after 3 sec.
int timer_check_timer_done(void)
{  
	return (timer_get_wall_time() >= timer_end);
}


