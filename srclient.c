#include <stdio.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

int main() {
    int sock, total_packets, window_size, base = 0, next_seq = 0, ack;
    int ack_received[100] = {0}; // Array to keep track of specific ACKs
    struct sockaddr_in server_addr;
    socklen_t addr_size;
    struct timeval tv;

    // --- USER INPUT ---
    printf("Enter total number of frames to send: ");
    scanf("%d", &total_packets);
    printf("Enter window size: ");
    scanf("%d", &window_size);
    // ------------------

    // 1 Create UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    // 2 Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr_size = sizeof(server_addr);

    // 3 Set a 2-second timeout on the socket
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    printf("\nStarting Selective Repeat transmission...\n");

    while (base < total_packets) {
        
        // 4 Send new frames entering the window
        while (next_seq < base + window_size && next_seq < total_packets) {
            printf("Sending Frame: %d\n", next_seq);
            sendto(sock, &next_seq, sizeof(next_seq), 0, (struct sockaddr*)&server_addr, addr_size);
            next_seq++;
        }

        // 5 Wait for ACK
        if (recvfrom(sock, &ack, sizeof(ack), 0, (struct sockaddr*)&server_addr, &addr_size) > 0) {
            printf("Received ACK: %d\n", ack);
            ack_received[ack] = 1; // Mark this specific frame as acknowledged

            // If the ACK is for the base frame, slide the window forward
            // past any other frames we already received out-of-order!
            if (ack == base) {
                while (ack_received[base] == 1) {
                    base++;
                }
            }
        } else {
            // 6 Timeout handling (SELECTIVE RETRANSMISSION)
            printf("\n[TIMEOUT] Timer expired!\n");
            
            // Loop through the current window. ONLY resend frames missing an ACK.
            for (int i = base; i < next_seq; i++) {
                if (ack_received[i] == 0) {
                    printf("-> Selectively Resending Frame: %d\n", i);
                    sendto(sock, &i, sizeof(i), 0, (struct sockaddr*)&server_addr, addr_size);
                }
            }
            printf("\n");
        }
    }
    
    printf("All %d frames sent successfully!\n", total_packets);
    
    // 7 Close socket
    close(sock);
    return 0;
}



// Algorithm for Selective Repeat Sender (Client)
// Step 1: Start the program.

// Step 2: Declare an array ack_received initialized to zeros to track individual acknowledgments.

// Step 3: Accept the total number of frames and the window size from the user.

// Step 4: Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).

// Step 5: Define the server address using the sockaddr_in structure:

// Set address family to AF_INET.

// Set port number using htons().

// Set server IP using inet_addr().

// Step 6: Attach a 2-second timeout to the socket using setsockopt() and SO_RCVTIMEO.

// Step 7: Initialize base = 0 and next_seq = 0. Loop while base is less than total_packets.

// Step 8: Inside the loop, check if next_seq is within the allowed window. If true, send the frame using sendto(), increment next_seq, and repeat until the window limit is reached.

// Step 9: Wait for an Acknowledgement using recvfrom().

// Step 10: Check the return value of recvfrom():

// If > 0 (Success): Mark the specific ACK in the tracking array (ack_received[ack] = 1). If the received ACK equals base, use a while loop to increment base past all consecutively received ACKs, sliding the window forward.

// If < 0 (Timeout): Display a timeout message. Loop from base to next_seq. Only retransmit frames i where ack_received[i] == 0.

// Step 11: Repeat from Step 7 until all frames are sent and acknowledged.

// Step 12: Close the socket using close().

// Step 13: Stop the program.