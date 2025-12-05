#include <stdio.h>
#include <string.h>

#define MAX_RECORDS 50
#define MAX_LENGTH  100

// Structure to represent a record
struct Record {
    int id;
    char data[MAX_LENGTH];
};

int main() {
    struct Record file[MAX_RECORDS];
    int n, i, choice, recordToRead;

    printf("Enter number of records in the file: ");
    scanf("%d", &n);

    if (n > MAX_RECORDS) {
        printf("Maximum records allowed is %d\n", MAX_RECORDS);
        return 0;
    }

    // Input records sequentially
    for (i = 0; i < n; i++) {
        file[i].id = i + 1;
        printf("Enter data for record %d: ", i + 1);
        scanf("%s", file[i].data);
    }

    printf("\nFile stored sequentially (physically and logically):\n");
    for (i = 0; i < n; i++) {
        printf("Record %d -> %s\n", file[i].id, file[i].data);
    }

    // Access simulation
    do {
        printf("\nEnter record number to access (1 to %d, 0 to exit): ", n);
        scanf("%d", &recordToRead);

        if (recordToRead == 0) {
            break;
        }

        if (recordToRead > 0 && recordToRead <= n) {
            printf("\nAccessing record %d requires reading all previous records:\n", recordToRead);
            for (i = 0; i < recordToRead; i++) {
                printf("Record %d -> %s\n", file[i].id, file[i].data);
            }
        } else {
            printf("Invalid record number!\n");
        }
    } while (1);

    printf("\nSimulation ended.\n");
    return 0;
}
