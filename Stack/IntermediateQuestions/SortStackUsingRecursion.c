#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define a node in the linked list representing the stack
struct StackNode {
    int value;
    struct StackNode* next;
};

// Function to create a new stack node
struct StackNode* createStackNode(int value) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Push a value onto the stack
void pushToStack(struct StackNode** stackTop, int value) {
    struct StackNode* newNode = createStackNode(value);
    newNode->next = *stackTop;
    *stackTop = newNode;
}

// Pop a value from the stack
int popFromStack(struct StackNode** stackTop) {
    if (*stackTop == NULL) {
        printf("Stack underflow!\n");
        return INT_MIN;
    }
    struct StackNode* tempNode = *stackTop;
    int poppedValue = tempNode->value;
    *stackTop = (*stackTop)->next;
    free(tempNode);
    return poppedValue;
}

// Peek at the top value of the stack
int peekTop(struct StackNode* stackTop) {
    return (stackTop != NULL) ? stackTop->value : INT_MIN;
}

// Check if the stack is empty
int isStackEmpty(struct StackNode* stackTop) {
    return stackTop == NULL;
}

// Insert a value into the stack in a sorted order
void insertInSortedOrder(struct StackNode** stackTop, int value) {
    if (isStackEmpty(*stackTop) || value > peekTop(*stackTop)) {
        pushToStack(stackTop, value);
        return;
    }

    int tempValue = popFromStack(stackTop);
    insertInSortedOrder(stackTop, value);
    pushToStack(stackTop, tempValue);
}

// Sort the stack using recursion
void sortStackRecursively(struct StackNode** stackTop) {
    if (!isStackEmpty(*stackTop)) {
        int tempValue = popFromStack(stackTop);
        sortStackRecursively(stackTop);
        insertInSortedOrder(stackTop, tempValue);
    }
}

// Print the stack elements
void printStackElements(struct StackNode* stackTop) {
    printf("Stack contents: ");
    while (stackTop != NULL) {
        printf("%d ", stackTop->value);
        stackTop = stackTop->next;
    }
    printf("\n");
}

// Main function to demonstrate the stack sorting
int main() {
    struct StackNode* stackTop = NULL;
    int numberOfElements, inputValue;

    printf("Enter the number of elements in the stack: ");
    scanf("%d", &numberOfElements);

    printf("Enter the elements:\n");
    for (int i = 0; i < numberOfElements; i++) {
        scanf("%d", &inputValue);
        pushToStack(&stackTop, inputValue);
    }

    printf("Original Stack:\n");
    printStackElements(stackTop);

    sortStackRecursively(&stackTop);

    printf("\nSorted Stack:\n");
    printStackElements(stackTop);

    return 0;
}
