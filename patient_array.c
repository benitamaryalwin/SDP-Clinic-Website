/*
 * MediCare Pro — Clinic Management System
 * SDP Project 2026
 * Module 1: Patient Management using Arrays and Linked Lists
 * Team Member: Charan
 * Concepts: Arrays, Structs, Bubble Sort, Linear Search, Linked List
 *           NEW: Edit Patient (update by ID), Patient Status
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 20

/* ──────────────────────────────────────────
   PART 1: Patient Array with CRUD
────────────────────────────────────────── */

typedef struct {
    int    id;
    char   name[50];
    int    age;
    char   gender[10];
    char   diagnosis[80];
    char   doctor[60];
    char   visitType[20];   /* "First Visit" | "Follow Up" */
    char   status[20];      /* "Active" | "Follow Up" | "Discharged" */
    char   contact[15];
} Patient;

Patient patients[MAX];
int count = 0;

/* ── Add ── */
void addPatient(int id, char name[], int age, char gender[],
                char diagnosis[], char doctor[], char status[]) {
    if (count >= MAX) { printf("Patient list full!\n"); return; }
    patients[count].id = id;
    strcpy(patients[count].name,      name);
    patients[count].age = age;
    strcpy(patients[count].gender,    gender);
    strcpy(patients[count].diagnosis, diagnosis);
    strcpy(patients[count].doctor,    doctor);
    strcpy(patients[count].status,    status);
    count++;
    printf("[+] Patient added: %s (ID=%d, Doctor=%s)\n", name, id, doctor);
}

/* ── Display ── */
void displayPatients() {
    printf("\n%-5s %-22s %-4s %-8s %-20s %-22s %-12s\n",
           "ID","Name","Age","Gender","Diagnosis","Doctor","Status");
    printf("%-5s %-22s %-4s %-8s %-20s %-22s %-12s\n",
           "---","--------------------","---","------","------------------","--------------------","----------");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-22s %-4d %-8s %-20s %-22s %-12s\n",
               patients[i].id, patients[i].name,
               patients[i].age, patients[i].gender,
               patients[i].diagnosis, patients[i].doctor,
               patients[i].status);
    }
    printf("Total: %d patient(s)\n\n", count);
}

/* ── Linear Search by ID ── */
int searchPatient(int id) {
    for (int i = 0; i < count; i++)
        if (patients[i].id == id) return i;
    return -1;
}

/* ── Edit Patient (NEW) ── */
void editPatient(int id, char newName[], int newAge, char newDiag[], char newStatus[]) {
    int idx = searchPatient(id);
    if (idx == -1) {
        printf("[!] Patient ID %d not found.\n", id);
        return;
    }
    if (newName[0] != '\0')  strcpy(patients[idx].name,      newName);
    if (newAge > 0)           patients[idx].age = newAge;
    if (newDiag[0] != '\0')  strcpy(patients[idx].diagnosis, newDiag);
    if (newStatus[0] != '\0') strcpy(patients[idx].status,   newStatus);
    printf("[✓] Patient ID %d updated: %s | Age %d | %s | %s\n",
           id, patients[idx].name, patients[idx].age,
           patients[idx].diagnosis, patients[idx].status);
}

/* ── Delete Patient ── */
void deletePatient(int id) {
    int idx = searchPatient(id);
    if (idx == -1) { printf("[!] Patient ID %d not found.\n", id); return; }
    printf("[-] Deleted: %s\n", patients[idx].name);
    for (int i = idx; i < count - 1; i++)
        patients[i] = patients[i + 1];
    count--;
}

/* ── Bubble Sort by age ── */
void sortByAge() {
    Patient temp;
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - i - 1; j++)
            if (patients[j].age > patients[j+1].age) {
                temp = patients[j]; patients[j] = patients[j+1]; patients[j+1] = temp;
            }
    printf("[✓] Patients sorted by age.\n");
}

/* ──────────────────────────────────────────
   PART 2: Linked List (dynamic patient list)
────────────────────────────────────────── */

typedef struct Node {
    Patient     data;
    struct Node *next;
} Node;

Node *head = NULL;

void llAdd(int id, char name[], int age) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data.id  = id;
    newNode->data.age = age;
    strcpy(newNode->data.name, name);
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
    } else {
        Node *temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
    printf("[+] Linked list: Added %s\n", name);
}

void llDisplay() {
    printf("\n--- Linked List Patients ---\n");
    Node *temp = head;
    while (temp) {
        printf("  ID: %d  Name: %-20s  Age: %d\n",
               temp->data.id, temp->data.name, temp->data.age);
        temp = temp->next;
    }
}

void llFree() {
    Node *temp;
    while (head) { temp = head; head = head->next; free(temp); }
}

/* ──────────────────────────────────────────
   MAIN
────────────────────────────────────────── */

int main() {
    printf("======================================\n");
    printf("  MediCare Pro: Patient Module (Charan)\n");
    printf("======================================\n\n");

    /* Add patients */
    addPatient(1, "Arjun Singh",    8,  "Male",   "Viral Fever",  "Dr. Rajesh Kumar",  "Active");
    addPatient(2, "Priya Nair",     5,  "Female", "Asthma",       "Dr. Priya Sharma",  "Active");
    addPatient(3, "Mohammed Ali",   12, "Male",   "Typhoid",      "Dr. Arun Mehta",    "Follow Up");
    addPatient(4, "Kavya Reddy",    9,  "Female", "Cold",         "Dr. Sunita Verma",  "Active");
    addPatient(5, "Rahul Das",      15, "Male",   "Joint Pain",   "Dr. Vikram Patel",  "Active");

    displayPatients();

    /* Search */
    int idx = searchPatient(3);
    if (idx != -1)
        printf("[Search] Found: %s — %s (Status: %s)\n\n",
               patients[idx].name, patients[idx].diagnosis, patients[idx].status);

    /* Edit Patient — NEW feature */
    printf("--- Editing Patient ID 2 ---\n");
    editPatient(2, "", 6, "Asthma (Controlled)", "Follow Up");
    displayPatients();

    /* Sort by age */
    sortByAge();
    displayPatients();

    /* Delete */
    printf("--- Deleting Patient ID 5 ---\n");
    deletePatient(5);
    displayPatients();

    /* Linked list demo */
    printf("--- Linked List Demo ---\n");
    llAdd(10, "Sneha Roy",   7);
    llAdd(11, "Karan Mehta", 10);
    llDisplay();
    llFree();

    return 0;
}
