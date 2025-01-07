#include <stdio.h>
#include <stdlib.h>

// Define a dynamic stack structure
struct DynamicStack {
    int* elements;
    int topIndex;
    int maxCapacity;
};

// Create a new stack with given capacity
struct DynamicStack* initializeStack(int capacity) {
    struct DynamicStack* stack = (struct DynamicStack*)malloc(sizeof(struct DynamicStack));
    stack->maxCapacity = capacity;
    stack->topIndex = -1;
    stack->elements = (int*)malloc(stack->maxCapacity * sizeof(int));
    return stack;
}

// Check if the stack is full
int isStackFull(struct DynamicStack* stack) {
    return stack->topIndex == stack->maxCapacity - 1;
}

// Check if the stack is empty
int isStackEmpty(struct DynamicStack* stack) {
    return stack->topIndex == -1;
}

// Push an element onto the stack
void stackPush(struct DynamicStack* stack, int data) {
    if (isStackFull(stack)) {
        printf("Stack Overflow! Cannot add %d.\n", data);
        return;
    }
    stack->elements[++stack->topIndex] = data;
}

// Pop an element from the stack
int stackPop(struct DynamicStack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack Underflow! Cannot remove element.\n");
        return -1;
    }
    return stack->elements[stack->topIndex--];
}

// Define a queue using two stacks
struct TwoStackQueue {
    struct DynamicStack* inputStack;
    struct DynamicStack* outputStack;
};

// Initialize a queue with two stacks
struct TwoStackQueue* initializeQueue(int capacity) {
    struct TwoStackQueue* queue = (struct TwoStackQueue*)malloc(sizeof(struct TwoStackQueue));
    queue->inputStack = initializeStack(capacity);
    queue->outputStack = initializeStack(capacity);
    return queue;
}

// Add an element to the queue
void addToQueue(struct TwoStackQueue* queue, int data) {
    stackPush(queue->inputStack, data);
    printf("%d added to the queue.\n", data);
}

// Remove an element from the queue
int removeFromQueue(struct TwoStackQueue* queue) {
    if (isStackEmpty(queue->inputStack) && isStackEmpty(queue->outputStack)) {
        printf("Queue is empty! Cannot dequeue.\n");
        return -1;
    }
    if (isStackEmpty(queue->outputStack)) {
        while (!isStackEmpty(queue->inputStack)) {
            stackPush(queue->outputStack, stackPop(queue->inputStack));
        }
    }
    return stackPop(queue->outputStack);
}

// Main program to test the queue implementation
int main() {
    int maxCapacity = 5;
    struct TwoStackQueue* myQueue = initializeQueue(maxCapacity);
    int userChoice, inputValue;

    while (1) {
        printf("\nSelect an operation:\n");
        printf("1. Enqueue (Add to queue)\n");
        printf("2. Dequeue (Remove from queue)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1: 
                printf("Enter a value to add to the queue: ");
                scanf("%d", &inputValue);
                addToQueue(myQueue, inputValue);
                break;

            case 2: 
                inputValue = removeFromQueue(myQueue);
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
