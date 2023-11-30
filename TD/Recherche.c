#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>

int main(int argc, char ** argv){
	struct addrinfo hints;
	struct addrinfo *res;
	char bufferServerName[128] = {0};
	char bufferHostName[128] = {0};
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_protocol=IPPROTO_TCP;
	hints.ai_socktype=SOCK_STREAM;
	printf("GetAddrInfo on: %s\n",argv[1]);
	getaddrinfo(argv[1],NULL,&hints,&res);
	struct addrinfo * current;
	current = res;
	while(current != NULL){
		printf("Found one answer: \t ai_family = %d \t ai_socktype = %d \t ai_protocol = %d\n", current->ai_family, current->ai_socktype, current->ai_protocol);
		current = current-> ai_next;
		getnameinfo(current->ai_addr, current->ai_addrlen, bufferHostName,128,bufferServerName,128,NI_NUMERICHOST | NI_NUMERICSERV);
		printf("Host: %s \t Service: %s\n", bufferHostName,bufferServerName);
		current= current->ai_next;
	}
	
	
	return 0;
	
}
	
