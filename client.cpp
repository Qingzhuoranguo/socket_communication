#include <iostream>
#include <string.h>
#include <stdio.h>
#include "AAPS.hpp"

#include <thread>         // std::thread
#include <mutex>          // std::mutex


std::mutex display_lock;

void type (AAPS_COM *c){
	while(true){
		AAPS_COM Connection = *c;
		std::string input;

		display_lock.lock();
		std::cout << "You>\t";
		getline (std::cin, input);
		display_lock.unlock();

		char *msg = (char *)malloc (input.size()+1);
		memcpy (msg, input.c_str(), input.size()+1);
		Connection.Send(msg);
		free(msg);
	}
}

void display (AAPS_COM *c){
	while (true){
		AAPS_COM Connection = *c;
		char *rmsg = Connection.Recv();

		display_lock.lock();
		std::cout <<"Server>\t"<<rmsg << std::endl;
		display_lock.unlock();
	}
}

int main (int argc, char *argv[] ){

	char ip[16];
	memcpy (ip, argv[1],16);
	int port;
	port = std::stoi(argv[2]);


	AAPS_Socket Server (ip, port);
	AAPS_COM Connection (&Server);
	Connection.HandShake();

	std::thread a = std::thread(type,&Connection);
	std::thread b = std::thread(display, &Connection);

	a.join();
	b.join();


	return 0;
}