#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>

int main (){

	time_t my_time = time (NULL);

	char time[32];
	memcpy(time,ctime(&my_time),32);
	memmove(time, time+4, 32-4);
	std::cout << time << std::endl;


	return 0;
}