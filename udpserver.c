#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {

    int sockfd;
    char buffer[1024];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    // 1 Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 2 Bind
    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("Waiting for message...\n");

    addr_size = sizeof(client_addr);

    // 3 Receive message
    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr*)&client_addr, &addr_size);

    printf("Client: %s\n", buffer);

    // 4 Send reply
    strcpy(buffer, "Hello Client");
    sendto(sockfd, buffer, sizeof(buffer), 0,
           (struct sockaddr*)&client_addr, addr_size);

    close(sockfd);

    return 0;
}



// Algorithm for UDP Server

// Step 1: Start the program.

// Step 2: Create a socket using
// socket(AF_INET, SOCK_DGRAM, 0).

// Step 3: Define the server address using sockaddr_in structure.

// Step 4: Assign values to the server address:

// Set address family to AF_INET

// Set port number using htons()

// Set IP address using INADDR_ANY

// Step 5: Bind the socket to the server address using bind().

// Step 6: Wait to receive a message from the client using recvfrom().

// Step 7: Display the received message.

// Step 8: Send a reply to the client using sendto().

// Step 9: Close the socket using close().

// Step 10: Stop the program.