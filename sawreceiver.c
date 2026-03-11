#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {

    int sock, frame;
    struct sockaddr_in server, client;
    socklen_t addr_size;

    srand(time(NULL));

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(9002);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr*)&server, sizeof(server));

    addr_size = sizeof(client);

    printf("Receiver waiting for frames...\n");

    while(1) {

        recvfrom(sock, &frame, sizeof(frame), 0,
                 (struct sockaddr*)&client, &addr_size);

        printf("Received Frame %d\n", frame);

        int r = rand() % 2;

        if(r == 0) {
            printf("Sending ACK %d\n\n", frame);

            sendto(sock, &frame, sizeof(frame), 0,
                   (struct sockaddr*)&client, addr_size);
        }
        else {
            printf("ACK lost for Frame %d\n\n", frame);
        }
    }

    close(sock);
}


// Algorithm for Receiver (Stop-and-Wait using UDP)

// Step 1: Start the program.

// Step 2: Create a UDP socket.

// Step 3: Define server address using sockaddr_in.

// Step 4: Bind the socket using bind().

// Step 5: Wait to receive frame using recvfrom().

// Step 6: Display received frame.

// Step 7: Randomly simulate ACK loss using rand().

// Step 8:

// If ACK is not lost → send acknowledgement using sendto().

// If ACK is lost → do not send acknowledgement.

// Step 9: Repeat for all frames.

// Step 10: Close socket.

// Step 11: Stop the program.