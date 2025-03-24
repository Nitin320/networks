#include <stdio.h>    
#include <sys/types.h>    
#include <sys/socket.h>  
#include <netinet/in.h>   
#include <arpa/inet.h>    
#include <string.h>       
#include <unistd.h>      

void main(){

	struct sockaddr_in serveraddr;
	int sock_desc, n, length;
	char filename[100], filedata[200];
	
	
	sock_desc = socket(AF_INET, SOCK_STREAM, 0);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(2000);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	connect(sock_desc, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	printf("Enter in the file name : ");
	scanf("%s", filename);
	
	write(sock_desc, filename, strlen(filename));
	
	close(sock_desc);

}