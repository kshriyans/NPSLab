#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>


void str_cli(FILE *fp, int sockfd){

	int buffsize = 1024, cont;
	char *buffer = malloc(buffsize);
	while(fgets(buffer, buffsize, fp ) != NULL){
	
		send(sockfd, buffer, sizeof(buffer), 0);
		if(( cont = recv(sockfd, buffer, buffsize, 0)) > 0){
		
			fputs(buffer, stdout);
		}
	}
	printf("\nEOF\n");

}


int main(int argc, char * argv[]){

	struct sockaddr_in address;
	int create_socket;
	if (( create_socket = socket(AF_INET,SOCK_STREAM,0)) >0)
		printf("Socket was created\n");
	address.sin_family = AF_INET;
	address.sin_port = htons(15001);
	inet_pton(AF_INET, argv[1], &address.sin_addr);
	if ( connect(create_socket, (struct sockaddr *) &address, sizeof(address)) == 0)
		printf("The connection was accepted with the server %s..\n",argv[1]);
	else
		printf("error in connect \n"); 
	
	str_cli(stdin,create_socket);
	return close(create_socket);

}
