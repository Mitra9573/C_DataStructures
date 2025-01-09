#include <stdio.h>
#include <stdlib.h>

// Define the stack structure
typedef struct {
    int* elements;    // Array to hold stack elements
    int index;        // Index of the top element
    int maxCapacity;  // Maximum capacity of the stack
} Stack;

// Function to create a new stack
Stack* createStack(int maxCapacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->elements = (int*)malloc(maxCapacity * sizeof(int));
    stack->index = -1;
    stack->maxCapacity = maxCapacity;
    return stack;
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->index == -1;
}

// Function to check if the stack is full
int isFull(Stack* stack) {
    return stack->index == stack->maxCapacity - 1;
}

// Function to push an element onto the stack
void push(Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow!\n");
        return;
    }
    stack->elements[++stack->index] = value;
}

// Function to pop an element from the stack
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow!\n");
        return -1;
    }
    return stack->elements[stack->index--];
}

// Function to get the top element of the stack
int top(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return stack->elements[stack->index];
}

// Function to perform a multi-pop operation
void multiPop(Stack* stack, int k) {
    if (k <= 0) {
        printf("Invalid number of elements to pop.\n");
        return;
    }
    int pops = (k > stack->index + 1) ? stack->index + 1 : k; // Limit pops to available elements
    stack->index -= pops;
    printf("Popped %d elements.\n", pops);
}

// Function to display the stack elements
void display(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = 0; i <= stack->index; i++) {
        printf("%d ", stack->elements[i]);
    }
    printf("\n");
}

// Main function to demonstrate the stack
int main() {
    int capacity;
    printf("Enter the capacity of the stack: ");
    scanf("%d", &capacity);

    Stack* stack = createStack(capacity);

    int choice, value, numToPop;
    while (1) {
        printf("\nOptions:\n");
        printf("1. Push a value onto the stack\n");
        printf("2. Pop a value from the stack\n");
        printf("3. Perform multiPop\n");
        printf("4. Display stack\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(stack, value);
                break;

            case 2:
                value = pop(stack);
                if (value != -1) {
                    printf("Popped value: %d\n", value);
                }
                break;

            case 3:
                printf("Enter number of elements to pop: ");
                scanf("%d", &numToPop);
                multiPop(stack, numToPop);
                break;

            case 4:
                display(stack);
                break;

            case 5:
                printf("Exiting program.\n");
                free(stack->elements); // Free allocated memory for stack elements
                free(stack); // Free the stack itself
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
