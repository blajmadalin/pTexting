#include <iostream>
#include <sys/socket.h>     //socket :)
#include <netinet/in.h>     // for sockaddr_in, htons(), INADDR_ANY
#include <unistd.h>         // for close()
#include <cstring> 
#include <stdio.h>

int main(){
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0); //defining socket

    sockaddr_in serverAddress; //creating serverAdress
    serverAddress.sin_family = AF_INET; //ipv4
    serverAddress.sin_port = htons(8080); //port is 8080
    serverAddress.sin_addr.s_addr = INADDR_ANY; //

    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)); //binding socket to server adress
    listen(serverSocket, 5); //starts listening on serverSocket.
    
    while(true){
        int clientSocket = accept(serverSocket, nullptr, nullptr);

        if(clientSocket < 0){
            perror("failed connection");
            continue;
        }

        char buffer[1024] = {0};
        recv(clientSocket, buffer, sizeof(buffer), 0);
        std::cout<<buffer;

        close(clientSocket);
    }

}
