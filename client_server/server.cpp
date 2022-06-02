//#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//using namespace std;

#define PORT 3333

#define BUF_SIZE 64

#define MSG_TO_SEND "My simple server v1\n"

int main(int argc, char **argv) {

	int server_socket, client_socket;

	int count = 0;

	socklen_t answer_len;

	char buffer[BUF_SIZE];

	//create server socket
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	//STRUCT WITH IP AND PORT NUMBER
	struct sockaddr_in sin, client;

	//clear struct
	memset((char*)&sin, '\0', sizeof(sin));

	//set struct fields
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = PORT;

	//connect socket with port
	bind(server_socket, (struct sockaddr *)&sin, sizeof(sin));

	printf("Server started. \n");

	//max size of clients = 3
	listen(server_socket, 3);

	while(1)
	{
		//len of answer
		answer_len = sizeof(client);

		//receive client request
		client_socket = accept(server_socket, (struct sockaddr *) &client, &answer_len);

		//send message to the client
		write(client_socket, MSG_TO_SEND, sizeof(MSG_TO_SEND));

		//increase count of client
		count++;

		//read client answer to buffer, return size of read bytes to the answer_len
		answer_len = read(client_socket, buffer, BUF_SIZE);

		//show client answer on standard output
		write(1, buffer, answer_len);

		printf("Client no %d\n", count);

		//disconnect
		shutdown(client_socket, 0);

		//close connection
		close(client_socket);
	}

	return 0;
}
