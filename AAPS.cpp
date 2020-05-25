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
	if (is_Server){
		std::cout << "Socket type:\tServer" << std::endl;
	}else if (is_Client){
		std::cout << "Socket type:\tClient" << std::endl;
	}else{
		std::cout << "Socket type:\tNeutral" << std::endl;
	}
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
	is_Server = true;
	return 0;
}

int AAPS_Socket::Accept (AAPS_Socket *server_socket){
	if (is_Server || is_Client){
		std::cerr << "Socket must be Nuetral\n";
		return -2;
	}
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
	is_Client = true;
	return 0;
}

AAPS_COM::AAPS_COM(int id, AAPS_Socket *server_socket, AAPS_Socket *client_socket){
	COM_ID = id;
	Server = server_socket;
	Client = client_socket;

}

AAPS_COM::AAPS_COM(int id, AAPS_Socket *server_socket, AAPS_Socket *client_socket, int size){
	COM_ID = id;
	Server = server_socket;
	Client = client_socket;
}

int AAPS_COM::Recv(){
	if ( Client->Accept (Server)<0 ){
		return -1;
	}
	while (true){
		//clear buffer
		memset (COM_BUFF, 0, 1024);

		int byteRcv = recv (Client->SocketFD, COM_BUFF, 1024,0);
		if (byteRcv < 0){
			std::cerr << "AAPS_COM: receiving failure.\n";
			return -2;
		}else if (byteRcv == 0){
			std::cout << "AAPS_COM: the Client disconnected\n";
			return -3;
		}else{
			std::cout << std::string (COM_BUFF, 0, byteRcv)<< std::endl;
		}
		send (Client->SocketFD, COM_BUFF, byteRcv + 1, 0);
		close(Client->SocketFD);
	}
	return 0;
}

// int AAPS_COM::Send(){
	

// }

