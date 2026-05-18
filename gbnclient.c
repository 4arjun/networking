#include <stdio.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <string.h>

int main() {
    int total_packets, window_size;

    // --- USER INPUT ---
    printf("Enter total number of frames to send: ");
    scanf("%d", &total_packets);
    printf("Enter window size: ");
    scanf("%d", &window_size);
    // ------------------

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr = { .sin_family = AF_INET, .sin_port = htons(9002) };
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Set a 2-second timeout on the socket
    struct timeval tv = { .tv_sec = 2, .tv_usec = 0 };
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    int base = 0, next_seq = 0, ack;
    socklen_t len = sizeof(addr);

    printf("\nStarting Go-Back-N transmission...\n");

    while (base < total_packets) {
        
        // 1. Send packets up to the window size limit
        while (next_seq < base + window_size && next_seq < total_packets) {
            printf("Sending Frame: %d\n", next_seq);
            sendto(sockfd, &next_seq, sizeof(next_seq), 0, (struct sockaddr*)&addr, len);
            next_seq++;
        }

        // 2. Wait for ACK
        if (recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr*)&addr, &len) > 0) {
            // Check for cumulative ACK moving forward
            if (ack >= base) {
                printf("Received ACK: %d\n", ack);
                base = ack + 1; // Slide window forward
            }
        } else {
            // 3. Timeout handling
            // recvfrom returned -1 because the 2-second timer expired
            printf("\n[TIMEOUT] Timer expired! Going back to Frame %d\n\n", base);
            next_seq = base; // GO BACK N LOGIC: Reset next_seq back to base to resend window
        }
    }
    
    printf("All %d frames sent successfully!\n", total_packets);
    return 0;
}


// Algorithm for Go-Back-N Sender
// Step 1: Start the program.

// Step 2: Accept the total number of frames and the window size from the user.

// Step 3: Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).

// Step 4: Define the receiver address using the sockaddr_in structure (set AF_INET, htons(9002), and inet_addr("127.0.0.1")).

// Step 5: Attach a 2-second timeout to the socket using setsockopt() and SO_RCVTIMEO.

// Step 6: Initialize the window start pointer (base = 0) and the next frame to send (next_seq = 0).

// Step 7: Loop while base is less than total_packets.

// Step 8: Inside the loop, check if next_seq is within the allowed window (next_seq < base + window_size). If true, send the frame using sendto(), increment next_seq, and repeat this step until the window is full.

// Step 9: Wait for an Acknowledgement using recvfrom().

// Step 10: Check the return value of recvfrom():

// If > 0 (Success): Check if the received ACK is valid (ACK >= base). If yes, slide the window forward by setting base = ACK + 1.

// If < 0 (Timeout): Display a timeout message. Execute the "Go-Back" logic by resetting next_seq = base (this forces the sender to retransmit the entire unacknowledged window).

// Step 11: Repeat from Step 7 until all frames are sent and acknowledged.

// Step 12: Stop the program.