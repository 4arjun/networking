#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr = { .sin_family = AF_INET, .sin_port = htons(9002) };
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));

    int expected = 0, recv_seq;
    socklen_t len = sizeof(addr);
    
    // Array to buffer out-of-order frames
    int received[100] = {0}; 

    srand(time(NULL)); // Seed the random number generator

    printf("\nSelective Repeat Receiver ready (20%% simulated packet loss). Waiting for frames...\n");
    
    // INFINITE LOOP: The server listens forever
    while (1) {
        recvfrom(sockfd, &recv_seq, sizeof(recv_seq), 0, (struct sockaddr*)&addr, &len);
        
        // --- SIMULATED PACKET LOSS (20% Chance) ---
        if (rand() % 10 < 1) {
            printf("[!] Network Drop Simulation: Frame %d lost!\n", recv_seq);
            continue; // Ignore the packet, do not send an ACK
        }
        // ------------------------------------------

        // Mark the frame as received and send an INDEPENDENT ACK
        if (received[recv_seq] == 0) {
            received[recv_seq] = 1;
            printf("Received Frame: %d\n", recv_seq);
        } else {
            printf("Received Duplicate Frame: %d\n", recv_seq);
        }
        
        // Send ACK for this exact frame (Not cumulative)
        sendto(sockfd, &recv_seq, sizeof(recv_seq), 0, (struct sockaddr*)&addr, len);

        // Deliver frames to the application layer if they are in order
        if (recv_seq == expected) {
            while (received[expected] == 1) {
                expected++; // Slide the receiver window forward
            }
            printf("--> (Application Layer expects next: %d)\n", expected);
        }
    }

    return 0;
}

// Algorithm for Infinite Selective Repeat Receiver
// Step 1: Start the program.

// Step 2: Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).

// Step 3: Define the receiver address using sockaddr_in structure and bind() it.

// Step 4: Initialize expected = 0 and an array received initialized to all zeros to buffer out-of-order packets. Seed the random number generator.

// Step 5: Enter an infinite loop (while(1)) to continuously listen for packets.

// Step 6: Wait to receive a frame using recvfrom().

// Step 7: Simulate packet loss by generating a random number. If dropped, use continue to return to Step 6 without sending an ACK.

// Step 8: Check if the received frame is new. If it is new (received[seq] == 0), mark it as received (received[seq] = 1) and display a success message.

// Step 9: Send an Independent ACK back for that exact sequence number using sendto().

// Step 10: Check if the sequence number matches expected. If yes, use a while loop to slide expected forward past any buffered, out-of-order frames that were received earlier.

// Step 11: Return to Step 6 to wait for the next frame.