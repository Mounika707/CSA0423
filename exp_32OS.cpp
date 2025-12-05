#include <stdio.h>

int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;
    for (i = 1; i < n; ++i) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int noOfFrames, noOfPages, frames[10], pages[30], time[10];
    int counter = 0, flag1, flag2, i, j, k, pos, faults = 0;

    printf("Enter number of frames: ");
    scanf("%d", &noOfFrames);

    printf("Enter number of pages: ");
    scanf("%d", &noOfPages);

    printf("Enter the page reference string:\n");
    for (i = 0; i < noOfPages; ++i) {
        scanf("%d", &pages[i]);
    }

    for (i = 0; i < noOfFrames; ++i) {
        frames[i] = -1;
    }

    printf("\nPage Reference String: ");
    for (i = 0; i < noOfPages; i++) {
        printf("%d ", pages[i]);
    }

    printf("\n\nSimulation of LRU Page Replacement:\n");

    for (i = 0; i < noOfPages; ++i) {
        flag1 = flag2 = 0;

        for (j = 0; j < noOfFrames; ++j) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            for (j = 0; j < noOfFrames; ++j) {
                if (frames[j] == -1) {
                    counter++;
                    faults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0) {
            pos = findLRU(time, noOfFrames);
            counter++;
            faults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }

        printf("\nAfter page %d: ", pages[i]);
        for (j = 0; j < noOfFrames; ++j) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
    }

    printf("\n\nTotal Page Faults = %d\n", faults);

    return 0;
}
