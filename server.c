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
        // Basic routing logic
        char response[1024]; 
        
        if (strcmp(method, "GET") == 0 && strcmp(path, "/users") == 0) {
            User admin;
            admin.id = 1;
            strcpy(admin.username, "cto_founder");
            admin.account_balance = 500000;

            sprintf(response, 
                "HTTP/1.1 200 OK\n"
                "Content-Type: application/json\n\n"
                "{\n  \"id\": %d,\n  \"username\": \"%s\",\n  \"balance\": %d\n}\n", 
                admin.id, admin.username, admin.account_balance);
                
        } else if (strcmp(method, "POST") == 0 && strcmp(path, "/users") == 0) {
            // --- NEW CODE: Extracting the Body ---
            // 1. Search the buffer for the exact dividing line
            char *body = strstr(buffer, "\r\n\r\n");
            
            if (body != NULL) {
                // 2. Move the pointer forward 4 spaces to skip the "\r\n\r\n" itself
                body += 4; 
                printf("\n[ROUTER] Received Payload: %s\n", body);
                
                // 3. Send a 201 Created response
                strcpy(response, "HTTP/1.1 201 Created\nContent-Type: application/json\n\n{\"status\": \"success\", \"message\": \"User received by C server!\"}\n");
            } else {
                strcpy(response, "HTTP/1.1 400 Bad Request\n\nMissing Body.\n");
            }
        } else {
            strcpy(response, "HTTP/1.1 404 NOT FOUND\n\n404: Route does not exist.\n");
        }

        send(client_socket, response, strlen(response), 0);
        close(client_socket); 
    }
    return 0;
}

