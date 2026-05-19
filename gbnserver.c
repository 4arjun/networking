#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main() {
    int server_sock, expected = 0, recv_seq, ack;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    // 1 Create UDP socket
    server_sock = socket(AF_INET, SOCK_DGRAM, 0);

    // 2 Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 3 Bind socket
    bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    srand(time(NULL)); // Seed the random number generator

    printf("\nGo-Back-N Receiver ready (20%% simulated packet loss). Waiting for frames...\n");
    
    addr_size = sizeof(client_addr);

    // 4 INFINITE LOOP: The server listens forever
    while (1) {
        // Receive frame and capture client address
        recvfrom(server_sock, &recv_seq, sizeof(recv_seq), 0, (struct sockaddr*)&client_addr, &addr_size);
        
        // --- SIMULATED PACKET LOSS (20% Chance) ---
        if (rand() % 10 < 2) {
            printf("[!] Network Drop Simulation: Frame %d lost!\n", recv_seq);
            continue; // Ignore the packet, do not send an ACK
        }
        // ------------------------------------------

        // Strict ordering check
        if (recv_seq == expected) {
            printf("Received Frame: %d\n", recv_seq);
            expected++; // Move to next expected frame
        } else {
            printf("Out of order! Expected %d, got %d\n", expected, recv_seq);
            // Do NOT increment expected.
        }
        
        // 5 Send Cumulative ACK (highest in-order frame received) back to the client
        ack = expected - 1; 
        sendto(server_sock, &ack, sizeof(ack), 0, (struct sockaddr*)&client_addr, addr_size);
    }

    // 6 Close socket (Unreachable due to infinite loop, but good practice)
    close(server_sock);
    return 0;
}


// Algorithm for Infinite Go-Back-N Receiver (Server)
// Step 1: Start the program.

// Step 2: Create a UDP server socket using socket(AF_INET, SOCK_DGRAM, 0).

// Step 3: Define the server address using the sockaddr_in structure:

// Set address family to AF_INET.

// Set port number using htons().

// Set IP address using INADDR_ANY.

// Step 4: Bind the socket with the server address using bind().

// Step 5: Initialize the strict expected frame variable to 0. Seed the random number generator.

// Step 6: Enter an infinite loop (while(1)) to continuously listen for packets.

// Step 7: Wait to receive a frame using recvfrom(). Ensure the sender's address is saved in client_addr.

// Step 8: Simulate packet loss by generating a random number. If the condition is met (e.g., 20% chance), drop the packet using the continue statement and return to Step 7.

// Step 9: Compare the received frame sequence with the strict expected frame sequence:

// If they match (In Order): Display a success message and increment expected by 1.

// If they do not match (Out of Order): Display an out-of-order error message. Do NOT increment expected.

// Step 10: Calculate the cumulative ACK to send (ack = expected - 1). This represents the highest frame received perfectly in order.

// Step 11: Send the calculated ACK back to the sender using sendto() and the stored client_addr.

// Step 12: Return to Step 7 to wait for the next frame.