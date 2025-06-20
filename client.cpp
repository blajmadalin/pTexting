#include <iostream>
#include <sys/socket.h>     //socket :)
#include <netinet/in.h>     // for sockaddr_in, htons(), INADDR_ANY
#include <unistd.h>         // for close()
#include <cstring> 
#include <stdio.h>

int main(){
    int clientSocket = (AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    const char* message = "Hello, server!";
    send(clientSocket, message, strlen(message), 0);
}