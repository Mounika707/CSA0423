#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILES 100
#define NAME_LEN 100

struct Directory {
    char dname[NAME_LEN];
    char fname[MAX_FILES][NAME_LEN];
    int fcnt;
} dir;

void create_file() {
    if (dir.fcnt >= MAX_FILES) {
        printf("Directory full — cannot add more files.\n");
        return;
    }
    printf("Enter the name of the file: ");
    scanf("%s", dir.fname[dir.fcnt]);
    dir.fcnt++;
    printf("File created successfully.\n");
}

void delete_file() {
    char name[NAME_LEN];
    printf("Enter the name of the file to delete: ");
    scanf("%s", name);

    int found = 0;
    for (int i = 0; i < dir.fcnt; i++) {
        if (strcmp(dir.fname[i], name) == 0) {
            found = 1;
            // overwrite this entry with last, reduce count
            strcpy(dir.fname[i], dir.fname[dir.fcnt - 1]);
            dir.fcnt--;
            printf("File \"%s\" deleted successfully.\n", name);
            break;
        }
    }
    if (!found) {
        printf("File \"%s\" not found in directory.\n", name);
    }
}

void search_file() {
    char name[NAME_LEN];
    printf("Enter the name of the file to search: ");
    scanf("%s", name);

    for (int i = 0; i < dir.fcnt; i++) {
        if (strcmp(dir.fname[i], name) == 0) {
            printf("File \"%s\" found at position %d.\n", name, i+1);
            return;
        }
    }
    printf("File \"%s\" not found in directory.\n", name);
}

void display_files() {
    printf("\nDirectory name: %s\n", dir.dname);
    printf("Files in directory:\n");
    if (dir.fcnt == 0) {
        printf("  (No files)\n");
    } else {
        for (int i = 0; i < dir.fcnt; i++) {
            printf("  %d. %s\n", i+1, dir.fname[i]);
        }
    }
    printf("\n");
}

int main() {
    dir.fcnt = 0;

    printf("Enter name of directory: ");
    if (scanf("%s", dir.dname) != 1) {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    while (1) {
        int choice;
        printf("Choose an option:\n");
        printf(" 1. Create file\n");
        printf(" 2. Delete file\n");
        printf(" 3. Search file\n");
        printf(" 4. Display files\n");
        printf(" 5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }
        switch (choice) {
            case 1: create_file(); break;
            case 2: delete_file(); break;
            case 3: search_file(); break;
            case 4: display_files(); break;
            case 5: exit(0);
            default: printf("Invalid choice — try again.\n");
        }
    }

    return 0;
}
