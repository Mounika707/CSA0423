#include <stdio.h>

#define MAX_BLOCKS 20
#define MAX_PROCS 20

void firstFit(int blockSize[], int m, int procSize[], int n) {
    int allocation[MAX_PROCS];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= procSize[i]) {
                allocation[i] = j;
                blockSize[j] -= procSize[i];
                break;
            }
        }
    }

    printf("\n--- First Fit ---\n");
    printf("Proc No.\tProc Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, procSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSize[], int m, int procSize[], int n) {
    int allocation[MAX_PROCS];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= procSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= procSize[i];
        }
    }

    printf("\n--- Best Fit ---\n");
    printf("Proc No.\tProc Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, procSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSize[], int m, int procSize[], int n) {
    int allocation[MAX_PROCS];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int wstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= procSize[i]) {
                if (wstIdx == -1 || blockSize[j] > blockSize[wstIdx]) {
                    wstIdx = j;
                }
            }
        }
        if (wstIdx != -1) {
            allocation[i] = wstIdx;
            blockSize[wstIdx] -= procSize[i];
        }
    }

    printf("\n--- Worst Fit ---\n");
    printf("Proc No.\tProc Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, procSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void nextFit(int blockSize[], int m, int procSize[], int n) {
    int allocation[MAX_PROCS];
    for (int i = 0; i < n; i++) allocation[i] = -1;
    int start = 0;

    for (int i = 0; i < n; i++) {
        int count = 0;
        int idx = -1;
        while (count < m) {
            int j = (start + count) % m;
            if (blockSize[j] >= procSize[i]) {
                idx = j;
                break;
            }
            count++;
        }
        if (idx != -1) {
            allocation[i] = idx;
            blockSize[idx] -= procSize[i];
            start = idx;
        }
    }

    printf("\n--- Next Fit ---\n");
    printf("Proc No.\tProc Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, procSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int m, n;
    int blockSize[MAX_BLOCKS], procSize[MAX_PROCS];
    printf("Enter number of blocks: ");
    scanf("%d", &m);
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter sizes of blocks:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }
    printf("Enter process sizes:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &procSize[i]);
    }

    // make copies for each algorithm so original block sizes remain unchanged
    int bs1[MAX_BLOCKS], bs2[MAX_BLOCKS], bs3[MAX_BLOCKS], bs4[MAX_BLOCKS];
    for (int i = 0; i < m; i++) {
        bs1[i] = blockSize[i];
        bs2[i] = blockSize[i];
        bs3[i] = blockSize[i];
        bs4[i] = blockSize[i];
    }

    firstFit(bs1, m, procSize, n);
    bestFit(bs2, m, procSize, n);
    worstFit(bs3, m, procSize, n);
    nextFit(bs4, m, procSize, n);

    return 0;
}
