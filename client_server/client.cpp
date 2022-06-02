#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_HOST "localhost"
#define SERVER_PORT 3333
#define CLIENT_PORT 3334

#define MSG "Enter your name\n"

int main()
{
	int sock;
	socklen_t answer_len;
	
	int BUF_SIZE = 64;
	
	char buffer[BUF_SIZE];
	
	char msg[10];
	
	//show msg on standardt output
	write(1, MSG, sizeof(MSG));
	
	//enter msg
	scanf("%s", msg);
	
	//struct to allow domain name
	struct hostent *h;
	
	//struct for client and server addresses 
	struct sockaddr_in client, server;
	
	//create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	//clear struct client
	memset((char*)&client, '\0', sizeof(client));
	
	//fill client struct
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = CLIENT_PORT;
	
	//connect socket with port
	bind(sock, (struct sockaddr *)&client, sizeof(client));
	memset((char*)&client, '\0', sizeof(server));
	
	//receive IP of server
	h= gethostbyname(SERVER_HOST);
	
	//fill server address struct
	server.sin_family = AF_INET;
	
	//set server address
	memcpy((char*)&server.sin_addr,h->h_addr, h->h_length);
	
	//set server port
	server.sin_port = SERVER_PORT;
	
	//connect to the server
	connect(sock, (struct sockaddr *)&server, sizeof(server));
	
	//receive msg from server
	answer_len = recv(sock, buffer, BUF_SIZE, 0);
	
	//show msg on standardt output
	write(1, buffer, answer_len);
	
	//send data to server
	send(sock, msg, sizeof(msg),0);
	
	shutdown(sock, 0);
	close(sock);
	exit(0);
	
	
}