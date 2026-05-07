
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "clinic_data.json"
#define MAX 1048576

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;

    if (strcmp(argv[1], "read") == 0) {
        FILE *fp = fopen(DATA_FILE, "rb");
        if (!fp) {
            printf("{\"patients\":[],\"appointments\":[],\"consultations\":[],\"invoices\":[],\"doctors\":[]}");
            return 0;
        }
        int c;
        while ((c = fgetc(fp)) != EOF) putchar(c);
        fclose(fp);
        return 0;
    }

    if (strcmp(argv[1], "write") == 0) {
        char *buf = malloc(MAX);
        size_t n = fread(buf, 1, MAX-1, stdin);
        buf[n] = '\0';

        FILE *fp = fopen(DATA_FILE, "wb");
        fwrite(buf, 1, n, fp);
        fclose(fp);
        free(buf);

        printf("{\"status\":\"saved\"}");
        return 0;
    }

    return 1;
}
