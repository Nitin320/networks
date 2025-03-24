#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

int main(){

	int sock_desc, frame;
	struct sockaddr_in server_addr;
	char server_message[200], client_message[200];
	
	sock_desc = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2000);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	connect(sock_desc, (struct sockaddr *)&server_addr, sizeof(server_addr));
	printf("Enter in the total frames : ");
	scanf("%d", &frame);
	
	while(frame > 0){
	
		printf("Enter in the frame message : ");
		scanf("%s", client_message);
		send(sock_desc, client_message, strlen(client_message), 0);
		
		x:
			recv(sock_desc, server_message, sizeof(server_message), 0);
			if(strcmp(server_message, "n") == 0){
				printf("Waiting...\n");
				goto x;
			}
			else frame--;
	
	}
	
	close(sock_desc);
}