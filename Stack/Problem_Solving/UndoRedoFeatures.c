#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY 100

// Define the Stack structure to hold string states
typedef struct Stack {
    char* data[MAX_HISTORY]; // Array to store string states
    int top;                  // Index of the top element in the stack
} Stack;

// Initialize the stack
void initStack(Stack* stack) {
    stack->top = -1;
}

// Push a new string state onto the stack
void push(Stack* stack, const char* state) {
    if (stack->top < MAX_HISTORY - 1) {
        stack->data[++(stack->top)] = strdup(state); // Duplicate the string and push it
    }
}

// Pop a string state from the stack
char* pop(Stack* stack) {
    if (stack->top == -1) return NULL;
    return stack->data[(stack->top)--];
}

// Peek at the top string of the stack without popping
char* peek(Stack* stack) {
    if (stack->top == -1) return NULL;
    return stack->data[stack->top];
}

// Free the memory used by the stack
void freeStack(Stack* stack) {
    for (int i = 0; i <= stack->top; i++) {
        free(stack->data[i]);
    }
}

// Edit the current string and store the old state in the undo stack
void editString(Stack* undoStack, Stack* redoStack, char** currentString, const char* newState) {
    push(undoStack, *currentString);  // Save the current state to the undo stack
    
    free(*currentString);  // Free the old string memory
    *currentString = strdup(newState);  // Allocate new memory for the updated string
    
    redoStack->top = -1;  // Clear the redo stack
}

// Perform undo operation
void undo(Stack* undoStack, Stack* redoStack, char** currentString) {
    char* lastState = pop(undoStack);
    if (lastState) {
        push(redoStack, *currentString);  // Save the current state to the redo stack
        
        free(*currentString);  // Free the current string memory
        *currentString = lastState;  // Restore the string to the last state
        printf("Undo successful. Current string: %s\n", *currentString);
    } else {
        printf("No more undo operations available.\n");
    }
}

// Perform redo operation
void redo(Stack* undoStack, Stack* redoStack, char** currentString) {
    char* redoState = pop(redoStack);
    if (redoState) {
        push(undoStack, *currentString);  // Save the current state to the undo stack
        free(*currentString);  // Free the current string memory
        *currentString = redoState;  // Restore the string to the redo state
        printf("Redo successful. Current string: %s\n", *currentString);
    } else {
        printf("No more redo operations available.\n");
    }
}

int main() {
    Stack undoStack, redoStack;
    char* currentString = (char*)malloc(100 * sizeof(char));  // Dynamically allocate memory for the string
    
    initStack(&undoStack);
    initStack(&redoStack);
    
    // Get the initial string input dynamically
    printf("Enter the initial string: ");
    fgets(currentString, 100, stdin);
    currentString[strcspn(currentString, "\n")] = '\0';  // Remove the newline character
    
    printf("Current string: %s\n", currentString);
    
    int choice;
    char newState[100];
    
    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Edit string\n");
        printf("2. Undo\n");
        printf("3. Redo\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();  // Clear the newline character left by scanf
        
        switch (choice) {
            case 1:
                printf("Enter new string: ");
                fgets(newState, sizeof(newState), stdin);
                newState[strcspn(newState, "\n")] = '\0';  // Remove the newline character
                
                editString(&undoStack, &redoStack, &currentString, newState);
                printf("String after edit: %s\n", currentString);
                break;
            case 2:
                undo(&undoStack, &redoStack, &currentString);
                break;
            case 3:
                redo(&undoStack, &redoStack, &currentString);
                break;
            case 4:
                printf("Exiting...\n");
                free(currentString);  // Free the dynamically allocated memory for the string
                freeStack(&undoStack);
                freeStack(&redoStack);
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
