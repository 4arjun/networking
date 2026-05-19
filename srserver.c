#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main() {
    int server_sock, expected = 0, recv_seq;
    int received[100] = {0}; // Array to buffer out-of-order frames
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

    printf("\nSelective Repeat Receiver ready (20%% simulated packet loss). Waiting for frames...\n");
    
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

        // Mark the frame as received and print status
        if (received[recv_seq] == 0) {
            received[recv_seq] = 1;
            printf("Received Frame: %d\n", recv_seq);
        } else {
            printf("Received Duplicate Frame: %d\n", recv_seq);
        }
        
        // 5 Send INDEPENDENT ACK for this exact frame back to the specific client
        sendto(server_sock, &recv_seq, sizeof(recv_seq), 0, (struct sockaddr*)&client_addr, addr_size);

        // Deliver frames to the application layer if they are in order
        if (recv_seq == expected) {
            while (received[expected] == 1) {
                expected++; // Slide the receiver window forward
            }
            printf("--> (Application Layer expects next: %d)\n", expected);
        }
    }

    // 6 Close socket (Unreachable due to infinite loop, but good practice)
    close(server_sock);
    return 0;
}


// Algorithm for Selective Repeat Receiver (Server)
// Step 1: Start the program.

// Step 2: Declare an array received initialized to zeros to buffer out-of-order packets.

// Step 3: Create a UDP server socket using socket(AF_INET, SOCK_DGRAM, 0).

// Step 4: Define the server address using the sockaddr_in structure:

// Set address family to AF_INET.

// Set port number using htons().

// Set IP address using INADDR_ANY.

// Step 5: Bind the socket with the server address using bind(). Initialize expected = 0 and seed the random number generator.

// Step 6: Enter an infinite loop (while(1)) to continuously listen for packets.

// Step 7: Wait to receive a frame from the sender using recvfrom(). Ensure the sender's address is saved in client_addr.

// Step 8: Simulate packet loss by generating a random number. If the condition is met (e.g., 20% chance), ignore the packet using the continue statement and return to Step 7.

// Step 9: Check if the received frame is new (received[seq] == 0). If it is new, mark it as received in the array and display a success message. If it is already marked, display a duplicate message.

// Step 10: Send an Independent ACK back for that exact sequence number using sendto() to client_addr.

// Step 11: Check if the received sequence number matches expected. If yes, use a while loop to slide expected forward past any buffered, out-of-order frames received earlier.

// Step 12: Return to Step 7 to wait for the next frame.