#include <stdio.h>

// 1 Structure to hold the routing table for each node
struct node {
    int dist[20];
    int next[20];
} route[20];

int main() {
    int costmat[20][20];
    int nodes, i, j, k, count;

    // 2 Accept number of nodes
    printf("Enter the number of nodes: ");
    scanf("%d", &nodes);

    // 3 Accept the cost matrix (Use 999 for infinity / no direct link)
    printf("Enter the cost matrix:\n");
    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            scanf("%d", &costmat[i][j]);
            
            // 4 Initialize routing tables with direct costs
            route[i].dist[j] = costmat[i][j];
            route[i].next[j] = j;
        }
    }

    // 5 Distance Vector / Bellman-Ford Algorithm Logic
    do {
        count = 0;
        for (i = 0; i < nodes; i++) {       // Source node
            for (j = 0; j < nodes; j++) {   // Destination node
                for (k = 0; k < nodes; k++) { // Intermediate node
                    
                    // If going through node 'k' is cheaper than the current path
                    if (route[i].dist[j] > costmat[i][k] + route[k].dist[j]) {
                        route[i].dist[j] = costmat[i][k] + route[k].dist[j];
                        route[i].next[j] = k; // Update next hop
                        count++; // Flag that a change occurred
                    }
                }
            }
        }
    } while (count != 0); // Repeat until no tables are updated

    // 6 Display final routing tables
    for (i = 0; i < nodes; i++) {
        printf("\nRouting Table for Router %d:\n", i + 1);
        printf("Dest\tNext Hop\tDist\n");
        for (j = 0; j < nodes; j++) {
            printf("%d\t%d\t\t%d\n", j + 1, route[i].next[j] + 1, route[i].dist[j]);
            // printf("To Node %d via %d : Distance %d\n", j + 1, route[i].next[j] + 1, route[i].dist[j]); 
        }
    }

    return 0;
}



// Algorithm for Distance Vector Routing

// Step 1: Start the program.

// Step 2: Declare a structure containing two arrays: one to store the shortest distances (dist) and one to store the next hop node (next). Create an array of this structure for all nodes.

// Step 3: Accept the total number of network nodes from the user.

// Step 4: Read the cost matrix from the user (where 0 is the distance to itself, and a large number like 999 represents infinity/no direct link).

// Step 5: Initialize the routing tables. For every source node i and destination node j, set the initial distance to the direct cost from the matrix, and set the initial next hop to j.

// Step 6: Start the Bellman-Ford iteration using a do-while loop. Initialize an update counter (count) to 0.

// Step 7: Loop through all combinations of source nodes (i), destination nodes (j), and intermediate neighbor nodes (k).

// Step 8: Check the Bellman-Ford condition:
// If the known distance from i to j is strictly greater than the cost from i to k plus the distance from k to j
// (dist[i][j] > cost[i][k] + dist[k][j]).

// Step 9: If the condition is true, update the shortest distance dist[i][j], set the next hop next[i][j] to k, and increment the count variable.

// Step 10: Repeat the do-while loop until count == 0 (meaning no further updates occurred and the network has stabilized).

// Step 11: Loop through the nodes and display the final formatted routing table (Destination, Next Hop, Distance) for each router.

// Step 12: Stop the program.