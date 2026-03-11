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

    // 1 Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);

    // 2 Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 3 Bind socket
    bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 4 Listen for clients
    listen(server_sock, 5);

    printf("Waiting for connection...\n");

    // 5 Accept connection
    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);

    // 6 Receive message
    recv(client_sock, buffer, sizeof(buffer), 0);
    printf("Client says: %s\n", buffer);

    // 7 Send response
    strcpy(buffer, "Message received");
    send(client_sock, buffer, sizeof(buffer), 0);

    // 8 Close socket
    close(server_sock);

    return 0;
}


// Algorithm for TCP Server

// Step 1: Start the program.

// Step 2: Create a socket using
// socket(AF_INET, SOCK_STREAM, 0).

// Step 3: Define the server address using sockaddr_in structure.

// Step 4: Assign values to the server address:

// Set address family to AF_INET

// Set port number using htons()

// Set IP address using INADDR_ANY

// Step 5: Bind the socket with the server address using bind().

// Step 6: Put the server in listening mode using listen().

// Step 7: Accept the client connection using accept().

// Step 8: Receive message from the client using recv().

// Step 9: Display the received message.

// Step 10: Send response to the client using send().

// Step 11: Close the socket using close().

// Step 12: Stop the program.