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
	
	int connection = Server.ClientSetup();
	if (connection < 0){
		return -1;
	}

	char buff[1024];
	std::string userInput;
	do {
		std::cout << ">";
		std::getline (std::cin, userInput);

		int byteSend = send (Server.get_socketfd(), userInput.c_str(), userInput.size() + 1 , 0);
	}while (true);

	//wait for response
	// memset (buff, 0, 1024);
	// int bytesReceived = recv (Server.SocketFD, buff, 1024, 0);

	//display response

	// std::cout << "Server> " << std::string (buff, bytesReceived) << std::endl;
	return 0;
}