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

    // variable initializations
    int sockfd, clientfd, readval, ret = 0;
    int opt = 1;
    char buffer[8192];
    for (int i = 0; i < 8192; i+=1) {
        buffer[i] = 0;
    }
    struct sockaddr_in address;

    // get socket file descriptor and set options
    printf("SERVER BEGIN\n\n");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == 0) {
        printf("Error creating socket\n\n");
        return -1;
    }
    ret = 0;
    ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    if (ret != 0) {
        printf("Error setting socket options");
        return -1;
    }

    // setup sockaddr
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // trash code for Wall
    clientfd = 1;
    readval = 1;
    if (clientfd == 0 && readval == 0) {
        printf("");
    }

    // TODO -----------------------------------------------------------------------------
    // bind listening socket

    // listen for connections

    //accept connections

    // read message

    // parse message

    // respond

    // CLOSING CODE - NO CODE BEYOND THIS POINT
    ret = close(sockfd);
    if (ret != 0) {
        printf("Error closing socket\n\n");
        return -1;
    }
    else {
        printf("Socket closed gracefully\n\n");
    }

    return 0;
}
