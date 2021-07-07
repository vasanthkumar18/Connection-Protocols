// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#define MAX 80 

#define PORT	 8080 
#define MAXLINE 1024 

// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE];  
	struct sockaddr_in	 servaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("SOCKET CREATION IS FAILED\n"); 
		exit(EXIT_FAILURE); 
	} 
	else 
		printf("SOCKET IS CREATED\n"); 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 

	  int n, len; 
	  int k;
	  char buff[MAX];
      for(;;)
      {
      		bzero(buff,sizeof(buff));
		printf("Enter the message to SERVER : ");
		k=0;
    		while ((buff[k++] = getchar()) != '\n'); 
		
      		sendto(sockfd, (const char *)buff, strlen(buff), 
        	MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            	sizeof(servaddr)); 
            	
            	bzero(buff,sizeof(buff));
            	
		n = recvfrom(sockfd, (char *)buff, MAXLINE,  
                MSG_WAITALL, (struct sockaddr *) &servaddr, 
                &len); 
	    	buff[n] = '\0'; 
    		printf("Message from SERVER : %s", buff); 
    		if ((strncmp(buff, "end", 3)) == 0) { 
			printf("END OF CLIENT\n"); 
			break; 
		} 
    	}
    	close(sockfd);
	return 0; 
} 

