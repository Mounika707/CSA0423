#include <stdio.h>

int main() {
    int frames[10], temp[10], pages[30];
    int numPages, numFrames;
    int i, j, k, pageFaults = 0, flag, index = 0;

    // Input number of pages
    printf("Enter number of pages: ");
    scanf("%d", &numPages);

    // Input reference string
    printf("Enter the reference string (space separated):\n");
    for (i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    // Input number of frames
    printf("Enter number of frames: ");
    scanf("%d", &numFrames);

    // Initialize frames
    for (i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }

    printf("\nFIFO Page Replacement Simulation:\n");

    // Process each page
    for (i = 0; i < numPages; i++) {
        flag = 0;

        // Check if page is already in frame
        for (j = 0; j < numFrames; j++) {
            if (frames[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        // If not found, replace using FIFO
        if (flag == 0) {
            frames[index] = pages[i];
            index = (index + 1) % numFrames;
            pageFaults++;
        }

        // Print current frame status
        printf("Step %d: ", i + 1);
        for (k = 0; k < numFrames; k++) {
            if (frames[k] == -1)
                printf(" - ");
            else
                printf(" %d ", frames[k]);
        }
        if (flag == 0)
            printf(" (Page Fault)");
        else
            printf(" (Hit)");
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
