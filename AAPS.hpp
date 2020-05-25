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

std::string itoa(int a);

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
	AAPS_Socket *Target;
	AAPS_Socket *Self;
	bool is_Active = false;
public:
	//passive connection 
	AAPS_COM(int id, AAPS_Socket *target_socket, AAPS_Socket *self_socket){
		COM_ID = id;
		Target = target_socket;
		Self = self_socket;
	}
	//active connection
	AAPS_COM(AAPS_Socket *socket){
		Target = socket;
		Self = NULL;
	}

	int Connect();
	int HandShake();

	int Send();
	char *Recv( int size );
	~AAPS_COM (){}

};



