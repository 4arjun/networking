#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_sock;
    char buffer[1024];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    // 1 Create UDP socket (Notice SOCK_DGRAM)
    server_sock = socket(AF_INET, SOCK_DGRAM, 0);

    // 2 Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 3 Bind socket
    bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("UDP Server waiting for messages...\n");

    // 4 Receive message using recvfrom()
    // Notice: NO listen() and NO accept() are needed for UDP!
    addr_size = sizeof(client_addr);
    memset(buffer, 0, sizeof(buffer));
    recvfrom(server_sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &addr_size);
    printf("Client says: %s\n", buffer);

    // 5 Send response using sendto()
    strcpy(buffer, "Message received perfectly!");
    sendto(server_sock, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, addr_size);

    // 6 Close socket
    close(server_sock);

    return 0;
}



// Algorithm for Clean UDP Server
// Step 1: Start the program.

// Step 2: Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).

// Step 3: Define the server and client addresses using the sockaddr_in structure.

// Step 4: Assign values to the server address:

// Set address family to AF_INET.

// Set port number using htons().

// Set IP address using INADDR_ANY.

// Step 5: Bind the socket with the server address using bind().

// Step 6: Clear the data buffer using memset().

// Step 7: Receive the message from the client using recvfrom(). (Note: Unlike TCP, UDP skips listen() and accept()!)

// Step 8: Display the received message on the terminal.

// Step 9: Prepare the response message using strcpy().

// Step 10: Send the response back to the client using sendto() and strlen().

// Step 11: Close the server socket using close().

// Step 12: Stop the program.