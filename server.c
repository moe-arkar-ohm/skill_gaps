#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h> // POSIX socket library
#include <netinet/in.h> // Internet address structures

// --- NEW CODE: Defining our Data Model in Memory ---
typedef struct {
    int id;
    char username[32];
    int account_balance;
} User;
int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    printf("Server listening on port 8080...\n");
    
    while(1) {
        int client_socket = accept(server_fd, NULL, NULL);
        char buffer[1024] = {0}; 
        recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        
        char method[16], path[256], protocol[16];
        sscanf(buffer, "%s %s %s", method, path, protocol);
        
        // We declare a pointer for our final message
        char response[1024]; 
        
        if (strcmp(path, "/users") == 0) {
            // 1. Instantiate a User in memory
            User admin;
            admin.id = 1;
            strcpy(admin.username, "cto_founder");
            admin.account_balance = 500000;

            // 2. Format a proper HTTP response with the Content-Type set to JSON
            // We use sprintf to inject our C variables into the JSON string
            sprintf(response, 
                "HTTP/1.1 200 OK\n"
                "Content-Type: application/json\n\n"
                "{\n  \"id\": %d,\n  \"username\": \"%s\",\n  \"balance\": %d\n}\n", 
                admin.id, admin.username, admin.account_balance);
        } else {
            strcpy(response, "HTTP/1.1 404 NOT FOUND\n\n404: Route does not exist.\n");
        }

        send(client_socket, response, strlen(response), 0);
        close(client_socket); 
    }
    return 0;
}

