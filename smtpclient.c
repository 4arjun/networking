#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock;
    char buffer[1024];
    struct sockaddr_in server_addr;

    // 1 Create TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // 2 Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 3 Connect to server
    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("\n--- SMTP Client Interactive Mode ---\n");
    printf("Expected Sequence to type:\n");
    printf(" 1. HELO yourdomain.com\n");
    printf(" 2. MAIL FROM:<you@example.com>\n");
    printf(" 3. RCPT TO:<friend@example.com>\n");
    printf(" 4. DATA\n");
    printf(" 5. Hello this is my email.\n");
    printf(" 6. QUIT\n\n");

    // 4 Receive initial 220 greeting from server
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Server: %s", buffer);

    // 5 Interactive Command Loop
    while (1) {
        printf("Client: ");
        memset(buffer, 0, sizeof(buffer));
        fgets(buffer, sizeof(buffer), stdin);
        
        // SMTP protocol STRICTLY requires commands to end with "\r\n"
        // fgets adds a standard "\n". This replaces it with "\r\n".
        buffer[strcspn(buffer, "\n")] = 0; 
        strcat(buffer, "\r\n");

        // Send the command you typed
        send(sock, buffer, strlen(buffer), 0);

        // Wait for the server's status code response
        memset(buffer, 0, sizeof(buffer));
        recv(sock, buffer, sizeof(buffer), 0);
        printf("Server: %s", buffer);

        // 6 If the server acknowledges the QUIT command (Status 221), break the loop
        if (strncmp(buffer, "221", 3) == 0) {
            break;
        }
    }

    // 7 Close socket
    close(sock);
    return 0;
}



// Algorithm for Interactive SMTP Client
// Step 1: Start the program.

// Step 2: Create a TCP socket using socket(AF_INET, SOCK_STREAM, 0).

// Step 3: Define the server address using the sockaddr_in structure:

// Set address family to AF_INET.

// Set port number using htons().

// Set server IP using inet_addr().

// Step 4: Establish a connection to the server using connect().

// Step 5: Clear the buffer and receive the initial 220 Ready greeting from the server using recv().

// Step 6: Enter an infinite loop (while(1)) to allow the user to type commands interactively.

// Step 7: Accept input from the user using fgets().

// Step 8: Format the input for the SMTP protocol by replacing the newline character (\n) with a Carriage Return and Line Feed (\r\n).

// Step 9: Send the formatted command to the server using send().

// Step 10: Receive the server's status code response using recv() and display it on the terminal.

// Step 11: Check if the received response starts with the 221 status code (which means the server accepted the QUIT command). If yes, break out of the loop.

// Step 12: If not 221, return to Step 7 to accept the next command from the user.

// Step 13: Close the socket using close().

// Step 14: Stop the program.