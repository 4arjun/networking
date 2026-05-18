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

    srand(time(NULL)); // Seed the random number generator

    printf("\nReceiver ready (with 20%% simulated packet loss). Waiting for frames...\n");
    
    // INFINITE LOOP: The server listens forever
    while (1) {
        recvfrom(sockfd, &recv_seq, sizeof(recv_seq), 0, (struct sockaddr*)&addr, &len);
        
        // --- SIMULATED PACKET LOSS (20% Chance) ---
        if (rand() % 10 < 2) {
            printf("[!] Network Drop Simulation: Frame %d lost!\n", recv_seq);
            continue; // Ignore the packet, do not send an ACK
        }
        // ------------------------------------------

        if (recv_seq == expected) {
            printf("Received Frame: %d\n", recv_seq);
            expected++; // Move to next expected frame
        } else {
            printf("Duplicate/Out of order! Expected %d, got %d\n", expected, recv_seq);
        }
        
        // Send ACK for the highest successfully received frame
        int ack = expected - 1; 
        sendto(sockfd, &ack, sizeof(ack), 0, (struct sockaddr*)&addr, len);
    }

    return 0;
}


// Step 1: Start the program.

// Step 2: Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).

// Step 3: Define the receiver address using sockaddr_in structure and bind() it to the socket.

// Step 4: Initialize the expected frame variable to 0. Seed the random number generator for simulation.

// Step 5: Enter an infinite loop (while(1)) to continuously listen for packets.

// Step 6: Wait to receive a frame using recvfrom().

// Step 7: Simulate packet loss by generating a random number. If the condition is met (e.g., 20% chance), ignore the packet using the continue statement and return to Step 6.

// Step 8: Compare the received frame sequence with the expected frame.

// If they match: Display success message and increment expected by 1.

// If they do not match: Display a duplicate/error message and do NOT increment expected.

// Step 9: Calculate the ACK to send (ack = expected - 1).

// Step 10: Send the calculated ACK back to the sender using sendto().

// Step 11: Return to Step 6 to wait for the next frame.