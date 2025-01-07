#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 1000

struct Stack {
       
    int *arr;               // Array to store stack elements
    int *increment;         // Array to store increments
    int top;                 // Index of the top element
    int capacity;            // Capacity of the stack
};

void initializeStack(struct Stack *stack, int capacity) {
    stack->capacity = capacity;
    stack->arr = (int *)malloc(capacity * sizeof(int));
    stack->increment = (int *)malloc(capacity * sizeof(int));
    stack->top = -1;
    for (int i = 0; i < capacity; i++) {
        stack->increment[i] = 0;
    }
}

int isFull(struct Stack *stack) {
    return stack->top == stack->capacity - 1;
}

void push(struct Stack *stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow\n");
        return;
    }

    stack->arr[++stack->top] = value;
    stack->increment[stack->top] = 0;
}

void increment(struct Stack *stack, int k, int value) {
    int limit = k < stack->top + 1 ? k : stack->top + 1;  // Ensure k doesn't exceed the stack size
    for (int i = 0; i < limit; i++) {
        stack->increment[i] += value;
    }
}

void printStack(struct Stack *stack) {
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->arr[i] + stack->increment[i]);
    }
    printf("\n");
}

int main() {
    struct Stack stack;
    int stackSize, element, incrementValue, incrementIndex;

    // Dynamic input for stack size
    printf("Enter the size of the stack: ");
    scanf("%d", &stackSize);

    // Initialize stack with dynamic size
    if (stackSize > MAX_CAPACITY) {
        printf("Stack size exceeds maximum capacity (%d).\n", MAX_CAPACITY);
        return 1;
    }

    initializeStack(&stack, stackSize);

    // Dynamic input for stack elements
    printf("Enter %d elements for the stack:\n", stackSize);
    for (int i = 0; i < stackSize; i++) {
        scanf("%d", &element);
        push(&stack, element);
    }

    // Dynamic input for increment operation
    printf("Enter the increment index (up to %d) and increment value:\n", stackSize);
    scanf("%d %d", &incrementIndex, &incrementValue);

    // Perform the increment operation
    increment(&stack, incrementIndex, incrementValue);

    // Display the modified stack
    printf("Modified stack after incrementing: ");
    printStack(&stack);

    // Free dynamically allocated memory for stack arrays
    free(stack.arr);
    free(stack.increment);

    return 0;
}
