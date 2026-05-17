#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock;
    char buffer[1024];
    struct sockaddr_in server_addr;
    socklen_t addr_size;

    // 1 Create UDP socket (Notice SOCK_DGRAM)
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr_size = sizeof(server_addr);

    // 2 Get input from user
    memset(buffer, 0, sizeof(buffer)); // Clear buffer before typing
    printf("Enter a message to send to the UDP server: ");
    fgets(buffer, sizeof(buffer), stdin); 
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline character

    // 3 Send message using sendto()
    sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, addr_size);

    // 4 Receive reply using recvfrom()
    memset(buffer, 0, sizeof(buffer));
    recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&server_addr, &addr_size);
    printf("Server says: %s\n", buffer);

    // 5 Close socket
    close(sock);

    return 0;
}



// Algorithm for Interactive UDP Client
// Step 1: Start the program.

// Step 2: Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).

// Step 3: Define the server address using the sockaddr_in structure.

// Step 4: Assign values to the server address:

// Set address family to AF_INET.

// Set port number using htons().

// Set server IP using inet_addr().

// Step 5: Clear the data buffer using memset().

// Step 6: Accept input from the user using fgets() and strip the newline character.

// Step 7: Send the message to the server using sendto() and strlen().

// Step 8: Clear the data buffer again using memset().

// Step 9: Receive the response from the server using recvfrom().

// Step 10: Display the received message on the terminal.

// Step 11: Close the socket using close().

// Step 12: Stop the program.