#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, j, head, direction;
    int request[50], seekTime = 0;
    int diskSize;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk request sequence:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the total disk size (number of cylinders): ");
    scanf("%d", &diskSize);

    printf("Enter head movement direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    // Sort the request sequence
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (request[i] > request[j]) {
                int temp = request[i];
                request[i] = request[j];
                request[j] = temp;
            }
        }
    }

    printf("\nDisk Scheduling using SCAN Algorithm:\n");
    printf("Head movement sequence:\n");

    if (direction == 1) { // moving right
        // First service requests greater than head
        for (i = 0; i < n; i++) {
            if (request[i] >= head) {
                printf("Head moves from %d to %d\n", head, request[i]);
                seekTime += abs(request[i] - head);
                head = request[i];
            }
        }
        // Move to end of disk
        printf("Head moves from %d to %d\n", head, diskSize - 1);
        seekTime += abs((diskSize - 1) - head);
        head = diskSize - 1;

        // Then service requests on the left side
        for (i = n - 1; i >= 0; i--) {
            if (request[i] < head) {
                printf("Head moves from %d to %d\n", head, request[i]);
                seekTime += abs(request[i] - head);
                head = request[i];
            }
        }
    } else { // moving left
        // First service requests smaller than head
        for (i = n - 1; i >= 0; i--) {
            if (request[i] <= head) {
                printf("Head moves from %d to %d\n", head, request[i]);
                seekTime += abs(request[i] - head);
                head = request[i];
            }
        }
        // Move to start of disk
        printf("Head moves from %d to %d\n", head, 0);
        seekTime += abs(head - 0);
        head = 0;

        // Then service requests on the right side
        for (i = 0; i < n; i++) {
            if (request[i] > head) {
                printf("Head moves from %d to %d\n", head, request[i]);
                seekTime += abs(request[i] - head);
                head = request[i];
            }
        }
    }

    printf("\nTotal Seek Time = %d\n", seekTime);
    printf("Average Seek Time = %.2f\n", (float)seekTime / n);

    return 0;
}
