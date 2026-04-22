#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
    int id;
    char name[50];
    char diagnosis[100];
    char prescription[100];
};

void addRecord() {
    FILE *fp = fopen("records.dat", "ab");
    struct Record r;

    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("\nEnter Patient ID: ");
    scanf("%d", &r.id);

    printf("Enter Patient Name: ");
    scanf(" %[^\n]", r.name);

    printf("Enter Diagnosis: ");
    scanf(" %[^\n]", r.diagnosis);

    printf("Enter Prescription: ");
    scanf(" %[^\n]", r.prescription);

    fwrite(&r, sizeof(r), 1, fp);
    fclose(fp);

    printf("\n--- Record Saved Successfully ---\n");
}

void viewRecords() {
    FILE *fp = fopen("records.dat", "rb");
    struct Record r;

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n--- Patient Records ---\n");

    while (fread(&r, sizeof(r), 1, fp)) {
        printf("\nID           : %d\n", r.id);
        printf("Name         : %s\n", r.name);
        printf("Diagnosis    : %s\n", r.diagnosis);
        printf("Prescription : %s\n", r.prescription);
        printf("-----------------------------\n");
    }

    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n===== Doctor Module =====\n");
        printf("1. Add Diagnosis & Prescription\n");
        printf("2. View Patient Records\n");
        printf("3. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                viewRecords();
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
