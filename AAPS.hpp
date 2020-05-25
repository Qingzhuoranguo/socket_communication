#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <assert.h>
#include <stdio.h>


class AAPS_Socket {
private:
	int SocketFD = -1;
	struct sockaddr_in Socket;
	char IPv4 [16];
 	int Port = 0;
 	bool is_Server = false;
 	bool is_Client = false;
public:
	AAPS_Socket(){}
	AAPS_Socket( char addr[], int port );
	~AAPS_Socket();
	void status ();

	int ServerSetup(int n);
	int Accept(AAPS_Socket *server_socket);

	friend class AAPS_COM;
} ;


class AAPS_COM {
private:
	char COM_BUFF[1024];
	int COM_ID;
	AAPS_Socket *Server;
	AAPS_Socket *Client;
public:
	AAPS_COM(int id, AAPS_Socket *server_socket, AAPS_Socket *client_socket);
	AAPS_COM(int id, AAPS_Socket *server_socket, AAPS_Socket *client_socket, int size);
	int Send();
	int Recv();
	~AAPS_COM (){}

};


