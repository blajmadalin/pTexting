#include <iostream>
#include <sys/socket.h>     //socket :)
#include <netinet/in.h>     // for sockaddr_in, htons(), INADDR_ANY
#include <unistd.h>         // for close()
#include <cstring> 
#include <stdio.h>
#include <thread>

void handleClient(int clientSocket){
while(true){
            char buffer[1024] = {0};
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

            if(bytesReceived <= 0){
                perror("client disconnected");
                close(clientSocket);
                break;
            }

            std::cout<<"Client: " <<buffer << '\n';
        }
}

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

        if(clientSocket < 1){
            perror("failed to connect client \n");
            continue;
        }

        std::cout<<"client connected \n";  
        std::thread(handleClient, clientSocket).detach();

    }

    return 0;

}
