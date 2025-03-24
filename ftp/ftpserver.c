#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>

int main(){

	struct sockaddr_in server_addr, client_addr;
	int sock_desc, client_sock, client_size, n, f;
	char filename[100], filedata[200];
	
	sock_desc = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2000);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	bind(sock_desc, (struct sockaddr *)&server_addr, sizeof(server_addr));
	listen(sock_desc, 5);
	
	while(1){
	
		client_size = sizeof(client_sock);
		client_sock = accept(sock_desc, (struct sockaddr *)&client_addr, &client_size);
		
		n = read(client_sock, filename, 100);
		printf("%s", filename);
		filename[n] = 0;
		f = open(filename, O_RDWR);
		n = read(f, filedata, 200);
		
		printf("The contents of the file is : ");
		printf("%s", filedata);
		
	}
	close(sock_desc);
	close(client_sock);

}