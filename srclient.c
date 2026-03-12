#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 9011
#define MAX_FRAMES 10
#define FRAME_LOSS_PROB 20  // 20% chance frame is lost
#define ACK_LOSS_PROB 15    // 15% chance ACK is lost

int main() {
    srand(time(0)); 

    int sock;
    struct sockaddr_in server;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&server, sizeof(server));
    printf("Selective Repeat ARQ Client connected\n");

    char frame[50], ack[50];
    int received[MAX_FRAMES] = {0};
    int received_count = 0;

    while (received_count < MAX_FRAMES) {
        int n = read(sock, frame, sizeof(frame));
        if (n <= 0) continue;

        int seq;
        sscanf(frame, "FRAME %d", &seq);

        
        usleep(400000);

        // CASE 2: Frame lost (probabilistic)
        int rand_val = rand() % 100;
        if (rand_val < FRAME_LOSS_PROB) {
            printf("❌ Frame %d LOST\n", seq);
            continue;
        }

        if (!received[seq]) {
            printf("Received: %s\n", frame);
            received[seq] = 1;
            received_count++;
        }

        // CASE 3: ACK lost (probabilistic)
        rand_val = rand() % 100;
        if (rand_val < ACK_LOSS_PROB) {
            printf("❌ ACK for frame %d LOST\n", seq);
            continue;
        }

        // CASE 1: Normal
        sprintf(ack, "ACK %d", seq);
        write(sock, ack, sizeof(ack));
        printf("Sent: %s\n", ack);
    }

    printf("All frames received. Client exiting.\n");
    close(sock);
    return 0;
}



// Algorithm: Selective Repeat ARQ (Client / Receiver)
// Step 1

// Start the program.

// Step 2

// Initialize random number generator.

// Step 3

// Create socket using socket().

// Step 4

// Set server address and port.

// Step 5

// Connect to the server using connect().

// Step 6

// Initialize arrays:

// received[] → track received frames

// received_count → count received frames.

// Step 7

// Repeat while received_count < MAX_FRAMES.

// Step 8 — Receive Frame

// Read frame message from server.

// Extract frame sequence number.

// Step 9 — Simulate Frame Loss

// Generate random number.

// If it falls within frame loss probability:

// Display frame lost message.

// Do not process frame.

// Continue loop.

// Step 10 — Process Correct Frame

// If frame is not already received:

// Mark frame as received.

// Increment received count.

// Step 11 — Simulate ACK Loss

// Generate random number.

// If it falls within ACK loss probability:

// Display ACK lost message.

// Do not send ACK.

// Continue loop.

// Step 12 — Send ACK

// Create ACK message "ACK seq".

// Send ACK to server using write().

// Step 13

// Repeat Steps 8–12 until all frames are received.

// Step 14

// Display message indicating all frames received.

// Step 15

// Close socket.

// Step 16

// End program.