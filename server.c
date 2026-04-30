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
   // The Event Loop
    while(1) {
        int client_socket = accept(server_fd, NULL, NULL);
        char buffer[1024] = {0}; 
        recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        
        // --- NEW CODE: The Router ---
        // We create small buckets to hold the extracted words
        char method[16], path[256], protocol[16];
        
        // sscanf looks at the buffer, grabs the first 3 words separated by spaces, 
        // and drops them into our buckets.
        sscanf(buffer, "%s %s %s", method, path, protocol);
        
        printf("\n[ROUTER] Action: %s | Route: %s\n", method, path);
        
        // Basic routing logic
        char *message;
        if (strcmp(path, "/ledger") == 0) {
            message = "HTTP/1.1 200 OK\n\nWelcome to the Financial Ledger!\n";
        } else if (strcmp(path, "/users") == 0) {
            message = "HTTP/1.1 200 OK\n\nReturning User Database...\n";
        } else {
            message = "HTTP/1.1 404 NOT FOUND\n\n404: Route does not exist.\n";
        }

        send(client_socket, message, strlen(message), 0);
        close(client_socket); 
    }
    return 0;
}