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

    // 1 Create TCP socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);

    // 2 Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 3 Bind socket
    bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 4 Listen for clients
    listen(server_sock, 5);
    printf("SMTP Server waiting for connections on port 9002...\n");

    // 5 Accept connection
    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    printf("\n--- Client Connected ---\n\n");

    // 6 Send initial 220 greeting
    strcpy(buffer, "220 smtp.localdomain Ready\r\n");
    send(client_sock, buffer, strlen(buffer), 0);
    printf("Server: %s", buffer);

    // 7 Process HELO
    memset(buffer, 0, sizeof(buffer));
    recv(client_sock, buffer, sizeof(buffer), 0);
    printf("Client: %s", buffer);
    strcpy(buffer, "250 OK Hello\r\n");
    send(client_sock, buffer, strlen(buffer), 0);

    // 8 Process MAIL FROM
    memset(buffer, 0, sizeof(buffer));
    recv(client_sock, buffer, sizeof(buffer), 0);
    printf("Client: %s", buffer);
    strcpy(buffer, "250 OK Sender Accepted\r\n");
    send(client_sock, buffer, strlen(buffer), 0);

    // 9 Process RCPT TO
    memset(buffer, 0, sizeof(buffer));
    recv(client_sock, buffer, sizeof(buffer), 0);
    printf("Client: %s", buffer);
    strcpy(buffer, "250 OK Recipient Accepted\r\n");
    send(client_sock, buffer, strlen(buffer), 0);

    // 10 Process DATA
    memset(buffer, 0, sizeof(buffer));
    recv(client_sock, buffer, sizeof(buffer), 0);
    printf("Client: %s", buffer);
    strcpy(buffer, "354 End data with <CR><LF>.<CR><LF>\r\n");
    send(client_sock, buffer, strlen(buffer), 0);

    // 11 Process Email Content
    memset(buffer, 0, sizeof(buffer));
    recv(client_sock, buffer, sizeof(buffer), 0);
    printf("Client: %s", buffer);
    strcpy(buffer, "250 OK Message Accepted for Delivery\r\n");
    send(client_sock, buffer, strlen(buffer), 0);

    // 12 Process QUIT
    memset(buffer, 0, sizeof(buffer));
    recv(client_sock, buffer, sizeof(buffer), 0);
    printf("Client: %s", buffer);
    strcpy(buffer, "221 smtp.localdomain closing connection\r\n");
    send(client_sock, buffer, strlen(buffer), 0);

    // 13 Close sockets
    close(client_sock);
    close(server_sock);

    return 0;
}



// Algorithm for SMTP Server
// Step 1: Start the program.

// Step 2: Create a main TCP server socket using socket(AF_INET, SOCK_STREAM, 0).

// Step 3: Define the server address using the sockaddr_in structure (set AF_INET, htons(9002), and INADDR_ANY).

// Step 4: Bind the socket to the port using bind().

// Step 5: Put the server in listening mode using listen().

// Step 6: Accept an incoming client connection using accept() and store the dedicated client socket.

// Step 7: Send the initial 220 Ready greeting to the client.

// Step 8: Receive the HELO command using recv() and reply with 250 OK.

// Step 9: Receive the MAIL FROM command and reply with 250 OK.

// Step 10: Receive the RCPT TO command and reply with 250 OK.

// Step 11: Receive the DATA command and reply with 354 End data with . to instruct the client to send the body.

// Step 12: Receive the email body content (ending in .) and reply with 250 OK Message Accepted.

// Step 13: Receive the QUIT command and reply with 221 closing connection.

// Step 14: Close the client socket and the main server socket using close().

// Step 15: Stop the program.