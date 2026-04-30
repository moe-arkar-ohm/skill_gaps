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
    
    // 5. Accept a connection and say hello
    int client_socket = accept(server_fd, NULL, NULL);
    char *message = "HTTP/1.1 200 OK\n\nHello from raw C!\n";
    send(client_socket, message, strlen(message), 0);
    
    printf("Message sent, closing server.\n");
    close(client_socket);
    close(server_fd);
    return 0;
}