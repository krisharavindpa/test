//lab 8
#include <stdio.h>
#define MAX 100
int q[MAX], f = -1, r = -1;

void enq(int v) { if(r < MAX-1) { if(f == -1) f = 0; q[++r] = v; } }
int deq() { return (f == -1 || f > r) ? -1 : q[f++]; }

int main() {
    enq(10); enq(20);
    printf("Array Queue: %d, %d\n", deq(), deq());
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct Node { int data; struct Node* next; } Node;
Node *front = NULL, *rear = NULL;

void enq(int v) {
    Node* t = malloc(sizeof(Node));
    t->data = v; t->next = NULL;
    if(rear) rear->next = t;
    rear = t;
    if(!front) front = t;
}

int deq() {
    if(!front) return -1;
    Node* t = front; int v = t->data;
    front = front->next; free(t);
    return v;
}

int main() {
    enq(30); enq(40);
    printf("LL Queue: %d, %d\n", deq(), deq());
    return 0;
}


//lab 9
//Stack- String Reversal
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "HELLO", stack[100];
    int top = -1, len = strlen(str);
    
    for(int i = 0; i < len; i++) stack[++top] = str[i]; // Push
    for(int i = 0; i < len; i++) str[i] = stack[top--]; // Pop
    
    printf("Reversed String (Stack): %s\n", str);
    return 0;
}

//Queue Application - Binary Number Generation 1 - N
#include <stdio.h>
#include <string.h>

int main() {
    char q[100][10], temp[10];
    int f = 0, r = -1, n = 5; // Generate first 5 binary numbers
    
    strcpy(q[++r], "1"); // Enqueue "1"
    for(int i = 0; i < n; i++) {
        strcpy(temp, q[f++]); // Dequeue
        printf("%s ", temp);
        
        strcpy(q[++r], temp); strcat(q[r], "0"); // Enqueue temp + "0"
        strcpy(q[++r], temp); strcat(q[r], "1"); // Enqueue temp + "1"
    }
    return 0;
}

//Lab 10: Implementation of trees using arrays

#include <stdio.h>

char tree[100]; // Root is at index 0

void set_root(char c) { tree[0] = c; }
void set_left(char c, int p) { tree[2 * p + 1] = c; }
void set_right(char c, int p) { tree[2 * p + 2] = c; }

int main() {
    for(int i = 0; i < 100; i++) tree[i] = '-'; // Initialize empty
    
    set_root('A');
    set_left('B', 0);
    set_right('C', 0);
    set_left('D', 1); // Left child of B
    
    printf("Array Tree (Level Order): ");
    for(int i = 0; i < 7; i++) printf("%c ", tree[i]);
    return 0;
}

//Lab 11:
//Implementation of BST Using Linked List:
#include <stdio.h>
#include <stdlib.h>

typedef struct Node { int data; struct Node *left, *right; } Node;

Node* insert(Node* root, int v) {
    if(!root) {
        Node* t = malloc(sizeof(Node));
        t->data = v; t->left = t->right = NULL;
        return t;
    }
    if(v < root->data) root->left = insert(root->left, v);
    else root->right = insert(root->right, v);
    return root;
}

void inorder(Node* root) {
    if(root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;
    int vals[] = {50, 30, 20, 40, 70, 60, 80};
    
    for(int i = 0; i < 7; i++) root = insert(root, vals[i]);
    
    printf("BST Inorder: ");
    inorder(root);
    return 0;
}
