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

    // 3 Get input from user and send
    memset(buffer, 0, sizeof(buffer)); // Clear buffer before typing
    printf("Enter a message to send to the server: ");
    fgets(buffer, sizeof(buffer), stdin); 
    
    // fgets adds a newline (\n) at the end. This line removes it.
    buffer[strcspn(buffer, "\n")] = 0; 

    send(sock, buffer, strlen(buffer), 0);

    // 4 Receive reply
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Server says: %s\n", buffer);

    // 5 Close socket
    close(sock);

    return 0;
}


// Algorithm for Interactive TCP Client
// Step 1: Start the program.

// Step 2: Create a socket using socket(AF_INET, SOCK_STREAM, 0).

// Step 3: Define the server address using the sockaddr_in structure.

// Step 4: Assign values to the server address:

// Set address family to AF_INET.

// Set port number using htons().

// Set server IP using inet_addr().

// Step 5: Connect to the server using connect().

// Step 6: Clear the data buffer using memset().

// Step 7: Accept input from the user using fgets() and strip the newline character.

// Step 8: Send the input message to the server using send() and strlen().

// Step 9: Clear the data buffer again using memset().

// Step 10: Receive the response from the server using recv().

// Step 11: Display the received message on the terminal.

// Step 12: Close the socket using close().

// Step 13: Stop the program.