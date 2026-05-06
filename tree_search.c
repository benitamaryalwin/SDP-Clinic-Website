/*
 * MediCare Pro — Clinic Management System
 * SDP Project 2026
 * Module 4: Doctor & Patient Search using Binary Search Tree
 * Team Member: Dafna
 * Concepts: BST Insert, Search, Delete, In-order / Pre-order Traversal
 *           NEW: Doctor status field, dynamic add/remove doctor
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ──────────────────────────────────────────
   BST Node — stores doctor record
────────────────────────────────────────── */

typedef struct BSTNode {
    int             id;
    char            name[60];
    char            specialization[50];
    char            qualifications[30];
    int             experience;     /* years */
    char            status[20];     /* Available | In Consultation | On Leave */
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

/* ──────────────────────────────────────────
   HELPERS
────────────────────────────────────────── */

BSTNode *newNode(int id, char name[], char spec[], char quals[], int exp, char status[]) {
    BSTNode *node = (BSTNode *)malloc(sizeof(BSTNode));
    node->id = id;
    strcpy(node->name,           name);
    strcpy(node->specialization, spec);
    strcpy(node->qualifications, quals);
    node->experience = exp;
    strcpy(node->status, status);
    node->left = node->right = NULL;
    return node;
}

/* ──────────────────────────────────────────
   BST OPERATIONS
────────────────────────────────────────── */

/* Insert */
BSTNode *insert(BSTNode *root, int id, char name[], char spec[],
                char quals[], int exp, char status[]) {
    if (!root) return newNode(id, name, spec, quals, exp, status);
    if      (id < root->id) root->left  = insert(root->left,  id, name, spec, quals, exp, status);
    else if (id > root->id) root->right = insert(root->right, id, name, spec, quals, exp, status);
    else printf("[!] Doctor ID %d already exists.\n", id);
    return root;
}

/* Search */
BSTNode *search(BSTNode *root, int id) {
    if (!root || root->id == id) return root;
    if (id < root->id) return search(root->left,  id);
    else               return search(root->right, id);
}

/* Find minimum (for delete) */
BSTNode *findMin(BSTNode *root) {
    while (root->left) root = root->left;
    return root;
}

/* Delete */
BSTNode *deleteNode(BSTNode *root, int id) {
    if (!root) return NULL;
    if      (id < root->id) root->left  = deleteNode(root->left,  id);
    else if (id > root->id) root->right = deleteNode(root->right, id);
    else {
        if (!root->left) {
            BSTNode *temp = root->right; free(root); return temp;
        } else if (!root->right) {
            BSTNode *temp = root->left;  free(root); return temp;
        } else {
            BSTNode *succ = findMin(root->right);
            root->id = succ->id;
            strcpy(root->name,           succ->name);
            strcpy(root->specialization, succ->specialization);
            strcpy(root->qualifications, succ->qualifications);
            root->experience = succ->experience;
            strcpy(root->status, succ->status);
            root->right = deleteNode(root->right, succ->id);
        }
    }
    return root;
}

/* ──────────────────────────────────────────
   TRAVERSALS
────────────────────────────────────────── */

/* In-order — sorted by ID */
void inorder(BSTNode *root) {
    if (!root) return;
    inorder(root->left);
    printf("  [%2d] %-24s | %-22s | %-12s | %2d yrs | %s\n",
           root->id, root->name, root->specialization,
           root->qualifications, root->experience, root->status);
    inorder(root->right);
}

/* Pre-order — root first */
void preorder(BSTNode *root) {
    if (!root) return;
    printf("  [%2d] %s (%s)\n", root->id, root->name, root->specialization);
    preorder(root->left);
    preorder(root->right);
}

/* Count available doctors */
int countAvailable(BSTNode *root) {
    if (!root) return 0;
    int here = strcmp(root->status, "Available") == 0 ? 1 : 0;
    return here + countAvailable(root->left) + countAvailable(root->right);
}

/* Free tree */
void freeTree(BSTNode *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

/* ──────────────────────────────────────────
   MAIN
────────────────────────────────────────── */

int main() {
    printf("==============================================\n");
    printf("  MediCare Pro: Doctor Search — BST (Dafna)\n");
    printf("==============================================\n\n");

    BSTNode *root = NULL;

    /* Insert doctors — NEW: with qualifications, experience, status */
    root = insert(root, 4, "Dr. Rajesh Kumar",  "Paediatrics",      "MBBS, MD",  10, "Available");
    root = insert(root, 2, "Dr. Priya Sharma",  "General Medicine", "MBBS, MS",   8, "In Consultation");
    root = insert(root, 6, "Dr. Arun Mehta",    "Orthopaedics",     "MBBS, DNB", 12, "Available");
    root = insert(root, 1, "Dr. Sunita Verma",  "ENT",              "MBBS, DLO",  7, "Available");
    root = insert(root, 3, "Dr. Vikram Patel",  "Cardiology",       "MBBS, DM",  15, "On Leave");
    root = insert(root, 5, "Dr. Meena Iyer",    "Dermatology",      "MBBS, MD",   9, "Available");

    /* NEW: Add a dynamically added doctor (simulates "Add Doctor" feature) */
    root = insert(root, 7, "Dr. Ananya Bose",   "Neurology",        "MBBS, DM",   6, "Available");

    printf("--- In-order Traversal (sorted by ID) ---\n");
    printf("  %-4s %-24s | %-22s | %-12s | %s | %s\n",
           "ID","Name","Specialization","Qualifications","Exp","Status");
    printf("  %-4s %-24s | %-22s | %-12s | %s | %s\n",
           "----","----------------------","--------------------","------------","---","----------");
    inorder(root);
    printf("\nAvailable doctors: %d / 7\n\n", countAvailable(root));

    printf("--- Pre-order Traversal ---\n");
    preorder(root);

    /* Search */
    printf("\n--- Search Doctor ID 5 ---\n");
    BSTNode *found = search(root, 5);
    if (found)
        printf("[✓] Found: %s | %s | %s | %d yrs exp | Status: %s\n\n",
               found->name, found->specialization, found->qualifications,
               found->experience, found->status);
    else
        printf("[!] Doctor ID 5 not found.\n\n");

    /* Search non-existing */
    printf("--- Search Doctor ID 9 ---\n");
    found = search(root, 9);
    printf(found ? "[✓] Found: %s\n" : "[!] Doctor ID 9 not found in BST.\n\n", found ? found->name : "");

    /* Delete — simulates removing a doctor */
    printf("--- Remove Doctor ID 3 (Dr. Vikram Patel — On Leave) ---\n");
    root = deleteNode(root, 3);
    printf("[✓] Doctor removed. In-order after deletion:\n");
    printf("  %-4s %-24s | %-22s | %s\n","ID","Name","Specialization","Status");
    printf("  %-4s %-24s | %-22s | %s\n","----","----------------------","--------------------","----------");
    inorder(root);
    printf("\nAvailable doctors: %d / 6\n\n", countAvailable(root));

    freeTree(root);
    printf("[✓] BST module complete.\n");
    return 0;
}
