#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>

int main (){

	//AF_INET: IPv4
	int ServerSocket = socket (AF_INET, SOCK_STREAM, 0);
	if (ServerSocket < 0 ){
		std::cerr << "Cannot create socket\n";
		return -1;
	}

	//Bind the socket 
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.0.22", &(server.sin_addr));
	server.sin_port = htons(12000);

	// char ls[INET_ADDRSTRLEN];
	// inet_ntop(AF_INET, &(server.sin_addr), ls, INET_ADDRSTRLEN);
	// printf("%s\n", ls);

	if (bind (ServerSocket, (struct sockaddr*)&server, sizeof(server)) == -1 ){
		std::cerr << "Cannot bind to (IP, prot)\n";
		return -2;
	}

	if ( listen(ServerSocket, SOMAXCONN) == -1 ){
		std::cerr << "Cannot listen\n";
		return -3;
	}
	
	std::cout << "Server ready to receive\n";


	while (1){
		struct sockaddr_in client;
		char client_IPv4_addr [INET_ADDRSTRLEN];
		socklen_t clientlen = sizeof (sockaddr_in);
		char buffer [1024];

		int ClientSocket = accept (	ServerSocket,
								(struct sockaddr *)&client,
								&clientlen);
		if (ClientSocket < 0){
			std::cerr << "ClientSocket creation failure.\n";
			return -4;
		}

		while (true){
			int n = read (ClientSocket, buffer, 8);
			if (n < 0){
				std::cerr << "Error reading from client.\n";
				return -5;
			}
			write(1, buffer, 8);
			write(1,"\n",1);
			memset(buffer, 0, 8);
		}
		// int n = read (ClientSocket, buffer, 8);
		// if (n < 0){
		// 	std::cerr << "Error reading from client.\n";
		// 	return -5;
		// }
		// std::cout << "Client - ";
		// std::cout << inet_ntop(AF_INET, &(client.sin_addr), client_IPv4_addr, INET_ADDRSTRLEN);
		// std::cout << ":\n\t" << buffer << std::endl;

		// std::system("./program");

		// char msg[] = "Server response\n";
		// int msg_len = strlen(msg);
		// n = send (ClientSocket, msg, msg_len, 0);
	}



	return 0;
}