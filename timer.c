#include "timer.h"
#include "io.h"
#include "channels.h"

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

double get_wall_time(void);

//int program_done = 0;
double timer_end = 0.0;

/*void timer_function_3sec(void)
{
	program_done = 0;
	double start = get_wall_time();
	while(get_wall_time() - start <= 3)
	{
		program_done = 0;
	}
	program_done = 1;
}*/

int get_timer_function(void){  //is_timer_expired
	return (get_wall_time() >= timer_end);
}

int set_timer(void){
	timer_end = get_wall_time() + 3.00;
	//program_done = 0;
}

double get_wall_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (double)time.tv_sec + (double)time.tv_usec * .000001;
}
