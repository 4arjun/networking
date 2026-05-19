#include <stdio.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

int main() {
    int sock, total_packets, window_size, base = 0, next_seq = 0, ack;
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

    printf("\nStarting Go-Back-N transmission...\n");

    while (base < total_packets) {
        
        // 4 Send packets up to the window size limit
        while (next_seq < base + window_size && next_seq < total_packets) {
            printf("Sending Frame: %d\n", next_seq);
            sendto(sock, &next_seq, sizeof(next_seq), 0, (struct sockaddr*)&server_addr, addr_size);
            next_seq++;
        }

        // 5 Wait for ACK
        if (recvfrom(sock, &ack, sizeof(ack), 0, (struct sockaddr*)&server_addr, &addr_size) > 0) {
            // Check for cumulative ACK moving forward
            if (ack >= base) {
                printf("Received ACK: %d\n", ack);
                base = ack + 1; // Slide window forward
            }
        } else {
            // 6 Timeout handling
            // recvfrom returned -1 because the 2-second timer expired
            printf("\n[TIMEOUT] Timer expired! Going back to Frame %d\n\n", base);
            next_seq = base; // GO BACK N LOGIC: Reset next_seq back to base to resend window
        }
    }
    
    printf("All %d frames sent successfully!\n", total_packets);
    
    // 7 Close socket
    close(sock);
    return 0;
}



// Algorithm for Go-Back-N Sender (Client)
// Step 1: Start the program.

// Step 2: Accept the total number of frames and the window size from the user.

// Step 3: Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).

// Step 4: Define the server address using the sockaddr_in structure:

// Set address family to AF_INET.

// Set port number using htons().

// Set server IP using inet_addr().

// Step 5: Attach a 2-second timeout to the socket using setsockopt() and SO_RCVTIMEO.

// Step 6: Initialize variables: window start pointer base = 0 and next frame pointer next_seq = 0.

// Step 7: Loop while base is less than total_packets.

// Step 8: Inside the loop, check if next_seq is within the allowed window limit (next_seq < base + window_size). If true, send the frame using sendto(), increment next_seq, and repeat until the window is full.

// Step 9: Wait for an Acknowledgement using recvfrom().

// Step 10: Check the return value of recvfrom():

// If > 0 (Success): Check if the received cumulative ACK is valid (ACK >= base). If yes, slide the window forward by updating base = ACK + 1.

// If < 0 (Timeout): Display a timeout message. Execute the "Go-Back" logic by resetting next_seq = base (this forces the sender to retransmit the entire unacknowledged window in the next iteration).

// Step 11: Repeat from Step 7 until all frames are sent and acknowledged.

// Step 12: Close the socket using close().

// Step 13: Stop the program.