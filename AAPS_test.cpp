#include <iostream>
#include <string.h>
#include "AAPS.hpp"
#include "UniqueID/UniqueID.hpp"


int main (){
	char ip[] = "192.168.0.22";
	int port = 12000;

	AAPS_Socket Server (ip, port);
	Server.ServerSetup(1);


	AAPS_Socket Client;
	UniqueID id;
	AAPS_COM Connection (id.id, &Server, &Client);


	Connection.Recv();


	return 0;
}