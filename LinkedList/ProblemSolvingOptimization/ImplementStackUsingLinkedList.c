#include <stdio.h>
#include <stdlib.h>

// Define a Node for the stack
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to push an element onto the stack
void push(struct Node** stackTop, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *stackTop;
    *stackTop = newNode;
    printf("%d pushed onto the stack.\n", data);
}

// Function to pop an element from the stack
int pop(struct Node** stackTop) {
    if (*stackTop == NULL) {
        printf("Stack underflow! Cannot pop from an empty stack.\n");
        return -1; // Return -1 to indicate an error
    }
    struct Node* temp = *stackTop;
    int poppedData = temp->data;
    *stackTop = temp->next;
    free(temp);
    return poppedData;
}

// Function to get the top element of the stack
int peek(struct Node* stackTop) {
    if (stackTop == NULL) {
        printf("Stack is empty! No top element.\n");
        return -1; // Return -1 to indicate an error
    }
    return stackTop->data;
}

// Function to check if the stack is empty
int isEmpty(struct Node* stackTop) {
    return stackTop == NULL;
}

// Function to display the stack
void displayStack(struct Node* stackTop) {
    if (stackTop == NULL) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack elements (top to bottom): ");
    struct Node* current = stackTop;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Main function
int main() {
    struct Node* stackTop = NULL;  // Top of the stack
    int operationChoice, inputValue;

    printf("Stack Operations Using Linked List:\n");
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Peek (Top)\n");
    printf("4. Display Stack\n");
    printf("5. Check if Stack is Empty\n");
    printf("6. Exit\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &operationChoice);

        switch (operationChoice) {
            case 1: // Push
                printf("Enter the value to push: ");
                scanf("%d", &inputValue);
                push(&stackTop, inputValue);
                break;
            case 2: // Pop
                inputValue = pop(&stackTop);
                if (inputValue != -1) {
                    printf("Popped value: %d\n", inputValue);
                }
                break;
            case 3: // Peek
                inputValue = peek(stackTop);
                if (inputValue != -1) {
                    printf("Top element: %d\n", inputValue);
                }
                break;
            case 4: // Display
                displayStack(stackTop);
                break;
            case 5: // Is Empty
                printf("Stack is %s\n", isEmpty(stackTop) ? "Empty" : "Not Empty");
                break;
            case 6: // Exit
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}
