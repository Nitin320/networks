#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(){

	int socket_desc;
	struct sockaddr_in server_addr, client_addr;
	char client_message[200], server_message[200];
	
	socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(3000);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	bind(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr));
	printf("Listening for incoming messages...\n");
	
	int client_size = sizeof(client_addr);
	recvfrom(socket_desc, client_message, sizeof(client_message), 0, (struct sockaddr *)&client_addr, &client_size);
	printf("Message from client is : %s\n", client_message);
	
	strcpy(server_message, "This is the server message.\n");
	sendto(socket_desc, server_message, strlen(server_message), 0, (struct sockaddr *)&client_addr, client_size);
	
	close(socket_desc);

}