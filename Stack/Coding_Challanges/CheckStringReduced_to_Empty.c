#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 1000

// Function to check if the string can be reduced to an empty string
bool canBeReducedToEmptyString(const char *inputStr) {
    char charStack[MAX_SIZE];  // Stack to simulate removing matching pairs
    int stackTop = -1;  // Stack pointer, -1 means empty stack

    // Process each character of the input string
    for (int i = 0; inputStr[i] != '\0'; i++) {
        // If the stack is not empty and the top of the stack matches the current character
        if (stackTop != -1 && charStack[stackTop] == inputStr[i]) {
            // Pop the stack by moving the top pointer down
            stackTop--;
        } else {
            // Push the current character onto the stack
            charStack[++stackTop] = inputStr[i];
        }
    }

    // If the stack is empty, the string can be reduced to empty
    return stackTop == -1;
}

int main() {
    char inputStr[MAX_SIZE];  // Input string

    // Read the string using fgets to allow spaces and dynamic input
    printf("Enter a string: ");
    fgets(inputStr, sizeof(inputStr), stdin);

    // Remove trailing newline if present
    inputStr[strcspn(inputStr, "\n")] = '\0';

    // Check if the string can be reduced to an empty string
    if (canBeReducedToEmptyString(inputStr)) {
        printf("The string can be reduced to an empty string.\n");
    } else {
        printf("The string cannot be reduced to an empty string.\n");
    }

    return 0;
}
