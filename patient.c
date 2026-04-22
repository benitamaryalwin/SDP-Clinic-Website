
#include <stdio.h>
struct Patient {
    int id;
    char name[50];
    int age;
    char gender[10];
    char phone[15];
};
void addPatient() {
    FILE *fp = fopen("patients.dat", "ab");
    struct Patient p;

    printf("Enter ID: ");
    scanf("%d", &p.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", p.name);

    printf("Enter Age: ");
    scanf("%d", &p.age);

    printf("Enter Gender: ");
    scanf("%s", p.gender);

    printf("Enter Phone: ");
    scanf("%s", p.phone);

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);

    printf("Patient Added!\n");
}
void viewPatients() {
    FILE *fp = fopen("patients.dat", "rb");
    struct Patient p;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while (fread(&p, sizeof(p), 1, fp)) {
        printf("\nID:%d Name:%s Age:%d Phone:%s\n",
               p.id, p.name, p.age, p.phone);
    }

    fclose(fp);
}
void searchPatient() {
    FILE *fp = fopen("patients.dat", "rb");
    struct Patient p;
    int id, found = 0;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter ID to search: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            printf("Found: %s Age:%d\n", p.name, p.age);
            found = 1;
        }
    }

    if (!found) printf("Not found!\n");

    fclose(fp);
}
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    struct Patient p;

    FILE *fp = fopen("patients.dat", "ab");

    p.id = atoi(argv[1]);
    strcpy(p.name, argv[2]);
    p.age = atoi(argv[3]);
    strcpy(p.gender, argv[4]);
    strcpy(p.phone, argv[5]);

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);

    printf("Patient Added: %s\n", p.name);
    printf("Assigned Doctor: General Physician\n");

    return 0;
}
