#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_sock, client_sock;
    char buffer[1024];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    FILE *file;

    // 1 Create socket, Bind, and Listen
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_sock, 5);
    
    printf("FTP Server listening on port 9002...\n");
    addr_size = sizeof(client_addr);
    
    // Accept client connection
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);

    // 2 Receive filename from client
    memset(buffer, 0, sizeof(buffer));
    recv(client_sock, buffer, sizeof(buffer), 0);
    
    printf("Client requested file: %s\n", buffer);

    // 3 Open file and send contents
    file = fopen(buffer, "r");
    
    if (file == NULL) {
        // If file doesn't exist, send an error message
        strcpy(buffer, "Error: File not found on server.\n");
        send(client_sock, buffer, strlen(buffer), 0);
    } else {
        // Read file line by line and send it to the client
        memset(buffer, 0, sizeof(buffer));
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            send(client_sock, buffer, strlen(buffer), 0);
            memset(buffer, 0, sizeof(buffer));
        }
        fclose(file);
        printf("File sent successfully!\n");
    }

    // 4 Close sockets
    close(client_sock);
    close(server_sock);
    return 0;
}



// Algorithm for FTP Server
// Step 1: Start the program.
// Step 2: Create a TCP server socket using socket(AF_INET, SOCK_STREAM, 0).
// Step 3: Define the server address (Port 9002, IP INADDR_ANY), bind() the socket, and put it in listening mode using listen().
// Step 4: Accept an incoming client connection using accept() and store the new client socket.
// Step 5: Receive the requested filename from the client using recv().
// Step 6: Attempt to open the requested file in read mode using fopen().
// Step 7: Check if the file pointer is NULL (meaning the file does not exist).

// If NULL: Send a "File not found" error string to the client.

// If NOT NULL: Enter a while loop to read the file using fgets().
// Step 8: Inside the loop, read one line of the file into the buffer and send it to the client using send(). Clear the buffer and repeat until the end of the file is reached.
// Step 9: Close the file pointer using fclose().
// Step 10: Close the client socket and the main server socket using close().
// Step 11: Stop the program.