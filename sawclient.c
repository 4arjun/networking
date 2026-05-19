#include <stdio.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

int main() {
    int sock, total_packets, frame = 0, ack;
    struct sockaddr_in server_addr;
    socklen_t addr_size;
    struct timeval tv;

    // --- USER INPUT ---
    printf("Enter total number of frames to send: ");
    scanf("%d", &total_packets);
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

    printf("\nStarting Stop-and-Wait transmission...\n");

    while (frame < total_packets) {
        
        // 4 Send ONE frame and wait
        printf("Sending Frame: %d\n", frame);
        sendto(sock, &frame, sizeof(frame), 0, (struct sockaddr*)&server_addr, addr_size);

        // 5 Wait for ACK
        if (recvfrom(sock, &ack, sizeof(ack), 0, (struct sockaddr*)&server_addr, &addr_size) > 0) {
            if (ack == frame) {
                printf("Received ACK: %d\n", ack);
                frame++; // Success! Move to the next frame
            }
        } else {
            // recvfrom returned -1 because the 2-second timer expired
            printf("\n[TIMEOUT] Timer expired! Resending Frame %d\n\n", frame);
        }
    }
    
    printf("All %d frames sent successfully!\n", total_packets);
    
    // 6 Close socket
    close(sock);
    return 0;
}



// Algorithm for Stop-and-Wait Sender (Client)
// Step 1: Start the program.

// Step 2: Accept the total number of frames to send from the user.

// Step 3: Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).

// Step 4: Define the server address using the sockaddr_in structure:

// Set address family to AF_INET.

// Set port number using htons().

// Set server IP using inet_addr().

// Step 5: Attach a 2-second timeout to the socket using setsockopt() and SO_RCVTIMEO.

// Step 6: Initialize the current frame variable to 0.

// Step 7: Loop while frame is less than total_packets.

// Step 8: Inside the loop, send the current frame using sendto().

// Step 9: Wait for an Acknowledgement using recvfrom().

// Step 10: Check the return value of recvfrom():

// If > 0 (Success): Check if the received ACK matches the current frame. If yes, increment frame by 1.

// If < 0 (Timeout): Display a timeout message. Do not increment the frame (forcing a retransmission in the next iteration).

// Step 11: Once the loop finishes, display a success message.

// Step 12: Close the socket using close().

// Step 13: Stop the program.