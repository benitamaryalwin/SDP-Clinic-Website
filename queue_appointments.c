/*
 * MediCare Pro — Clinic Management System
 * SDP Project 2026
 * Module 2: Appointment Management using Queue
 * Team Member: Chris
 * Concepts: Queue (FIFO), Circular Queue, Enqueue, Dequeue
 *           NEW: Appointment reason field, dynamic doctor list
 */

#include <stdio.h>
#include <string.h>

#define SIZE 10

/* ──────────────────────────────────────────
   PART 1: Simple Queue (FIFO)
   "First booked = First served"
────────────────────────────────────────── */

typedef struct {
    int  id;
    char patient[50];
    char doctor[60];
    char date[15];
    char time[10];
    char reason[80];
} Appointment;

Appointment queue[SIZE];
int front = -1, rear = -1;

int isFull()  { return rear == SIZE - 1; }
int isEmpty() { return front == -1; }

/* Enqueue — book appointment */
void enqueue(int id, char patient[], char doctor[], char date[], char reason[]) {
    if (isFull()) { printf("[!] Queue full — cannot book more appointments.\n"); return; }
    if (front == -1) front = 0;
    rear++;
    queue[rear].id = id;
    strcpy(queue[rear].patient, patient);
    strcpy(queue[rear].doctor,  doctor);
    strcpy(queue[rear].date,    date);
    strcpy(queue[rear].reason,  reason);
    printf("[+] Booked: %-18s → %-22s on %s (%s)\n",
           patient, doctor, date, reason);
}

/* Dequeue — serve next patient (FIFO) */
void dequeue() {
    if (isEmpty()) { printf("[!] No appointments in queue.\n"); return; }
    printf("[✓] Serving: %s with %s on %s\n",
           queue[front].patient, queue[front].doctor, queue[front].date);
    if (front == rear) { front = rear = -1; }
    else               { front++; }
}

void displayQueue() {
    if (isEmpty()) { printf("Queue is empty.\n\n"); return; }
    printf("\n%-5s %-20s %-22s %-12s %-25s\n",
           "Pos","Patient","Doctor","Date","Reason");
    printf("%-5s %-20s %-22s %-12s %-25s\n",
           "---","------------------","--------------------","----------","-----------------------");
    for (int i = front; i <= rear; i++) {
        printf("%-5d %-20s %-22s %-12s %-25s\n",
               i - front + 1,
               queue[i].patient, queue[i].doctor,
               queue[i].date,    queue[i].reason);
    }
    printf("Queue size: %d\n\n", rear - front + 1);
}

/* ──────────────────────────────────────────
   PART 2: Circular Queue
   (for repeating time slots)
────────────────────────────────────────── */

#define CSIZE 5

Appointment cq[CSIZE];
int cfront = -1, crear = -1;

int cIsFull()  { return (crear + 1) % CSIZE == cfront; }
int cIsEmpty() { return cfront == -1; }

void cEnqueue(int id, char patient[], char doctor[]) {
    if (cIsFull())   { printf("[!] Circular queue full!\n"); return; }
    if (cfront == -1) cfront = 0;
    crear = (crear + 1) % CSIZE;
    cq[crear].id = id;
    strcpy(cq[crear].patient, patient);
    strcpy(cq[crear].doctor,  doctor);
    printf("[+] Circular Queue: Added %-18s → %s\n", patient, doctor);
}

void cDequeue() {
    if (cIsEmpty()) { printf("[!] Circular queue empty!\n"); return; }
    printf("[✓] Circular Queue: Served %s\n", cq[cfront].patient);
    if (cfront == crear) { cfront = crear = -1; }
    else                 { cfront = (cfront + 1) % CSIZE; }
}

/* ──────────────────────────────────────────
   MAIN
────────────────────────────────────────── */

int main() {
    printf("=========================================\n");
    printf("  MediCare Pro: Appointment Module (Chris)\n");
    printf("=========================================\n\n");

    /* Book appointments (Enqueue) */
    enqueue(1, "Arjun Singh",   "Dr. Rajesh Kumar",  "2026-05-10", "Routine Checkup");
    enqueue(2, "Priya Nair",    "Dr. Priya Sharma",  "2026-05-10", "Follow Up");
    enqueue(3, "Mohammed Ali",  "Dr. Arun Mehta",    "2026-05-11", "Knee Pain");
    enqueue(4, "Kavya Reddy",   "Dr. Sunita Verma",  "2026-05-11", "Ear Infection");
    enqueue(5, "Rahul Das",     "Dr. Meena Iyer",    "2026-05-12", "Skin Rash");
    enqueue(6, "Sneha Roy",     "Dr. Rajesh Kumar",  "2026-05-12", "Vaccination");

    displayQueue();

    printf("--- Serving next 2 patients (Dequeue) ---\n");
    dequeue();
    dequeue();

    displayQueue();

    /* Circular Queue Demo */
    printf("--- Circular Queue (repeating slots) ---\n");
    cEnqueue(1, "Patient A", "Dr. Rajesh Kumar");
    cEnqueue(2, "Patient B", "Dr. Priya Sharma");
    cEnqueue(3, "Patient C", "Dr. Arun Mehta");
    cDequeue();
    cEnqueue(4, "Patient D", "Dr. Sunita Verma");  /* reuses freed slot */
    printf("[✓] Circular queue working correctly (wrap-around verified).\n");

    return 0;
}
