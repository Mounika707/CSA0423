#include <stdio.h>

#define MAX_BLOCKS 50

int main() {
    int indexBlock[MAX_BLOCKS];   // index block storing pointers to file blocks
    int fileBlocks[MAX_BLOCKS];   // simulated file blocks
    int n, i, choice, blockToRead;

    printf("Enter number of blocks in the file: ");
    scanf("%d", &n);

    if (n > MAX_BLOCKS) {
        printf("Maximum blocks allowed is %d\n", MAX_BLOCKS);
        return 0;
    }

    // Input data for each block
    for (i = 0; i < n; i++) {
        printf("Enter data for block %d: ", i + 1);
        scanf("%d", &fileBlocks[i]);
        indexBlock[i] = i; // index block points to the block number
    }

    printf("\nIndex Block (pointers to file blocks):\n");
    for (i = 0; i < n; i++) {
        printf("Index[%d] -> Block %d\n", i, indexBlock[i]);
    }

    printf("\nFile Blocks (data stored in each block):\n");
    for (i = 0; i < n; i++) {
        printf("Block %d -> Data: %d\n", i, fileBlocks[i]);
    }

    // Access simulation
    do {
        printf("\nEnter block number to access (0 to %d, -1 to exit): ", n - 1);
        scanf("%d", &blockToRead);

        if (blockToRead == -1) {
            break;
        }

        if (blockToRead >= 0 && blockToRead < n) {
            int physicalBlock = indexBlock[blockToRead];
            printf("Accessing Block %d via Index[%d] -> Data: %d\n",
                   physicalBlock, blockToRead, fileBlocks[physicalBlock]);
        } else {
            printf("Invalid block number!\n");
        }
    } while (1);

    printf("\nSimulation ended.\n");
    return 0;
}
