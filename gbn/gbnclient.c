#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(){

	int socket_desc;
	struct sockaddr_in server_addr;

	int client_ack, server_num;
	
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4000);
	server_addr. sin_addr.s_addr = inet_addr("127.0.0.1");
	
	connect(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr));
	
	int total, frame;
	int curr = 0;
	
	printf("Enter in the total number of elements : ");
	scanf("%d", &total);
	printf("Enter in the frame size : ");
	scanf("%d", &frame);
	
	send(socket_desc, &total, sizeof(int), 0);
	send(socket_desc, &frame, sizeof(int), 0);
	
	int sender = frame;
	int choice;
	
	for(int i=0; i<frame; i++){
		
		server_num = i;
		printf("Sending frame %d\n", i);
		send(socket_desc, &server_num, sizeof(int), 0);
	
	}
	
	
	while(curr < total-frame){
	
		choice = rand()%2;
		
		if(choice == 1){
			memset(&client_ack, 0, sizeof(int));
			recv(socket_desc, &client_ack, sizeof(int), 0);
			printf("recieved ack for %d\n", client_ack);
			curr++;
			server_num = sender;
			printf("Sending frame %d\n", server_num);
			send(socket_desc, &server_num, sizeof(int), 0);
			sender++;
			
		}
		else{
			
			printf("Acknoledgement Lost, retransmitting from %d\n", curr);
			for(int i=0; i<frame; i++){
				server_num = curr + i;
				printf("Retransmitting %d\n", server_num);
				send(socket_desc, &server_num, sizeof(int), 0);
			}
			
		}
	}
	
	while(curr <= total){
		
		memset(&client_ack, 0, sizeof(int));
		recv(socket_desc, &client_ack, sizeof(int), 0);
		printf("recieved ack for %d\n", client_ack);
		curr++;
	}
	
	close(socket_desc);

}