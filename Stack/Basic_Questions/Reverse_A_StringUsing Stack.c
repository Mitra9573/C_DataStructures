#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a stack node
struct StackNode {
    char value;
    struct StackNode *next;
};

// Function to create a new stack node
struct StackNode* createStackNode(char value) {
    struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to push a character onto the stack
struct StackNode* push(struct StackNode *stackTop, char value) {
    struct StackNode *newNode = createStackNode(value);
    newNode->next = stackTop;
    stackTop = newNode;
    return stackTop;
}

// Function to pop a character from the stack
char pop(struct StackNode **stackTop) {
    if (*stackTop == NULL) {
        printf("Stack underflow! Cannot pop.\n");
        return '\0';
    }
    struct StackNode *temp = *stackTop;
    char poppedValue = temp->value;
    *stackTop = (*stackTop)->next;
    free(temp);
    return poppedValue;
}

// Function to reverse a string using a stack
void reverseString(char *inputStr) {
    struct StackNode *charStack = NULL;  // Initialize an empty stack

    // Push all characters of the string onto the stack
    for (int i = 0; inputStr[i] != '\0'; i++) {
        charStack = push(charStack, inputStr[i]);
    }

    // Pop characters from the stack and overwrite the string
    int index = 0;
    while (charStack != NULL) {
        inputStr[index++] = pop(&charStack);
    }
}

int main() {
    char inputStr[100];  // Allow a larger input for flexibility

    printf("Enter a string: ");
    scanf("%[^\n]s", inputStr);  // Read the input string (max 100 characters)

    printf("Original string: %s\n", inputStr);
    reverseString(inputStr);
    printf("Reversed string: %s\n", inputStr);

    return 0;
}
