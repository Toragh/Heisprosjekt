#include "timer.h"
#include "io.h"
#include "channels.h"

#include <stdio.h>
#include <time.h>

int program_done = 0;

void timer_function_3sec(void){
	program_done = 0;
	time_t start = time(NULL);
	while(time(NULL)-start != 3)
	{
		program_done = 0;
	}
	program_done = 1;
}

int get_timer_function(void){
	return program_done;
}

int set_timer_function(void){
	program_done = 0;
}
