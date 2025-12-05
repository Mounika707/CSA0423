#include <stdio.h>
#include <string.h>

// Structure to represent file permissions
struct Permissions {
    int read;
    int write;
    int execute;
};

// Structure to represent a user type
struct User {
    char type[10]; // owner, group, others
    struct Permissions perms;
};

// Function to display permissions in rwx format
void displayPerms(struct Permissions p) {
    printf("%c", p.read ? 'r' : '-');
    printf("%c", p.write ? 'w' : '-');
    printf("%c", p.execute ? 'x' : '-');
}

int main() {
    struct User owner = {"Owner", {1, 1, 1}};   // rwx
    struct User group = {"Group", {1, 0, 1}};   // r-x
    struct User others = {"Others", {1, 0, 0}}; // r--

    printf("Linux File Access Permission Simulation\n");
    printf("----------------------------------------\n");

    printf("%-10s : ", owner.type);
    displayPerms(owner.perms);
    printf("\n");

    printf("%-10s : ", group.type);
    displayPerms(group.perms);
    printf("\n");

    printf("%-10s : ", others.type);
    displayPerms(others.perms);
    printf("\n");

    // Simulate access check
    char userType[10];
    char action[10];
    printf("\nEnter user type (Owner/Group/Others): ");
    scanf("%s", userType);
    printf("Enter action (read/write/execute): ");
    scanf("%s", action);

    struct User current;
    if (strcmp(userType, "Owner") == 0) current = owner;
    else if (strcmp(userType, "Group") == 0) current = group;
    else current = others;

    int allowed = 0;
    if (strcmp(action, "read") == 0 && current.perms.read) allowed = 1;
    if (strcmp(action, "write") == 0 && current.perms.write) allowed = 1;
    if (strcmp(action, "execute") == 0 && current.perms.execute) allowed = 1;

    if (allowed)
        printf("\nAccess GRANTED: %s can %s the file.\n", current.type, action);
    else
        printf("\nAccess DENIED: %s cannot %s the file.\n", current.type, action);

    return 0;
}
