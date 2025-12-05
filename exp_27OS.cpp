#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>   // for opendir, readdir
#include <string.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    char *path;

    // If user provides a directory path, use it; otherwise use current directory
    if (argc > 1) {
        path = argv[1];
    } else {
        path = ".";  // current directory
    }

    // Open directory
    dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    printf("Listing files in directory: %s\n\n", path);

    // Read entries one by one
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close directory
    closedir(dir);

    return 0;
}
