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

	int Accept(AAPS_Socket *server_socket);
public:
	AAPS_Socket(){}
	AAPS_Socket( char addr[], int port );
	~AAPS_Socket();
	void status ();

	int get_socketfd(){return SocketFD;}

	int ServerSetup(int n);
	int ClientSetup();

	friend class AAPS_COM;
} ;


class AAPS_COM {
private:
	char *COM_BUFF;
	int COM_ID;
	AAPS_Socket *Server;
	AAPS_Socket *Client;
public:
	//passive connection 
	AAPS_COM(int id, AAPS_Socket *server_socket, AAPS_Socket *client_socket);
	//active connection
	AAPS_COM(AAPS_Socket *server_socket);
	int Connect();

	int Send();
	int Recv( int size );
	~AAPS_COM (){ delete COM_BUFF; }

};



