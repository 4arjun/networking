#include <stdio.h>

struct router
{
    int cost[20];
    int from[20];
} routingTable[20];

int main()
{
    int costmat[20][20];
    int routers, i, j, k;
    int otherShorterPathExists;

    printf("Enter number of routers: ");
    scanf("%d",&routers);

    printf("Enter cost matrix:\n");

    for(i=0;i<routers;i++)
    {
        for(j=0;j<routers;j++)
        {
            scanf("%d",&costmat[i][j]);

            routingTable[i].cost[j] = costmat[i][j];
            routingTable[i].from[j] = j;
        }
    }

    do
    {
        otherShorterPathExists = 0;

        for(i=0;i<routers;i++)
        {
            for(j=0;j<routers;j++)
            {
                for(k=0;k<routers;k++)
                {

                    if(routingTable[i].cost[j] >
                       costmat[i][k] + routingTable[k].cost[j])
                    {
                        routingTable[i].cost[j] =
                        costmat[i][k] + routingTable[k].cost[j];

                        routingTable[i].from[j] = k;

                        otherShorterPathExists = 1;
                    }

                }
            }
        }

    } while(otherShorterPathExists);

    printf("\nRouting Tables:\n");

    for(i=0;i<routers;i++)
    {
        printf("\nRouter %d\n",i+1);

        for(j=0;j<routers;j++)
        {
            printf("Router %d via %d distance %d\n",
            j+1,
            routingTable[i].from[j]+1,
            routingTable[i].cost[j]);
        }
    }

    return 0;
}


// Algorithm: Distance Vector Routing (Using Routing Table Structure)
// Step 1

// Start the program.

// Step 2

// Define a structure router that contains two arrays:

// cost[] → stores the distance to each destination router

// from[] → stores the next hop router.

// Step 3

// Declare variables:

// costmat[][] → to store the cost matrix

// routers → number of routers

// i, j, k → loop counters

// otherShorterPathExists → flag to check if routing table changes.

// Step 4

// Read the number of routers from the user.

// Step 5

// Read the cost matrix.

// For each router i and destination j:

// Set initial cost:

// routingTable[i].cost[j] = costmat[i][j]

// Set next hop:

// routingTable[i].from[j] = j

// This assumes direct paths initially.

// Step 6

// Apply the Distance Vector update rule repeatedly.

// Set:

// otherShorterPathExists = 0
// Step 7

// For every router i, destination j, and intermediate router k:

// Check if a shorter path exists:

// routingTable[i].cost[j] > costmat[i][k] + routingTable[k].cost[j]
// Step 8

// If a shorter path is found:

// Update distance:

// routingTable[i].cost[j] =
// costmat[i][k] + routingTable[k].cost[j]

// Update next hop:

// routingTable[i].from[j] = k

// Set:

// otherShorterPathExists = 1
// Step 9

// Repeat Steps 6–8 until otherShorterPathExists becomes 0
// (no more shorter paths exist).

// Step 10

// Print the routing table for each router:

// For each router i:

// Display destination router

// Display next hop router:

// routingTable[i].from[j] + 1

// Display minimum distance:

// routingTable[i].cost[j]

// Example output:

// Router 3 via 2 distance 3
// Step 11

// End the program.