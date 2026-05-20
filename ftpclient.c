#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


// client requests a specific file, and the server reads that file from its hard drive and sends the contents back to the client over the network.
int main() {
    int sock, bytes_received;
    char buffer[1024];
    struct sockaddr_in server_addr;

    // 1 Create TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // 2 Configure server address & Connect
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 3 Get filename from user
    memset(buffer, 0, sizeof(buffer));
    printf("Enter filename to request from server: ");
    fgets(buffer, sizeof(buffer), stdin);
    
    // Remove the newline character added by fgets
    buffer[strcspn(buffer, "\n")] = 0;

    // 4 Send filename to server
    send(sock, buffer, strlen(buffer), 0);

    printf("\n--- File Contents from Server ---\n");

    // 5 Receive and print file contents in a loop
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
        
        // If bytes_received is 0, the server finished sending and closed the connection
        if (bytes_received <= 0) {
            break; 
        }
        
        // Print the chunk of the file we just received
        printf("%s", buffer);
    }
    
    printf("\n---------------------------------\n");

    // 6 Close socket
    close(sock);
    return 0;
}


// Algorithm for FTP Client
// Step 1: Start the program.
// Step 2: Create a TCP socket using socket(AF_INET, SOCK_STREAM, 0).
// Step 3: Define the server address (IP 127.0.0.1, Port 9002) and establish a connection using connect().
// Step 4: Prompt the user to enter the name of the file they want to download. Use fgets() to read the input and remove the trailing newline character.
// Step 5: Send the requested filename to the server using send().
// Step 6: Enter an infinite while(1) loop to receive the file contents.
// Step 7: Inside the loop, use recv() to receive incoming data chunks.
// Step 8: Check the return value of recv(). If it is <= 0, the server has finished sending the file and closed the connection; break out of the loop.
// Step 9: If data was received, print the buffer to the screen.
// Step 10: After the loop finishes, close the socket using close().
// Step 11: Stop the program.