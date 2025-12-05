#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 50

// Structure to represent a disk block
struct Block {
    int data;
    int next; // pointer to next block (-1 if none)
};

int main() {
    struct Block disk[MAX_BLOCKS];
    int n, i;
    int start, end;

    printf("Enter number of blocks in the file: ");
    scanf("%d", &n);

    if (n > MAX_BLOCKS) {
        printf("Maximum blocks allowed is %d\n", MAX_BLOCKS);
        return 0;
    }

    // Input data for each block
    for (i = 0; i < n; i++) {
        printf("Enter data for block %d: ", i);
        scanf("%d", &disk[i].data);
        if (i < n - 1)
            disk[i].next = i + 1; // link to next block
        else
            disk[i].next = -1;    // last block
    }

    // Directory pointers
    start = 0;
    end = n - 1;

    printf("\nDirectory contains:\n");
    printf("Start block pointer -> %d\n", start);
    printf("End block pointer   -> %d\n", end);

    printf("\nLinked Allocation (block chain):\n");
    i = start;
    while (i != -1) {
        printf("Block %d -> Data: %d, Next: %d\n", i, disk[i].data, disk[i].next);
        i = disk[i].next;
    }

    // Access simulation
    int blockToRead;
    do {
        printf("\nEnter block number to access (0 to %d, -1 to exit): ", n - 1);
        scanf("%d", &blockToRead);

        if (blockToRead == -1) {
            break;
        }

        if (blockToRead >= 0 && blockToRead < n) {
            printf("Accessing Block %d -> Data: %d\n", blockToRead, disk[blockToRead].data);
        } else {
            printf("Invalid block number!\n");
        }
    } while (1);

    printf("\nSimulation ended.\n");
    return 0;
}
