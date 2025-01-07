#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define the structure for a stack node
struct StackNode {
    int value;               // Value of the node
    int currentMax;          // Maximum value in the stack at this node
    struct StackNode* nextNode;  // Pointer to the next node
};

// Function to create a new stack node
struct StackNode* createStackNode(int value, int currentMax) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->value = value;
    newNode->currentMax = currentMax;
    newNode->nextNode = NULL;
    return newNode;
}

// Function to check if the stack is empty
int isEmpty(struct StackNode* stackTop) {
    return stackTop == NULL;
}

// Function to push an element onto the stack
void pushToStack(struct StackNode** stackTop, int value) {
    int currentMax = isEmpty(*stackTop) ? value : (value > (*stackTop)->currentMax ? value : (*stackTop)->currentMax);
    struct StackNode* newNode = createStackNode(value, currentMax);
    newNode->nextNode = *stackTop;
    *stackTop = newNode;
    printf("Pushed %d onto the stack.\n", value);
}

// Function to pop an element from the stack
int popFromStack(struct StackNode** stackTop) {
    if (isEmpty(*stackTop)) {
        printf("Stack underflow!\n");
        return INT_MIN;
    }
    struct StackNode* currentNode = *stackTop;
    int poppedValue = currentNode->value;
    *stackTop = currentNode->nextNode;
    free(currentNode);
    return poppedValue;
}

// Function to get the top element of the stack
int getStackTop(struct StackNode* stackTop) {
    if (isEmpty(stackTop)) {
        printf("Stack is empty!\n");
        return INT_MIN;
    }
    return stackTop->value;
}

// Function to get the maximum value in the stack
int getStackMax(struct StackNode* stackTop) {
    if (isEmpty(stackTop)) {
        printf("Stack is empty!\n");
        return INT_MIN;
    }
    return stackTop->currentMax;
}

int main() {
    struct StackNode* stackTop = NULL; // Initialize the stack
    int choice, value;

    while (1) {
        printf("\nChoose an operation:\n");
        printf("1. Push\n2. Pop\n3. Top\n4. Get Maximum\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                printf("Enter a value to push: ");
                scanf("%d", &value);
                pushToStack(&stackTop, value);
                break;

            case 2: 
                value = popFromStack(&stackTop);
                if (value != INT_MIN) {
                    printf("Popped %d from the stack.\n", value);
                }
                break;

            case 3: 
                value = getStackTop(stackTop);
                if (value != INT_MIN) {
                    printf("Top of the stack is %d.\n", value);
                }
                break;

            case 4:  
                value = getStackMax(stackTop);
                if (value != INT_MIN) {
                    printf("Maximum value in the stack is %d.\n", value);
                }
                break;

            case 5:  
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }

    return 0;
}
