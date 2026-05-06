/*
 * MediCare Pro — Clinic Management System
 * SDP Project 2026
 * Module 3: Consultation History using Stack
 * Team Member: Benita
 * Concepts: Stack (LIFO), Push, Pop, Peek, Undo Last Entry
 *           NEW: Doctor field, Follow-up date, Notes
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 15

/* ──────────────────────────────────────────
   PART 1: Array Stack (LIFO)
   "Last consultation = top of stack"
   Undo = pop last entry
────────────────────────────────────────── */

typedef struct {
    int  id;
    char patient[50];
    char doctor[60];
    char complaint[80];
    char diagnosis[80];
    char medication[80];
    char followUp[15];   /* date string or "" */
    char notes[100];
} Consultation;

Consultation stack[MAX];
int top = -1;

int isFull()  { return top == MAX - 1; }
int isEmpty() { return top == -1; }

/* Push — save new consultation */
void push(int id, char patient[], char doctor[], char complaint[],
          char diagnosis[], char medication[], char followUp[], char notes[]) {
    if (isFull()) { printf("[!] Stack full — cannot save more records.\n"); return; }
    top++;
    stack[top].id = id;
    strcpy(stack[top].patient,    patient);
    strcpy(stack[top].doctor,     doctor);
    strcpy(stack[top].complaint,  complaint);
    strcpy(stack[top].diagnosis,  diagnosis);
    strcpy(stack[top].medication, medication);
    strcpy(stack[top].followUp,   followUp);
    strcpy(stack[top].notes,      notes);
    printf("[+] Saved: %-18s | %-20s | %s\n", patient, diagnosis, doctor);
}

/* Pop — undo last entry */
void pop() {
    if (isEmpty()) { printf("[!] No consultations to undo.\n"); return; }
    printf("[↩] Undo: Removed last consultation for %s (%s)\n",
           stack[top].patient, stack[top].diagnosis);
    top--;
}

/* Peek — view latest without removing */
void peek() {
    if (isEmpty()) { printf("[!] Stack empty.\n"); return; }
    printf("\n--- Latest Consultation (Stack Top) ---\n");
    printf("  Patient   : %s\n", stack[top].patient);
    printf("  Doctor    : %s\n", stack[top].doctor);
    printf("  Complaint : %s\n", stack[top].complaint);
    printf("  Diagnosis : %s\n", stack[top].diagnosis);
    printf("  Medication: %s\n", stack[top].medication);
    if (stack[top].followUp[0])
        printf("  Follow-up : %s\n", stack[top].followUp);
    if (stack[top].notes[0])
        printf("  Notes     : %s\n", stack[top].notes);
    printf("\n");
}

/* Display all — latest first (LIFO order) */
void displayAll() {
    if (isEmpty()) { printf("No consultations on record.\n\n"); return; }
    printf("\n%-4s %-20s %-22s %-22s %-22s %-12s\n",
           "No.","Patient","Doctor","Diagnosis","Medication","Follow-up");
    printf("%-4s %-20s %-22s %-22s %-22s %-12s\n",
           "---","------------------","--------------------","--------------------","--------------------","----------");
    for (int i = top; i >= 0; i--) {
        printf("%-4d %-20s %-22s %-22s %-22s %-12s\n",
               top - i + 1,
               stack[i].patient, stack[i].doctor,
               stack[i].diagnosis, stack[i].medication,
               stack[i].followUp[0] ? stack[i].followUp : "—");
    }
    printf("Total consultations: %d\n\n", top + 1);
}

/* ──────────────────────────────────────────
   PART 2: Linked List Stack (dynamic size)
────────────────────────────────────────── */

typedef struct LLNode {
    Consultation    data;
    struct LLNode  *next;
} LLNode;

LLNode *llTop = NULL;

void llPush(char patient[], char complaint[], char doctor[]) {
    LLNode *newNode = (LLNode *)malloc(sizeof(LLNode));
    strcpy(newNode->data.patient,   patient);
    strcpy(newNode->data.complaint, complaint);
    strcpy(newNode->data.doctor,    doctor);
    newNode->next = llTop;
    llTop = newNode;
    printf("[+] LL Stack: Pushed %-18s (%s)\n", patient, doctor);
}

void llPop() {
    if (!llTop) { printf("[!] LL Stack is empty.\n"); return; }
    printf("[↩] LL Stack: Popped %s\n", llTop->data.patient);
    LLNode *temp = llTop;
    llTop = llTop->next;
    free(temp);
}

void llFree() {
    while (llTop) llPop();
}

/* ──────────────────────────────────────────
   MAIN
────────────────────────────────────────── */

int main() {
    printf("===========================================\n");
    printf("  MediCare Pro: Consultation Module (Benita)\n");
    printf("===========================================\n\n");

    /* Push consultations */
    push(1, "Arjun Singh",   "Dr. Rajesh Kumar",  "Fever and cold",     "Viral Fever",  "Paracetamol 500mg",  "2026-05-17", "Rest for 3 days");
    push(2, "Priya Nair",    "Dr. Priya Sharma",  "Breathing trouble",  "Asthma",       "Salbutamol Inhaler", "2026-05-20", "Avoid cold air");
    push(3, "Mohammed Ali",  "Dr. Arun Mehta",    "Stomach ache",       "Gastritis",    "Antacid + ORS",      "",           "Light diet");
    push(4, "Kavya Reddy",   "Dr. Sunita Verma",  "Ear pain",           "Otitis Media", "Amoxicillin 250mg",  "2026-05-18", "Keep ear dry");

    displayAll();
    peek();

    printf("--- Undo last consultation ---\n");
    pop();
    displayAll();

    /* Linked List Stack Demo */
    printf("--- Linked List Stack Demo ---\n");
    llPush("Rahul Das",   "Joint pain",  "Dr. Vikram Patel");
    llPush("Sneha Roy",   "Skin rash",   "Dr. Meena Iyer");
    llPush("Karan Mehta", "Headache",    "Dr. Priya Sharma");
    llPop();   /* undo Karan Mehta */
    llFree();

    printf("\n[✓] Stack module complete.\n");
    return 0;
}
