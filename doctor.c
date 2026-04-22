int main(int argc, char *argv[]) {
    struct Record r;

    r.id = atoi(argv[1]);
    strcpy(r.name, argv[2]);
    strcpy(r.diagnosis, argv[3]);
    strcpy(r.prescription, argv[4]);

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
