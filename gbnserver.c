#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <time.h>

#define PORT 9012
#define MAX_FRAMES 10
#define WINDOW_SIZE 3
#define TIMEOUT 2

int main() {

    srand(time(0));

    int s_sock, c_sock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    s_sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(s_sock,(struct sockaddr*)&server,sizeof(server));
    listen(s_sock,1);

    printf("Go Back N ARQ Server running\n");

    c_sock = accept(s_sock,(struct sockaddr*)&client,&len);

    int base = 0;
    int nextseq = 0;

    char frame[50], ack[50];

    fd_set readfds;
    struct timeval tv;

    while(base < MAX_FRAMES) {

        // Send frames within window
        while(nextseq < base + WINDOW_SIZE && nextseq < MAX_FRAMES) {

            sprintf(frame,"FRAME %d",nextseq);
            write(c_sock,frame,sizeof(frame));

            printf("Sent: %s\n",frame);

            nextseq++;

            usleep(500000);
        }

        FD_ZERO(&readfds);
        FD_SET(c_sock,&readfds);

        tv.tv_sec = TIMEOUT;
        tv.tv_usec = 0;

        int rv = select(c_sock+1,&readfds,NULL,NULL,&tv);

        if(rv == 0) {

            printf("⏰ Timeout! Retransmitting from FRAME %d\n",base);

            nextseq = base;

        } else {

            int n = read(c_sock,ack,sizeof(ack));
            if(n <= 0) continue;

            int ack_no;
            sscanf(ack,"ACK %d",&ack_no);

            printf("Received: %s\n",ack);

            base = ack_no + 1;
        }
    }

    printf("All frames sent successfully (Go Back N)\n");

    close(c_sock);
    close(s_sock);

    return 0;
}


// Algorithm: Go-Back-N ARQ (Server / Sender)
// Step 1

// Start the program.

// Step 2

// Initialize random number generator using srand().

// Step 3

// Create a TCP socket using socket().

// Step 4

// Configure server address:

// Set address family to AF_INET

// Set port number

// Set IP address to INADDR_ANY.

// Step 5

// Bind the socket using bind().

// Step 6

// Listen for incoming connections using listen().

// Step 7

// Accept a client connection using accept().

// Step 8

// Initialize variables:

// base → first unacknowledged frame

// nextseq → next frame to be sent.

// Step 9

// Repeat while base < MAX_FRAMES.

// Step 10 — Send Frames in Window

// While:

// nextseq < base + WINDOW_SIZE

// and nextseq < MAX_FRAMES:

// Create frame "FRAME nextseq".

// Send frame to client using write().

// Print sent frame.

// Increment nextseq.

// Add a small delay.

// Step 11 — Wait for ACK

// Initialize file descriptor set.

// Add client socket to read set.

// Set timeout using TIMEOUT.

// Call select() to wait for acknowledgement.

// Step 12 — Timeout Handling

// If select() returns 0 (timeout):

// Print timeout message.

// Set:

// nextseq = base

// Retransmit all frames starting from base.

// (This is why it is called Go-Back-N.)

// Step 13 — If ACK is Received

// Read ACK message from client.

// Extract acknowledgement number.

// Update sender window:

// base = ack_no + 1

// Slide window forward.

// Step 14

// Repeat Steps 10–13 until all frames are acknowledged.

// Step 15

// Display message indicating all frames were sent successfully.

// Step 16

// Close client and server sockets.

// Step 17

// End program.