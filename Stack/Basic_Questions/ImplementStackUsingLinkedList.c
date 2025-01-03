#include <stdio.h>
#include <stdlib.h>

// Define the structure for a stack node
struct StackNode {
    int value;
    struct StackNode *next;
};

// Function to create a new stack node
struct StackNode* createStackNode(int value) {
    struct StackNode *newStackNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    if (newStackNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newStackNode->value = value;
    newStackNode->next = NULL;
    return newStackNode;
}

// Function to check if the stack is empty
int isEmpty(struct StackNode *stackTop) {
    return stackTop == NULL;
}

// Function to push an element onto the stack
struct StackNode* pushToStack(struct StackNode *stackTop, int value) {
    struct StackNode *newStackNode = createStackNode(value);
    newStackNode->next = stackTop;
    stackTop = newStackNode;
    printf("%d pushed to stack\n", value);
    return stackTop;
}

// Function to pop an element from the stack
int popFromStack(struct StackNode **stackTop) {
    if (isEmpty(*stackTop)) {
        printf("Stack Underflow! Cannot pop.\n");
        return -1;
    }
    struct StackNode *currentNode = *stackTop;
    int poppedValue = currentNode->value;
    *stackTop = currentNode->next;
    free(currentNode);
    return poppedValue;
}

// Function to peek the top element of the stack
int peekStack(struct StackNode *stackTop) {
    if (isEmpty(stackTop)) {
        printf("Stack is empty! Cannot peek.\n");
        return -1;
    }
    return stackTop->value;
}

// Function to display the stack
void displayStack(struct StackNode *stackTop) {
    if (isEmpty(stackTop)) {
        printf("Stack is empty!\n");
        return;
    }
    struct StackNode *currentNode = stackTop;
    printf("Stack elements: ");
    while (currentNode != NULL) {
        printf("%d ", currentNode->value);
        currentNode = currentNode->next;
    }
    printf("\n");
}

int main() {
    struct StackNode *stackTop = NULL; // Initialize an empty stack

    // Push elements onto the stack
    stackTop = pushToStack(stackTop, 10);
    stackTop = pushToStack(stackTop, 20);
    stackTop = pushToStack(stackTop, 30);
    stackTop = pushToStack(stackTop, 40);
    stackTop = pushToStack(stackTop, 50);

    // Display the stack
    displayStack(stackTop);

    // Peek the top element
    printf("Top element: %d\n", peekStack(stackTop));

    // Pop elements from the stack
    printf("Popped element: %d\n", popFromStack(&stackTop));
    printf("Popped element: %d\n", popFromStack(&stackTop));
    printf("Popped element: %d\n", popFromStack(&stackTop));
    printf("Popped element: %d\n", popFromStack(&stackTop));
    printf("Popped element: %d\n", popFromStack(&stackTop));

    // Display the stack after popping
    displayStack(stackTop);

    return 0;
}
