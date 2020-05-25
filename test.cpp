#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <string.h>
#include <typeinfo>


int main (){

	char *buff = (char *)malloc (10);

	for (int i = 0; i < 10; i++){

		buff[i] = 'a';
	}

	std::cout << std::string (buff) << std::endl;

	return 0;
}