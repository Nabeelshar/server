#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT_NO 8080

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    // Clear serv_addr
    memset(&serv_addr, 0, sizeof(serv_addr));

    // Set up the server address
    portno = PORT_NO;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR on binding");

    // Listen for incoming connections
    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    // Accept incoming connections
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) 
        error("ERROR on accept");

    // Clear the buffer
    memset(buffer, 0, sizeof(buffer));

    // Read data from the client
    n = read(newsockfd, buffer, 255);
    if (n < 0) 
        error("ERROR reading from socket");
    std::cout << "Here is the message: " << buffer << std::endl;

    // Send data to the client
    n = write(newsockfd, "I got your message", 18);
    if (n < 0) 
        error("ERROR writing to socket");

    // Close the sockets
    close(newsockfd);
    close(sockfd);
    return 0; 
}
