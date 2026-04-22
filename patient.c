#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    int id;
    char name[50];
    int age;
    char gender[10];
    char phone[15];
    struct Patient *next;
};

struct Patient *front = NULL, *rear = NULL;

void addPatient(int id, char name[], int age, char gender[], char phone[]) {
    struct Patient *newNode = (struct Patient*)malloc(sizeof(struct Patient));

    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->age = age;
    strcpy(newNode->gender, gender);
    strcpy(newNode->phone, phone);
    newNode->next = NULL;

    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }

    printf("\n--- Patient Added to Queue ---\n");
    printf("Name: %s\n", name);
}

void servePatient() {
    if (front == NULL) {
        printf("No patients in queue\n");
        return;
    }

    struct Patient *temp = front;

    printf("\n--- Serving Patient ---\n");
    printf("Name: %s\n", temp->name);

    front = front->next;

    if (front == NULL)
        rear = NULL;

    free(temp);
}

void displayQueue() {
    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }

    struct Patient *temp = front;

    printf("\n--- Patient Queue ---\n");

    while (temp != NULL) {
        printf("ID: %d | Name: %s | Age: %d\n",
               temp->id, temp->name, temp->age);
        temp = temp->next;
    }
}

int main(int argc, char *argv[]) {
    int id = atoi(argv[1]);
    char *name = argv[2];
    int age = atoi(argv[3]);
    char *gender = argv[4];
    char *phone = argv[5];

    addPatient(id, name, age, gender, phone);

    printf("\nAssigned Doctor: ");
    if (age < 12)
        printf("Pediatrician\n");
    else
        printf("General Physician\n");

    return 0;
}