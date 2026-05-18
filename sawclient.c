#include <stdio.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <string.h>

int main() {
    int total_packets;

    // --- USER INPUT ---
    printf("Enter total number of frames to send: ");
    scanf("%d", &total_packets);
    // ------------------

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr = { .sin_family = AF_INET, .sin_port = htons(9002) };
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Set a 2-second timeout on the socket
    struct timeval tv = { .tv_sec = 2, .tv_usec = 0 };
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    int frame = 0, ack;
    socklen_t len = sizeof(addr);

    printf("\nStarting Stop-and-Wait transmission...\n");

    while (frame < total_packets) {
        // Send ONE frame and wait
        printf("Sending Frame: %d\n", frame);
        sendto(sockfd, &frame, sizeof(frame), 0, (struct sockaddr*)&addr, len);

        // Wait for ACK
        if (recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr*)&addr, &len) > 0) {
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
    return 0;
}


// Step 1: Start the program.

// Step 2: Accept the total number of frames to send from the user.

// Step 3: Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).

// Step 4: Define the receiver address using sockaddr_in structure (set AF_INET, htons(9002), and inet_addr("127.0.0.1")).

// Step 5: Attach a 2-second timeout to the socket using setsockopt() and SO_RCVTIMEO.

// Step 6: Initialize the current frame variable to 0.

// Step 7: Loop while frame is less than the total frames to send.

// Step 8: Inside the loop, send the current frame using sendto().

// Step 9: Wait for an Acknowledgement using recvfrom().

// Step 10: Check the return value of recvfrom():

// If > 0 (Success): Check if the received ACK matches the current frame. If yes, increment frame by 1.

// If < 0 (Timeout): Display a timeout message. Do not increment the frame (forcing a retransmission in the next iteration).

// Step 11: Once the loop finishes, display a success message.

// Step 12: Stop the program.