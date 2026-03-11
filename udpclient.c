#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {

    int sockfd;
    char buffer[1024];
    struct sockaddr_in server_addr;
    socklen_t addr_size;

    // 1 Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 2 Send message
    strcpy(buffer, "Hello Server");
    sendto(sockfd, buffer, sizeof(buffer), 0,
           (struct sockaddr*)&server_addr, sizeof(server_addr));

    addr_size = sizeof(server_addr);

    // 3 Receive reply
    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr*)&server_addr, &addr_size);

    printf("Server: %s\n", buffer);

    close(sockfd);

    return 0;
}

// Algorithm for UDP Client

// Step 1: Start the program.

// Step 2: Create a socket using
// socket(AF_INET, SOCK_DGRAM, 0).

// Step 3: Define the server address using sockaddr_in.

// Step 4: Assign values to the server address:

// Set address family to AF_INET

// Set port number using htons()

// Set server IP address using inet_addr()

// Step 5: Send message to the server using sendto().

// Step 6: Wait to receive reply from the server using recvfrom().

// Step 7: Display the received message.

// Step 8: Close the socket using close().

// Step 9: Stop the program.