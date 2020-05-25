#include <iostream>
#include <string.h>

#include "AAPS.hpp"


int main (int argc, char *argv[] ){
	char ip[16];
	std::cin >> ip;
	int port;
	char p[15];
	std::cin >> p;
	port = std::stoi(p);


	AAPS_Socket Server (ip, port);
	AAPS_COM Connection (&Server);
	Connection.HandShake();

	return 0;
}