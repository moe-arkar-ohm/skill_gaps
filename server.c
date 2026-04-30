#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h> // POSIX socket library
#include <netinet/in.h> // Internet address structures

int main() {
    // 1. Ask the OS for a network socket (like asking for a telephone)
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // 2. Configure the address and port (Port 8080)
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    
    // 3. Bind the socket to the port (plug the phone into the wall)
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    
    // 4. Listen for incoming connections
    listen(server_fd, 3);
    printf("Server listening on port 8080...\n");
    // The Event Loop
    while(1) {
        int client_socket = accept(server_fd, NULL, NULL);
        
        // 1. Create a blank notepad (buffer) of 1024 bytes in memory
        char buffer[1024] = {0}; 
        
        // 2. Read the browser's incoming message into the notepad
        recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        
        // 3. Print the notepad to our terminal
        printf("\n--- NEW REQUEST RECIEVED ---\n");
        printf("%s", buffer);
        printf("----------------------------\n");
        
        // 4. Send our standard reply
        char *message = "HTTP/1.1 200 OK\n\nHello from the infinite loop!\n";
        send(client_socket, message, strlen(message), 0);
        
        close(client_socket); 
    }
    return 0;
}