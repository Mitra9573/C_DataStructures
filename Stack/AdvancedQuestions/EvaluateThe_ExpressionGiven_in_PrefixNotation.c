#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Define a dynamic size for the stack
#define INITIAL_SIZE 10

// Stack structure
struct Stack {
       
    int *arr;
    int top;
    int capacity;
};

// Function to initialize the stack
void initializeStack(struct Stack *stack, int capacity) {
    stack->arr = (int *)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
}

// Function to check if the stack is empty
int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

// Function to check if the stack is full
int isFull(struct Stack *stack) {
    return stack->top == stack->capacity - 1;
}

// Function to expand the stack when full
void expandStack(struct Stack *stack) {
    stack->capacity *= 2;
    stack->arr = (int *)realloc(stack->arr, stack->capacity * sizeof(int));
}

// Function to push an element onto the stack
void push(struct Stack *stack, int value) {
    if (isFull(stack)) {
        expandStack(stack); // Expand the stack when it's full
    }
    stack->arr[++stack->top] = value;
}

// Function to pop an element from the stack
int pop(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->arr[stack->top--];
}

// Function to evaluate the prefix expression
int evaluatePrefix(char *exp) {
    struct Stack stack;
    initializeStack(&stack, INITIAL_SIZE); // Initialize with dynamic size
    
    int len = strlen(exp);
    for (int i = len - 1; i >= 0; i--) {
        if (exp[i] == ' ') continue; // Skip spaces

        // If the character is a digit
        if (isdigit(exp[i])) {
            int num = 0;
            while (i >= 0 && isdigit(exp[i])) {
                num = num * 10 + (exp[i] - '0');
                i--;
            }
            i++; // Adjust the index as we go backwards
            push(&stack, num); // Push the number to stack
        }
        else { // Operator encountered
            int operand1 = pop(&stack);
            int operand2 = pop(&stack);
            int result;
            switch (exp[i]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        printf("Division by zero is not allowed.\n");
                        free(stack.arr);
                        return -1;
                    }
                    result = operand1 / operand2;
                    break;
                default:
                    printf("Invalid operator\n");
                    free(stack.arr);
                    return -1;
            }
            push(&stack, result); // Push the result back onto stack
        }
    }

    int finalResult = pop(&stack);
    free(stack.arr); // Free dynamically allocated memory
    return finalResult;
}

int main() {
    // Dynamically allocate memory for the expression input
    char *expression = NULL;
    size_t bufferSize = 0;
    
    printf("Enter a prefix expression: ");
    getline(&expression, &bufferSize, stdin); // Read entire line as prefix expression

    // Remove the trailing newline character if it exists
    expression[strcspn(expression, "\n")] = '\0';
    
    int result = evaluatePrefix(expression);
    printf("Result: %d\n", result);

    // Free the memory allocated for the expression
    free(expression);

    return 0;
}
