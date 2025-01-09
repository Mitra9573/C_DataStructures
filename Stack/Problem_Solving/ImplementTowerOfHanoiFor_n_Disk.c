#include <stdio.h>
#include <stdlib.h>

#define MAX_DISKS 100

// Stack structure to hold the disks
struct Stack {
    int* arr;  // Array of disks
    int top;   // Index of the top element
    int capacity;  // Capacity of the stack
};

// Function to initialize the stack with dynamic memory allocation
void initializeStack(struct Stack* stack, int capacity) {
    stack->arr = (int*)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push a disk onto the stack
void push(struct Stack* stack, int value) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack overflow\n");
        exit(1);
    }
    stack->arr[++stack->top] = value;
}

// Function to pop a disk from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack->arr[stack->top--];
}

// Function to move a disk from one stack to another
void moveDisk(struct Stack* src, struct Stack* dest, const char* srcName, const char* destName) {
    int disk = pop(src);
    push(dest, disk);
    printf("Move disk %d from %s to %s\n", disk, srcName, destName);
}

// Function to solve Tower of Hanoi recursively
void towerOfHanoi(int n, struct Stack* src, struct Stack* dest, struct Stack* aux, const char* srcName, const char* destName, const char* auxName) {
    if (n == 1) {
        moveDisk(src, dest, srcName, destName);
        return;
    }
    towerOfHanoi(n - 1, src, aux, dest, srcName, auxName, destName);
    moveDisk(src, dest, srcName, destName);
    towerOfHanoi(n - 1, aux, dest, src, auxName, destName, srcName);
}

int main() {
    int n;
    printf("Enter the number of disks: ");
    scanf("%d", &n);

    if (n > MAX_DISKS) {
        printf("Number of disks exceeds maximum capacity (%d).\n", MAX_DISKS);
        return 1;
    }

    // Dynamically allocate memory for the stacks
    struct Stack src, dest, aux;
    initializeStack(&src, n);
    initializeStack(&dest, n);
    initializeStack(&aux, n);

    // Initialize the source stack with disks (largest to smallest)
    for (int i = n; i >= 1; i--) {
        push(&src, i);
    }

    printf("Steps to solve Tower of Hanoi for %d disks:\n", n);
    towerOfHanoi(n, &src, &dest, &aux, "A", "C", "B");

    // Free dynamically allocated memory for stacks
    free(src.arr);
    free(dest.arr);
    free(aux.arr);

    return 0;
}
