//matrix multiplication LAB 3
#include <stdio.h>
#include <stdlib.h>

int** allocate(int r, int c) {
    int **m = malloc(r * sizeof(int*));
    for (int i = 0; i < r; i++) m[i] = calloc(c, sizeof(int));
    return m;
}

void free_mat(int **m, int r) {
    for (int i = 0; i < r; i++) free(m[i]);
    free(m);
}

int main() {
    int r1, c1, r2, c2;
    printf("Enter dims for A and B: ");
    scanf("%d %d %d %d", &r1, &c1, &r2, &c2);

    if (c1 != r2) {
        printf("Multiplication impossible (c1 != r2).\n");
        return 1;
    }

    int **A = allocate(r1, c1), **B = allocate(r2, c2), **C = allocate(r1, c2);

    printf("Enter elements of Matrix A :\n");
    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c1; j++) scanf("%d", &A[i][j]);

    printf("Enter elements of Matrix B :\n");
    for (int i = 0; i < r2; i++)
        for (int j = 0; j < c2; j++) scanf("%d", &B[i][j]);

    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c2; j++)
            for (int k = 0; k < c1; k++)
                C[i][j] += A[i][k] * B[k][j];

    printf("\nResultant Matrix :\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) printf("%4d", C[i][j]);
        printf("\n");
    }

    free_mat(A, r1); free_mat(B, r2); free_mat(C, r1);
    return 0;
}

// Lab 4
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct List { int arr[MAX], size; };

void create(struct List *l) {
    printf("Size: ");
    scanf("%d", &l->size);
    if (l->size > MAX || l->size < 0) { l->size = 0; return; }
    for (int i = 0; i < l->size; i++) scanf("%d", &l->arr[i]);
}

void insert(struct List *l) {
    int p, v;
    if (l->size >= MAX) return;
    printf("Pos and val:");
    scanf("%d%d", &p, &v);
    if (p < 0 || p > l->size) return;
    for (int i = l->size - 1; i >= p; i--) l->arr[i + 1] = l->arr[i];
    l->arr[p] = v;
    l->size++;
}

void deleteElement(struct List *l) {
    int p;
    if (!l->size) return;
    printf("pos:");
    scanf("%d", &p);
    if (p < 0 || p >= l->size) return;
    for (int i = p; i < l->size - 1; i++) l->arr[i] = l->arr[i + 1];
    l->size--;
}

void search(struct List *l) {
    int v;
    if (!l->size) return;
    printf("Val: ");
    scanf("%d", &v);
    for (int i = 0; i < l->size; i++)
        if (l->arr[i] == v) printf("idx: %d", i);
}

void display(struct List *l) {
    for (int i = 0; i < l->size; i++) printf("%d ", l->arr[i]);
    printf("\n");
}

int main() {
    struct List l = { .size = 0 };
    int choice;
    while (1) {
        printf("1. create\n2.Insert\n3. Delete\n4. Search\n5. Display\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: create(&l); break;
            case 2: insert(&l); break;
            case 3: deleteElement(&l); break;
            case 4: search(&l); break;
            case 5: display(&l); break;
            case 6: exit(0);
            default: printf("\nInvalid choice! Please try again.\n");
        }
    }
}

// LAB 5
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head, int val) {
    struct Node* n = malloc(sizeof(struct Node));
    n->data = val;
    n->next = *head;
    *head = n;
}

void printList(struct Node* n) {
    while (n) {
        printf("%d -> ", n->data);
        n = n->next;
    }
    printf("NULL\n");
}

int main(void) {
    struct Node* head = NULL;

    push(&head, 30);
    push(&head, 20);
    push(&head, 10);

    printList(head);

    while (head) {
        struct Node* tmp = head;
        head = head->next;
        free(tmp);
    }
    return 0;
}
