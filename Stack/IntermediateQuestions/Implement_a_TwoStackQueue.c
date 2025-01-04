#include <stdio.h>
#include <stdlib.h>

// Define a stack structure
struct DynamicStack {
    int* elements;   // Array to store stack elements
    int currentIndex; // Top index of the stack
    int maxSize;     // Maximum capacity of the stack
};

// Create a stack with a given capacity
struct DynamicStack* initializeStack(int maxSize) {
    struct DynamicStack* stack = (struct DynamicStack*)malloc(sizeof(struct DynamicStack));
    stack->maxSize = maxSize;
    stack->currentIndex = -1;
    stack->elements = (int*)malloc(stack->maxSize * sizeof(int));
    return stack;
}

// Check if the stack is full
int isStackFull(struct DynamicStack* stack) {
    return stack->currentIndex == stack->maxSize - 1;
}

// Check if the stack is empty
int isStackEmpty(struct DynamicStack* stack) {
    return stack->currentIndex == -1;
}

// Push an element onto the stack
void stackPush(struct DynamicStack* stack, int data) {
    if (isStackFull(stack)) {
        printf("Stack Overflow! Cannot add %d.\n", data);
        return;
    }
    stack->elements[++stack->currentIndex] = data;
}

// Pop an element from the stack
int stackPop(struct DynamicStack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack Underflow! No elements to remove.\n");
        return -1;
    }
    return stack->elements[stack->currentIndex--];
}

// Define a queue structure using two stacks
struct TwoStackQueue {
    struct DynamicStack* inputStack;  // Stack for enqueue operations
    struct DynamicStack* outputStack; // Stack for dequeue operations
};

// Create a queue with a given capacity
struct TwoStackQueue* initializeQueue(int maxSize) {
    struct TwoStackQueue* queue = (struct TwoStackQueue*)malloc(sizeof(struct TwoStackQueue));
    queue->inputStack = initializeStack(maxSize);
    queue->outputStack = initializeStack(maxSize);
    return queue;
}

// Enqueue an element into the queue
void enqueue(struct TwoStackQueue* queue, int data) {
    stackPush(queue->inputStack, data);
    printf("%d added to the queue.\n", data);
}

// Dequeue an element from the queue
int dequeue(struct TwoStackQueue* queue) {
    if (isStackEmpty(queue->inputStack) && isStackEmpty(queue->outputStack)) {
        printf("Queue is empty! No elements to remove.\n");
        return -1;
    }
    if (isStackEmpty(queue->outputStack)) {
        while (!isStackEmpty(queue->inputStack)) {
            stackPush(queue->outputStack, stackPop(queue->inputStack));
        }
    }
    return stackPop(queue->outputStack);
}

// Main function to test the queue operations
int main() {
    int queueCapacity = 5;
    struct TwoStackQueue* myQueue = initializeQueue(queueCapacity);
    int userChoice, inputValue;

    while (1) {
        printf("\nSelect an operation:\n");
        printf("1. Add to Queue (Enqueue)\n");
        printf("2. Remove from Queue (Dequeue)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1: 
                printf("Enter a value to add to the queue: ");
                scanf("%d", &inputValue);
                enqueue(myQueue, inputValue);
                break;

            case 2: 
                inputValue = dequeue(myQueue);
                if (inputValue != -1) {
                    printf("Removed %d from the queue.\n", inputValue);
                }
                break;

            case 3: 
                printf("Exiting the program.\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }

    return 0;
}
