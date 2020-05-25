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
	int n = Client.Accept(&Server);
	if (n < 0) {return -1;}
	UniqueID id;
	
	AAPS_COM Connection (id.id, &Client, &Server);
	Connection.HandShake();


	return 0;
}