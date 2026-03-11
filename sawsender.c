#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

int main() {

    int sock;
    int frame = 0, ack;
    struct sockaddr_in server;
    socklen_t addr_size;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(9002);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    addr_size = sizeof(server);

    // set 2 second timeout
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;

    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    while(frame < 5) {

        printf("Sending Frame %d\n", frame);

        sendto(sock, &frame, sizeof(frame), 0,
               (struct sockaddr*)&server, addr_size);

        int n = recvfrom(sock, &ack, sizeof(ack), 0,
                         (struct sockaddr*)&server, &addr_size);

        if(n < 0) {
            printf("Timeout! Resending Frame %d\n\n", frame);
        }
        else if(ack == frame) {
            printf("ACK %d received\n\n", ack);
            frame++;
        }
    }

    close(sock);
}

// Algorithm for Sender (Stop-and-Wait using UDP)

// Step 1: Start the program.

// Step 2: Create a UDP socket using
// socket(AF_INET, SOCK_DGRAM, 0).

// Step 3: Define the server address using sockaddr_in.

// Step 4: Assign server IP and port number.

// Step 5: Set a 2-second receive timeout using setsockopt() with SO_RCVTIMEO.

// Step 6: Initialize frame number.

// Step 7: Send the frame to the receiver using sendto().

// Step 8: Wait for acknowledgement using recvfrom().

// Step 9:

// If ACK is received → send next frame.

// If timeout occurs → retransmit the same frame.

// Step 10: Repeat until all frames are transmitted.

// Step 11: Close the socket.

// Step 12: Stop the program.