#include <stdio.h>
#include <stdlib.h>

// Maximum size of the stack
#define STACK_CAPACITY 100 

typedef struct {
    int stackArray[STACK_CAPACITY]; // Array to store stack elements
    int stackTop;                  // Index of the top element
} IntStack;

// Function to initialize the stack
void initializeStack(IntStack *intStack) {
    intStack->stackTop = -1;
}

// Function to check if the stack is empty
int isEmpty(IntStack *intStack) {
    return intStack->stackTop == -1;
}

// Function to check if the stack is full
int isFull(IntStack *intStack) {
    return intStack->stackTop == STACK_CAPACITY - 1;
}

// Function to push an element onto the stack
void push(IntStack *intStack, int element) {
    if (isFull(intStack)) {
        printf("Stack overflow! Cannot push %d.\n", element);
        return;
    }
    intStack->stackArray[++(intStack->stackTop)] = element;
    printf("Pushed %d onto the stack. Remaining space: %d\n", element, STACK_CAPACITY - intStack->stackTop - 1);
}

// Function to pop an element from the stack
int pop(IntStack *intStack) {
    if (isEmpty(intStack)) {
        printf("Stack underflow! Stack is empty.\n");
        return -1;
    }
    return intStack->stackArray[(intStack->stackTop)--];
}

// Function to peek at the top element of the stack
int peek(IntStack *intStack) {
    if (isEmpty(intStack)) {
        printf("Stack is empty! Cannot peek.\n");
        return -1;
    }
    return intStack->stackArray[intStack->stackTop];
}

// Main function
int main() {
    IntStack intStack;
    initializeStack(&intStack);

    // Push elements onto the stack
    push(&intStack, 15);
    push(&intStack, 25);
    push(&intStack, 35);

    // Peek at the top element
    int topElement = peek(&intStack);
    if (topElement != -1) {
        printf("Top element is %d.\n", topElement);
    }

    // Pop elements from the stack
    int poppedElement = pop(&intStack);
    if (poppedElement != -1) {
        printf("Popped %d from the stack.\n", poppedElement);
    }

    poppedElement = pop(&intStack);
    if (poppedElement != -1) {
        printf("Popped %d from the stack.\n", poppedElement);
    }

    // Check if the stack is empty
    if (isEmpty(&intStack)) {
        printf("Stack is now empty.\n");
    } else {
        printf("Stack is not empty.\n");
    }

    poppedElement = pop(&intStack);
    if (poppedElement != -1) {
        printf("Popped %d from the stack.\n", poppedElement);
    }

    return 0;
}
