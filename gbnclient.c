#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 9012
#define MAX_FRAMES 10
#define FRAME_LOSS_PROB 20
#define ACK_LOSS_PROB 15

int main() {

    srand(time(0));

    int sock;
    struct sockaddr_in server;

    sock = socket(AF_INET,SOCK_STREAM,0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock,(struct sockaddr*)&server,sizeof(server));

    printf("Go Back N ARQ Client connected\n");

    char frame[50], ack[50];

    int expected = 0;

    while(expected < MAX_FRAMES) {

        int n = read(sock,frame,sizeof(frame));
        if(n <= 0) continue;

        int seq;
        sscanf(frame,"FRAME %d",&seq);

        usleep(400000);

        // Frame loss simulation
        int rand_val = rand()%100;

        if(rand_val < FRAME_LOSS_PROB) {

            printf("❌ Frame %d LOST\n",seq);
            continue;
        }

        // Correct frame received
        if(seq == expected) {

            printf("Received: %s\n",frame);

            rand_val = rand()%100;

            if(rand_val < ACK_LOSS_PROB) {

                printf("❌ ACK for frame %d LOST\n",seq);
                continue;
            }

            sprintf(ack,"ACK %d",seq);
            write(sock,ack,sizeof(ack));

            printf("Sent: %s\n",ack);

            expected++;
        }

        // Out of order frame
        else {

            printf("⚠ Discarded FRAME %d (Expecting %d)\n",seq,expected);

            sprintf(ack,"ACK %d",expected-1);
            write(sock,ack,sizeof(ack));

            printf("Resent: %s\n",ack);
        }
    }

    printf("All frames received. Client exiting.\n");

    close(sock);

    return 0;
}


// Algorithm: Go-Back-N ARQ (Client / Receiver)
// Step 1

// Start the program.

// Step 2

// Initialize random number generator.

// Step 3

// Create a socket using socket().

// Step 4

// Set server IP and port.

// Step 5

// Connect to the server using connect().

// Step 6

// Initialize variable:

// expected = 0

// (This stores the next expected frame number.)

// Step 7

// Repeat while expected < MAX_FRAMES.

// Step 8 — Receive Frame

// Read frame from server.

// Extract sequence number.

// Step 9 — Simulate Frame Loss

// Generate random number.

// If random number is less than FRAME_LOSS_PROB:

// Print frame lost message.

// Discard frame.

// Continue loop.

// Step 10 — Correct Frame Received

// If received frame number equals expected:

// Print received frame.

// Simulate ACK loss using probability.

// If ACK is not lost:

// Create acknowledgement "ACK seq".

// Send ACK to server.

// Increment expected.

// Step 11 — Out-of-Order Frame

// If frame number is not equal to expected:

// Discard frame.

// Send ACK for the last correctly received frame.

// Example:

// ACK expected-1
// Step 12

// Repeat Steps 8–11 until all frames are received.

// Step 13

// Display message that all frames are received.

// Step 14

// Close socket.

// Step 15

// End program.
