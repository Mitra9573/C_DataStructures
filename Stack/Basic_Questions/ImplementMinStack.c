#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure definition for a stack node
struct StackNode {
    int value;                // Value of the node
    int currentMin;           // Minimum value in the stack up to this node
    struct StackNode* next;   // Pointer to the next node
};

// Function to create a new stack node
struct StackNode* createNode(int element, int currentMin) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!newNode) {
        printf("Memory allocation failed! Exiting...\n");
        exit(1);
    }
    newNode->value = element;
    newNode->currentMin = currentMin;
    newNode->next = NULL;
    return newNode;
}

// Function to push an element onto the stack
void push(struct StackNode** stackHead, int element) {
    int min = (*stackHead == NULL) ? element : (element < (*stackHead)->currentMin ? element : (*stackHead)->currentMin);
    struct StackNode* newNode = createNode(element, min);
    newNode->next = *stackHead;
    *stackHead = newNode;
    printf("Pushed %d onto the stack. Current minimum: %d\n", element, min);
}

// Function to pop an element from the stack
int pop(struct StackNode** stackHead) {
    if (*stackHead == NULL) {
        printf("Stack underflow! Cannot pop.\n");
        return INT_MIN;
    }
    struct StackNode* temp = *stackHead;
    int poppedElement = temp->value;
    *stackHead = (*stackHead)->next;
    free(temp);
    return poppedElement;
}

// Function to get the top element of the stack
int peek(struct StackNode* stackHead) {
    if (stackHead == NULL) {
        printf("Stack is empty! Cannot peek.\n");
        return INT_MIN;
    }
    return stackHead->value;
}

// Function to get the minimum value in the stack
int getMin(struct StackNode* stackHead) {
    if (stackHead == NULL) {
        printf("Stack is empty! Cannot determine the minimum value.\n");
        return INT_MIN;
    }
    return stackHead->currentMin;
}

int main() {
    struct StackNode* stackHead = NULL; // Pointer to the top of the stack
    int choice, element;

    while (1) {
        printf("\nChoose an operation:\n");
        printf("1. Push\n2. Pop\n3. Peek\n4. Get Minimum\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                printf("Enter a value to push: ");
                scanf("%d", &element);
                push(&stackHead, element);
                break;

            case 2: 
                element = pop(&stackHead);
                if (element != INT_MIN) {
                    printf("Popped %d from the stack.\n", element);
                }
                break;

            case 3: 
                element = peek(stackHead);
                if (element != INT_MIN) {
                    printf("Top of the stack is %d.\n", element);
                }
                break;

            case 4:  
                element = getMin(stackHead);
                if (element != INT_MIN) {
                    printf("Minimum value in the stack is %d.\n", element);
                }
                break;

            case 5: 
                printf("Exiting program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }

    return 0;
}
