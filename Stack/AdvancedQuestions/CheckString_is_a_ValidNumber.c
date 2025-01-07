#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Stack structure
struct Stack {
    char *data;
    int top;
    int capacity;
};

// Function to create a stack
struct Stack* createStack(int capacity) {
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->data = (char *)malloc(capacity * sizeof(char));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// Function to check if the stack is full
int isFull(struct Stack *stack) {
    return stack->top == stack->capacity - 1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(struct Stack *stack, char ch) {
    if (!isFull(stack)) {
        stack->data[++stack->top] = ch;
    }
}

// Function to pop an element from the stack
char pop(struct Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->data[stack->top--];
    }
    return '\0';
}

// Function to peek the top element of the stack
char peek(struct Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->data[stack->top];
    }
    return '\0';
}

// Function to validate if a string is a valid number
int isValidNumber(const char *input) {
    int length = strlen(input);
    struct Stack *stack = createStack(length);
    int index = 0;
    int hasDigit = 0, hasDot = 0, hasExponent = 0;

    // Skip leading spaces
    while (input[index] == ' ') index++;

    // Handle optional sign at the start
    if (input[index] == '+' || input[index] == '-') {
        push(stack, input[index]);
        index++;
    }

    // Process the main part of the number
    while (input[index] != '\0') {
        char currentChar = input[index];

        if (isdigit(currentChar)) {
            hasDigit = 1;
            push(stack, currentChar);
        }
        else if (currentChar == '.' && !hasDot && !hasExponent) {
            hasDot = 1;
            push(stack, currentChar);
        }
        else if ((currentChar == 'e' || currentChar == 'E') && hasDigit && !hasExponent) {
            hasExponent = 1;
            hasDigit = 0; 
            push(stack, currentChar);

            // Check for optional sign after exponent
            index++;
            if (input[index] == '+' || input[index] == '-') {
                push(stack, input[index]);
                index++;
            }

            // Check if digits follow the exponent
            if (!isdigit(input[index])) {
                free(stack->data);
                free(stack);
                return 0;
            }

            while (isdigit(input[index])) {
                hasDigit = 1;
                push(stack, input[index]);
                index++;
            }

            continue; 
        }
        else if (currentChar == ' ') {
            break;
        }
        else {
            break;
        }
        index++;
    }

    // Skip trailing spaces
    while (input[index] == ' ') index++;

    // The string is valid if it ends with a digit and there are no invalid characters
    int isValid = hasDigit && input[index] == '\0';

    free(stack->data);
    free(stack);
    return isValid;
}

// Main function to run the program
int main() {
    char *input = NULL;
    size_t bufferSize = 0;

    printf("Enter a string: ");
    
    // Read the input string dynamically
    if (getline(&input, &bufferSize, stdin) == -1) {
        printf("Error reading input.\n");
        return 1;
    }

    // Remove newline character if it exists
    input[strcspn(input, "\n")] = '\0'; 

    // Check if the input is a valid number
    if (isValidNumber(input)) {
        printf("The string is a valid number.\n");
    } else {
        printf("The string is not a valid number.\n");
    }

    // Free the dynamically allocated memory
    free(input);

    return 0;
}
