#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(){

	int socket_desc;
	struct sockaddr_in server_addr;
	char server_message[200], client_message[200];
	
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2000);
	server_addr. sin_addr.s_addr = inet_addr("127.0.0.1");
	
	connect(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr));
	
	printf("Enter in a message : ");
	gets(client_message);
	
	send(socket_desc, client_message, strlen(client_message), 0);
	recv(socket_desc, server_message, sizeof(server_message), 0);
	
	printf("server's response is : %s\n", server_message);
	
	close(socket_desc);

}