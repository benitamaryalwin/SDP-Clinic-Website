#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
    int id;
    char name[50];
    char diagnosis[100];
    char prescription[100];
};

int main() {
    struct Record r;

    printf("Enter Patient ID: ");
    scanf("%d", &r.id);
    getchar(); // consume leftover newline

    printf("Enter Name: ");
    fgets(r.name, sizeof(r.name), stdin);
    r.name[strcspn(r.name, "\n")] = '\0';

    printf("Enter Diagnosis: ");
    fgets(r.diagnosis, sizeof(r.diagnosis), stdin);
    r.diagnosis[strcspn(r.diagnosis, "\n")] = '\0';

    printf("Enter Prescription: ");
    fgets(r.prescription, sizeof(r.prescription), stdin);
    r.prescription[strcspn(r.prescription, "\n")] = '\0';

    FILE *fp = fopen("records.dat", "ab");

    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fwrite(&r, sizeof(r), 1, fp);
    fclose(fp);

    printf("\n--- Diagnosis Recorded ---\n");
    printf("Patient ID   : %d\n", r.id);
    printf("Name         : %s\n", r.name);
    printf("Diagnosis    : %s\n", r.diagnosis);
    printf("Prescription : %s\n", r.prescription);

    return 0;
}
