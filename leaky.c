#include <stdio.h>

int main() {
    int capacity, leak_rate, storage = 0, dropped = 0;
    int n, i, incoming[50], sent;

    // 1 Accept bucket parameters
    printf("Enter bucket capacity: ");
    scanf("%d", &capacity);
    printf("Enter output (leak) rate: ");
    scanf("%d", &leak_rate);
    
    // 2 Accept incoming traffic
    printf("Enter number of time intervals: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter incoming packets at time %d: ", i + 1);
        scanf("%d", &incoming[i]);
    }

    printf("\nTime\tIncoming\tSent\tDropped\t\tRemaining\n");
    printf("----------------------------------------------------------\n");

    // 3 Process each time interval
    for (i = 0; i < n; i++) {
        
        // Check if adding incoming packets overflows the bucket
        if (incoming[i] + storage > capacity) {
            dropped = (incoming[i] + storage) - capacity;
            storage = capacity; // Bucket is full
        } else {
            dropped = 0;
            storage += incoming[i];
        }

        // 4 Leak (Send) packets at the constant output rate
        if (storage >= leak_rate) {
            sent = leak_rate;
            storage -= leak_rate;
        } else {
            // If fewer packets remain than the leak rate, send whatever is left
            sent = storage;
            storage = 0;
        }

        // 5 Display status for this time interval
        printf("%d\t%d\t\t%d\t%d\t\t%d\n", i + 1, incoming[i], sent, dropped, storage);
    }

    // 6 Empty any remaining packets in the bucket after all inputs stop
    while (storage > 0) {
        i++; // Increment time
        dropped = 0; // No new packets are coming, so nothing can drop
        
        if (storage >= leak_rate) {
            sent = leak_rate;
            storage -= leak_rate;
        } else {
            sent = storage;
            storage = 0;
        }
        
        printf("%d\t0\t\t%d\t%d\t\t%d\n", i, sent, dropped, storage);
    }

    return 0;
}


// Algorithm for Leaky Bucket
// Step 1: Start the program.

// Step 2: Declare necessary variables and an array to store the incoming packets.

// Step 3: Accept the capacity of the bucket and the constant leak_rate (output rate) from the user.

// Step 4: Accept the number of time intervals (n), and use a for loop to read the number of incoming packets for each time interval into the incoming[] array.

// Step 5: Initialize current storage = 0 and dropped = 0. Print the header for the output table.

// Step 6: Start a loop for i = 0 to n - 1 to process the incoming packets for each time interval.

// Step 7: Inside the loop, check if the bucket overflows:

// If incoming[i] + storage > capacity: Calculate the discarded packets (dropped = (incoming[i] + storage) - capacity) and set storage = capacity.

// If not: Set dropped = 0 and simply add the packets to the bucket (storage += incoming[i]).

// Step 8: Process the leak (transmission) at a constant rate:

// If storage >= leak_rate: Transmit packets equal to the leak rate (sent = leak_rate) and decrement storage by the leak rate (storage -= leak_rate).

// If storage < leak_rate: Transmit whatever is remaining in the bucket (sent = storage) and set storage = 0.

// Step 9: Display the Time, Incoming, Sent, Dropped, and Remaining storage for the current interval.

// Step 10: After the main loop ends, if there are still packets left in the bucket (storage > 0), use a while loop to continue leaking packets at the constant leak_rate. Print the status for each extra time step (with 0 incoming and 0 dropped packets) until the bucket is completely empty.

// Step 11: Stop the program.