#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS   10
#define MAX_FILES   50
#define NAME_LEN    100

struct UserDir {
    char dirname[NAME_LEN];
    char filenames[MAX_FILES][NAME_LEN];
    int file_count;
};

int main() {
    struct UserDir dirs[MAX_USERS];
    int user_count = 0;

    while (1) {
        int choice;
        printf("\n--- Two-Level Directory Simulation ---\n");
        printf("1. Create User Directory\n");
        printf("2. Create File in a User Directory\n");
        printf("3. Delete File from a User Directory\n");
        printf("4. Search File in a User Directory\n");
        printf("5. Display All Directories & Files\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }
        if (choice == 6) {
            printf("Exiting program.\n");
            break;
        }

        if (choice == 1) {
            if (user_count >= MAX_USERS) {
                printf("Cannot create more user directories. Limit reached.\n");
                continue;
            }
            printf("Enter name of new user directory: ");
            scanf("%s", dirs[user_count].dirname);
            dirs[user_count].file_count = 0;
            user_count++;
            printf("Directory created successfully.\n");
        }
        else if (choice == 2) {
            char dname[NAME_LEN];
            printf("Enter user directory name: ");
            scanf("%s", dname);
            int i;
            for (i = 0; i < user_count; i++) {
                if (strcmp(dirs[i].dirname, dname) == 0) {
                    if (dirs[i].file_count >= MAX_FILES) {
                        printf("Cannot create more files in directory '%s'. Limit reached.\n", dname);
                    } else {
                        printf("Enter file name: ");
                        scanf("%s", dirs[i].filenames[dirs[i].file_count]);
                        dirs[i].file_count++;
                        printf("File created successfully in directory '%s'.\n", dname);
                    }
                    break;
                }
            }
            if (i == user_count) {
                printf("Directory '%s' not found.\n", dname);
            }
        }
        else if (choice == 3) {
            char dname[NAME_LEN], fname[NAME_LEN];
            printf("Enter user directory name: ");
            scanf("%s", dname);
            printf("Enter file name to delete: ");
            scanf("%s", fname);

            int i, j;
            for (i = 0; i < user_count; i++) {
                if (strcmp(dirs[i].dirname, dname) == 0) {
                    int found = 0;
                    for (j = 0; j < dirs[i].file_count; j++) {
                        if (strcmp(dirs[i].filenames[j], fname) == 0) {
                            found = 1;
                            // replace this file slot with last file
                            strcpy(dirs[i].filenames[j],
                                   dirs[i].filenames[dirs[i].file_count - 1]);
                            dirs[i].file_count--;
                            printf("File '%s' deleted from directory '%s'.\n", fname, dname);
                            break;
                        }
                    }
                    if (!found) {
                        printf("File '%s' not found in directory '%s'.\n", fname, dname);
                    }
                    break;
                }
            }
            if (i == user_count) {
                printf("Directory '%s' not found.\n", dname);
            }
        }
        else if (choice == 4) {
            char dname[NAME_LEN], fname[NAME_LEN];
            printf("Enter user directory name: ");
            scanf("%s", dname);
            printf("Enter file name to search: ");
            scanf("%s", fname);

            int i, j;
            int found = 0;
            for (i = 0; i < user_count; i++) {
                if (strcmp(dirs[i].dirname, dname) == 0) {
                    for (j = 0; j < dirs[i].file_count; j++) {
                        if (strcmp(dirs[i].filenames[j], fname) == 0) {
                            printf("File '%s' found in directory '%s' at position %d.\n",
                                   fname, dname, j + 1);
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        printf("File '%s' not found in directory '%s'.\n", fname, dname);
                    }
                    break;
                }
            }
            if (i == user_count) {
                printf("Directory '%s' not found.\n", dname);
            }
        }
        else if (choice == 5) {
            int i, j;
            if (user_count == 0) {
                printf("No user directories created yet.\n");
            } else {
                printf("\n--- Directory Listing ---\n");
                for (i = 0; i < user_count; i++) {
                    printf("Directory: %s\n", dirs[i].dirname);
                    if (dirs[i].file_count == 0) {
                        printf("   (No files)\n");
                    } else {
                        for (j = 0; j < dirs[i].file_count; j++) {
                            printf("   %d. %s\n", j + 1, dirs[i].filenames[j]);
                        }
                    }
                }
            }
        }
        else {
            printf("Invalid choice; please try again.\n");
        }
    }

    return 0;
}
