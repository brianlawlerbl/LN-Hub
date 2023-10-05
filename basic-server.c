/*
Initial Prototype for HTTP Server
Single-threaded GET only
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
 
#define PORT 8000

int main (void){

    int sockfd, clientfd, readval, ret = 0;

    printf("SERVER BEGIN\n\n");

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == 0) {
        printf("Error creating socket\n\n");
    }


    ret = close(sockfd);
    if (ret != 0) {
        printf("Error closing socket\n\n");
    }
    else {
        printf("Socket closed gracefully\n\n");
    }

    return 0;
}
