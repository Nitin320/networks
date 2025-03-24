#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(){

	int sock_desc, client_sock, client_size;
	struct sockaddr_in server_addr, client_addr;
	char server_message[200], client_message[200];
	
	sock_desc = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2000);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(sock_desc, (struct sockaddr *)&server_addr, sizeof(server_addr));
	listen(sock_desc, 1);
	printf("Listening for incoming connections....\n");
	
	client_size = sizeof(client_addr);
	client_sock = accept(sock_desc, (struct sockaddr *)&client_addr, &client_size);
	
	while(1){
	
		recv(client_sock, client_message, sizeof(client_message), 0);
		printf("Message from client is %s\n", client_message);
		z:
			printf("y or n");
			scanf("%s", server_message);
			send(client_sock, server_message, strlen(server_message), 0);
			if(strcmp(server_message, "n") == 0) goto z;
	
	}
	close(client_sock);

}