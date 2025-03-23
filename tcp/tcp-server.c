#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(){

	int socket_desc, client_sock, client_size;
	struct sockaddr_in server_addr, client_addr;
	char server_message[200], client_message[200];
	
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2000);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	bind(socket_desc, (struct sock_addr *)&server_addr, sizeof(server_addr));
	listen(socket_desc, 1);
	printf("Listening for incoming connextions ......\n");
	
	client_size = sizeof(client_addr);
	client_sock = accept(socket_desc, (struct sockaddr *)&client_addr, &client_size);
	
	recv(client_sock, client_message, sizeof(client_message), 0);
	printf("The message from client is %s", client_message);
	
	strcpy(server_message, "This is the server message");
	send(client_sock, server_message, strlen(server_message), 0);
	
	close(client_sock);
	close(socket_desc);
	
}