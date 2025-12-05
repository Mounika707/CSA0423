#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char data[100];

    // 1. Create and write to a file
    fp = fopen("example.txt", "w");  // "w" creates or overwrites
    if (fp == NULL) {
        perror("Error creating file");
        return 1;
    }
    fprintf(fp, "Hello, this is a file management demo!\n");
    fprintf(fp, "We are writing data into the file.\n");
    fclose(fp);
    printf("File created and data written successfully.\n");

    // 2. Read from the file
    fp = fopen("example.txt", "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return 1;
    }
    printf("\nReading file contents:\n");
    while (fgets(data, sizeof(data), fp) != NULL) {
        printf("%s", data);
    }
    fclose(fp);

    // 3. Append data to the file
    fp = fopen("example.txt", "a");  // "a" appends
    if (fp == NULL) {
        perror("Error opening file for appending");
        return 1;
    }
    fprintf(fp, "This line is appended to the file.\n");
    fclose(fp);
    printf("\nData appended successfully.\n");

    // 4. Read again after append
    fp = fopen("example.txt", "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return 1;
    }
    printf("\nReading file contents after append:\n");
    while (fgets(data, sizeof(data), fp) != NULL) {
        printf("%s", data);
    }
    fclose(fp);

    // 5. Delete the file
    if (remove("example.txt") == 0) {
        printf("\nFile deleted successfully.\n");
    } else {
        perror("Error deleting file");
    }

    return 0;
}
