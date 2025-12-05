#include <stdio.h>

int findOptimal(int pages[], int frames[], int n, int index, int noOfFrames) {
    int i, j, farthest = index, pos = -1;
    for (i = 0; i < noOfFrames; i++) {
        int found = 0;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                found = 1;
                break;
            }
        }
        if (!found) {
            return i; // If a page is never used again, replace it immediately
        }
    }
    if (pos == -1)
        return 0;
    else
        return pos;
}

int main() {
    int noOfFrames, noOfPages, frames[10], pages[30];
    int i, j, k, pos, faults = 0, flag, filled = 0;

    printf("Enter number of frames: ");
    scanf("%d", &noOfFrames);

    printf("Enter number of pages: ");
    scanf("%d", &noOfPages);

    printf("Enter the page reference string:\n");
    for (i = 0; i < noOfPages; i++) {
        scanf("%d", &pages[i]);
    }

    for (i = 0; i < noOfFrames; i++) {
        frames[i] = -1;
    }

    printf("\nPage Reference String: ");
    for (i = 0; i < noOfPages; i++) {
        printf("%d ", pages[i]);
    }

    printf("\n\nSimulation of Optimal Page Replacement:\n");

    for (i = 0; i < noOfPages; i++) {
        flag = 0;

        // Check if page is already in frame
        for (j = 0; j < noOfFrames; j++) {
            if (frames[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            if (filled < noOfFrames) {
                frames[filled++] = pages[i];
                faults++;
            } else {
                pos = findOptimal(pages, frames, noOfPages, i + 1, noOfFrames);
                frames[pos] = pages[i];
                faults++;
            }
        }

        printf("\nAfter page %d: ", pages[i]);
        for (j = 0; j < noOfFrames; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
    }

    printf("\n\nTotal Page Faults = %d\n", faults);

    return 0;
}
