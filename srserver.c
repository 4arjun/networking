#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <time.h>

#define PORT 9011
#define MAX_FRAMES 10
#define WINDOW_SIZE 3
#define TIMEOUT 2      // seconds
#define MAX_RETRIES 5  // max retransmissions

int main() {
    srand(time(0)); // seed RNG

    int s_sock, c_sock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    s_sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(s_sock, (struct sockaddr *)&server, sizeof(server));
    listen(s_sock, 1);

    printf("Selective Repeat ARQ Server running\n");
    c_sock = accept(s_sock, (struct sockaddr *)&client, &len);

    int base = 0;
    int acked[MAX_FRAMES] = {0};
    int sent[MAX_FRAMES] = {0};
    int retries[MAX_FRAMES] = {0};

    char frame[50], ack[50];
    fd_set readfds;
    struct timeval tv;

    while (base < MAX_FRAMES) {

        // Send frames within window
        for (int i = base; i < base + WINDOW_SIZE && i < MAX_FRAMES; i++) {
            if (!sent[i]) {
                sprintf(frame, "FRAME %d", i);
                write(c_sock, frame, sizeof(frame));
                printf("Sent: %s\n", frame);
                sent[i] = 1;
                usleep(500000);  // 0.5s delay for demo
            }
        }

        // Wait for ACK
        FD_ZERO(&readfds);
        FD_SET(c_sock, &readfds);
        tv.tv_sec = TIMEOUT;
        tv.tv_usec = 0;

        int rv = select(c_sock + 1, &readfds, NULL, NULL, &tv);

        if (rv == 0) {
            // Timeout: retransmit only un-ACKed frames
            printf("⏰ Timeout! Retransmitting missing frames in window\n");
            for (int i = base; i < base + WINDOW_SIZE && i < MAX_FRAMES; i++) {
                if (!acked[i]) {
                    sent[i] = 0;          // mark for retransmission
                    retries[i]++;
                    if (retries[i] > MAX_RETRIES) {
                        // force send if too many retries
                        printf("⚡ Forced retransmission of FRAME %d\n", i);
                        sent[i] = 0;
                        retries[i] = 0;
                    }
                }
            }
        } else {
            int n = read(c_sock, ack, sizeof(ack));
            if (n <= 0) continue;

            int ack_no;
            sscanf(ack, "ACK %d", &ack_no);
            if (!acked[ack_no]) {
                acked[ack_no] = 1;
                printf("Received: %s\n", ack);
            }

            // Slide window
            while (base < MAX_FRAMES && acked[base]) {
                base++;
            }
        }
    }

    printf("All frames sent successfully (Selective Repeat)\n");
    close(c_sock);
    close(s_sock);
    return 0;
}



// Algorithm: Selective Repeat ARQ (Server / Sender)
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

// Bind the socket to the address using bind().

// Step 6

// Listen for incoming connections using listen().

// Step 7

// Accept a client connection using accept().

// Step 8

// Initialize variables:

// base → first frame in the sliding window

// acked[] → array to track acknowledged frames

// sent[] → array to track sent frames

// retries[] → array to count retransmissions.

// Step 9

// Repeat while base < MAX_FRAMES.

// Step 10 — Send Frames in Window

// For every frame i from base to base + WINDOW_SIZE:

// If the frame has not been sent:

// Create frame message "FRAME i".

// Send frame to client using write().

// Mark frame as sent.

// Introduce a small delay for demonstration.

// Step 11 — Wait for ACK

// Initialize file descriptor set.

// Add client socket to read set.

// Set timeout value.

// Call select() to wait for ACK.

// Step 12 — If Timeout Occurs

// If select() returns 0:

// Print timeout message.

// For each frame in the window:

// If frame is not acknowledged:

// Mark frame as not sent so it can be retransmitted.

// Increase retry counter.

// If retries exceed maximum limit:

// Force retransmission.

// Step 13 — If ACK is Received

// Read ACK message from client.

// Extract ACK number.

// Mark corresponding frame as acknowledged.

// Step 14 — Slide the Window

// While the first frame in the window is acknowledged:

// Increment base.

// Move window forward.

// Step 15

// Repeat Steps 10–14 until all frames are acknowledged.

// Step 16

// Print message that all frames are transmitted successfully.

// Step 17

// Close client and server sockets.

// Step 18

// End the program.
