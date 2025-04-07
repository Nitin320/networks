#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(){

	int socket_desc, client_sock, client_size;
	struct sockaddr_in server_addr, client_addr;
	
	int client_ack, server_num, checker_array[100];
	
	int total, frame;
	
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4000);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if(bind(socket_desc, (struct sock_addr *)&server_addr, sizeof(server_addr)) < 0){
		printf("ERRORRR\n");
	}
	listen(socket_desc, 1);
	printf("Listening for incoming connextions ......\n");
	
	client_size = sizeof(client_addr);
	client_sock = accept(socket_desc, (struct sockaddr *)&client_addr, &client_size);
	
	int curr = 0;
	
	for(int i=0; i<100; i++) checker_array[i] = 0;
	
	recv(client_sock, &total, sizeof(int), 0);
	recv(client_sock, &frame, sizeof(int), 0);
	
	for(int i=0; i<frame; i++){
		memset(&server_num, 0, sizeof(int));
		recv(client_sock, &server_num, sizeof(int), 0);
		printf("Recieved frame : %d\n", server_num);
		
		checker_array[server_num] = 1;
		curr++;
		
		client_ack = i;
		send(client_sock, &client_ack, sizeof(int), 0);
		printf("Sent ack : %d\n", i);
	}
	
	while(curr <= total){
	
		memset(&server_num, 0, sizeof(int));
		recv(client_sock, &server_num, sizeof(int), 0);
		printf("Recieved frame : %d\n", server_num);
		sleep(1);
		
		if(checker_array[server_num] == 0){
		
			checker_array[server_num] = 1;
			client_ack = server_num;
			send(client_sock, &client_ack, sizeof(int), 0);
			printf("Sent ack : %d\n", client_ack);
			curr++;
		}
		else{
		
			printf("Frame recieved already...Ignoring\n");
			//send(client_sock, &client_ack, sizeof(int), 0);
		}
	}
	
	close(client_sock);
	close(socket_desc);
	
}