#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, head;
    int request[50];
    int seekTime = 0;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk request sequence:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("\nDisk Scheduling using First Come First Served (FCFS):\n");
    printf("Head movement sequence:\n");

    // Process requests in the order they arrive
    for (i = 0; i < n; i++) {
        printf("Head moves from %d to %d\n", head, request[i]);
        seekTime += abs(request[i] - head);
        head = request[i];
    }

    printf("\nTotal Seek Time = %d\n", seekTime);
    printf("Average Seek Time = %.2f\n", (float)seekTime / n);

    return 0;
}
