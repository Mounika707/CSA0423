#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char line[1024];
    char *pattern;
    char *filename;
    int lineNumber = 0;
    int found = 0;

    // Check arguments: need pattern and filename
    if (argc < 3) {
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
        return 1;
    }

    pattern = argv[1];
    filename = argv[2];

    // Open file
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read file line by line
    while (fgets(line, sizeof(line), fp) != NULL) {
        lineNumber++;
        if (strstr(line, pattern) != NULL) {
            printf("Line %d: %s", lineNumber, line);
            found = 1;
        }
    }

    if (!found) {
        printf("Pattern '%s' not found in file '%s'.\n", pattern, filename);
    }

    fclose(fp);
    return 0;
}
