#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[30];
    float salary;
};

void addEmployee(FILE *fp) {
    struct Employee emp;
    printf("\nEnter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Employee Name: ");
    scanf("%s", emp.name);
    printf("Enter Employee Salary: ");
    scanf("%f", &emp.salary);

    fseek(fp, (emp.id - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, fp);

    printf("Employee record added successfully!\n");
}

void displayEmployees(FILE *fp) {
    struct Employee emp;
    rewind(fp);
    printf("\n--- Employee Records ---\n");
    while (fread(&emp, sizeof(struct Employee), 1, fp) == 1) {
        if (emp.id != 0) { // skip empty records
            printf("ID: %d | Name: %s | Salary: %.2f\n", emp.id, emp.name, emp.salary);
        }
    }
}

void searchEmployee(FILE *fp) {
    int id;
    struct Employee emp;
    printf("\nEnter Employee ID to search: ");
    scanf("%d", &id);

    fseek(fp, (id - 1) * sizeof(struct Employee), SEEK_SET);
    if (fread(&emp, sizeof(struct Employee), 1, fp) == 1 && emp.id != 0) {
        printf("Employee Found!\n");
        printf("ID: %d | Name: %s | Salary: %.2f\n", emp.id, emp.name, emp.salary);
    } else {
        printf("Employee with ID %d not found.\n", id);
    }
}

int main() {
    FILE *fp;
    int choice;

    fp = fopen("employee.dat", "rb+");
    if (fp == NULL) {
        fp = fopen("employee.dat", "wb+");
        if (fp == NULL) {
            printf("Error opening file!\n");
            exit(1);
        }
    }

    while (1) {
        printf("\n--- Employee Menu ---\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(fp); break;
            case 2: displayEmployees(fp); break;
            case 3: searchEmployee(fp); break;
            case 4: fclose(fp); exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
