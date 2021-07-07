// Server side implementation of UDP client-server model 
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
	struct sockaddr_in servaddr, cliaddr; 
	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("SOCKET CREATION FAILED\n"); 
		exit(EXIT_FAILURE); 
	} 
	else 
		printf("SOCKET IS CREATED\n"); 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("SOCKET BINDING IS FAILED"); 
		exit(EXIT_FAILURE); 
	} 
	else 
		printf("SOCKET IS BINDED \n");
	    int len, n; 
  
    len = sizeof(cliaddr);  //len is value/resuslt 
    char buff[MAX];
    int k=0;
  for(;;)
  {
  		bzero(buff,MAX);
    		n = recvfrom(sockfd, (char *)buff, MAXLINE,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                &len); 
    		buffer[n] = '\0'; 
    		printf("From CLIENT : %sTo CLIENT : ", buff); 
    		bzero(buff,MAX);
    		k=0;
    		while ((buff[k++] = getchar()) != '\n'); 
    		sendto(sockfd, (const char *)buff, strlen(buff),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            len); 
            if (strncmp("end", buff, 3) == 0) { 
			printf("END OF SERVER \n"); 
			break; 
			}
    }
      
	close(sockfd);
	return 0; 
} 

