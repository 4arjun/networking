#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {

    int sock;
    char buffer[1024];

    struct sockaddr_in server_addr;

    // 1 Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 2 Connect to server
    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 3 Send message
    strcpy(buffer, "Hello Server");
    send(sock, buffer, sizeof(buffer), 0);

    // 4 Receive reply
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Server says: %s\n", buffer);

    // 5 Close socket
    close(sock);

    return 0;
}


// Algorithm for TCP Client

// Step 1: Start the program.

// Step 2: Create a socket using
// socket(AF_INET, SOCK_STREAM, 0).

// Step 3: Define the server address using sockaddr_in.

// Step 4: Assign values to the server address:

// Set address family to AF_INET

// Set port number using htons()

// Set server IP using inet_addr()

// Step 5: Connect to the server using connect().

// Step 6: Send message to the server using send().

// Step 7: Receive response from the server using recv().

// Step 8: Display the received message.

// Step 9: Close the socket using close().

// Step 10: Stop the program.