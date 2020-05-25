#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "AAPS.hpp"


AAPS_Socket::AAPS_Socket( char addr[], int port ){
	strcpy( IPv4, addr);
	Port = port;

	SocketFD = socket (AF_INET, SOCK_STREAM, 0);
	if (SocketFD<0){ 
		std::cerr << "Socket creation failure\n";
	}

	Socket.sin_family = AF_INET;
	inet_pton (AF_INET, (char*)IPv4, &(Socket.sin_addr));
	Socket.sin_port = htons(port);
}

AAPS_Socket::~AAPS_Socket(){}

void AAPS_Socket::status(){
	std::cout << "Socket addr:\t" << IPv4 << std::endl;
	std::cout << "Socket port:\t" << Port << std::endl;
	std::cout << std::endl;
}

int AAPS_Socket::ServerSetup (int n){
	if (bind (SocketFD, (struct sockaddr*)&Socket, sizeof(Socket)) == -1 ){
		std::cerr << "Binding to (" << IPv4 << ", " << Port << ") failed.\n";
		return -2;
	}
	if ( listen(SocketFD, n) == -1 ){
		std::cerr << "Listening to " << n << " clients failed.\n";
		return -3;
	}

	std::cout << "Server on (" << IPv4 << ", " << Port << ") is ready to receive.\n\n";
	return 0;
}

int AAPS_Socket::ClientSetup(){
	return connect (SocketFD, (sockaddr *)&Socket, sizeof(sockaddr_in));
}

int AAPS_Socket::Accept (AAPS_Socket *server_socket){
	socklen_t clientlen = sizeof (sockaddr_in);
	SocketFD = accept(
		server_socket->SocketFD,
		(struct sockaddr *)&Socket,
		&clientlen
	);

	if (SocketFD < 0){
		std::cerr << "ClientSocket connection failure.\n";
		return -1;
	}
	inet_ntop(AF_INET, &(Socket.sin_addr), IPv4, 16);
	Port =  ntohs((server_socket->Socket).sin_port);
	std::cout << "Connection to Client (" << 
					 IPv4<<
					 ", " <<
					 Port << 
					") is established\n\n";
	return 0;
}





int AAPS_COM::Connect (){
	if (Self != NULL) {return -1;}
	int indicator = Target->ClientSetup();
	if (indicator<0){
		std::cerr << "AAPS_COM: connection error.\n";
		return indicator;
	}
	HandShake();
	return 0;
}

std::string itoa(int a)
{
    std::string ss="";   //create empty string
    while(a)
    {
        int x=a%10;
        a/=10;
        char i='0';
        i=i+x;
        ss=i+ss;      //append new character at the front of the string!
    }
    return ss;
}

int AAPS_COM::HandShake() {
	// client side handshake
	if (Self == NULL){
		int indicator = Target->ClientSetup();
		if (indicator<0){
			std::cerr << "AAPS_COM: connection error.\n";
			return indicator;
		}


		char buff[1024];
		memset(buff, 0, 1024);
		int bytesReceived = recv (Target->SocketFD, buff, 1024, 0);
		if (bytesReceived<0){ return -2; }
		int x = std::stoi (buff);
		COM_ID = x;
		send(Target->SocketFD, itoa(x).c_str(), strlen(itoa(x).c_str()), 0);
		return 0;
	}
	//else: server side handshake
	for (int i = 0; i < 50; i ++ ){ //give client 50 trys to respond correct unique id.
		// give the client the connection id.
		if (not is_Active){
			send (Target->SocketFD, itoa(COM_ID).c_str(), strlen(itoa(COM_ID).c_str()), 0);
		}
		char buff[1024];
		memset (buff, 0, 1024);
		int bytesReceived = recv (Target->SocketFD, buff, 1024, 0);
		if (bytesReceived<0){ return -2; }
		if (std::stoi(buff) == COM_ID){
			std::cout << "HandShake complete.\n";
			is_Active = true;
			return 0;
		}
	}
	std::cout << "HandShake failed\n";
	return -1;
}


	




		// //clear buffer
		// memset (COM_BUFF, 0, size);

		// int byteRcv = recv (Client->SocketFD, COM_BUFF, size, 0);

		// if (byteRcv < 0){
		// 	std::cerr << "AAPS_COM: receiving failure.\n";
		// 	return -2;
		// }else if (byteRcv == 0){
		// 	std::cout << "AAPS_COM: the Client disconnected\n";
		// 	return -3;
		// }else{
		// 	std::cout << std::string (COM_BUFF, 0, byteRcv)<< std::endl;
		// }
		// // send (Client->SocketFD, COM_BUFF, byteRcv + 1, 0);
		// // close(Client->SocketFD);