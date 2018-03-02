#include "timer.h"
#include "io.h"
#include "channels.h"

#include <stdio.h>
#include <time.h>

int timer_function_3sec(void){
	int program_done = 0;
	time_t start = time(NULL);
	while(time(NULL)-start != 3)
	{
		program_done = 0;
	}
	program_done = 1;
	return program_done;
}

int get_timer_function(void){
	return timer_function_3sec();
}
