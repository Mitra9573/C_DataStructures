#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack structure to hold integers
typedef struct {
    int data[MAX];
    int top;
} Stack;

// Initialize the stack
void initStack(Stack* stack) {
    stack->top = -1;
}

// Push an element onto the stack
void push(Stack* stack, int value) {
    if (stack->top < MAX - 1) {
        stack->data[++(stack->top)] = value;
    } else {
        printf("Stack overflow\n");
    }
}

// Pop an element from the stack
int pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->data[(stack->top)--];
}

// Perform a mathematical operation
int operate(int operand1, int operand2, char operator) {
    switch (operator) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand1 / operand2;
        case '%': return operand1 % operand2;
        default: return 0;
    }
}

int main() {
    Stack calculatorStack;
    initStack(&calculatorStack);

    int number1, number2, result;
    char operator;
    char continueOperation;

    do {
        // Dynamic input for calculation
        printf("Enter first integer: ");
        scanf("%d", &number1);
        printf("Enter second integer: ");
        scanf("%d", &number2);
        printf("Enter an operator (+, -, *, /, %%): ");
        scanf(" %c", &operator);  // Note the space before %c to consume any previous whitespace

        // Push the operands onto the stack
        push(&calculatorStack, number1);
        push(&calculatorStack, number2);

        // Pop the operands from the stack
        number2 = pop(&calculatorStack);
        number1 = pop(&calculatorStack);

        // Perform the operation and print the result
        result = operate(number1, number2, operator);
        printf("Result of %d %c %d = %d\n", number1, operator, number2, result);

        // Ask if the user wants to perform another operation
        printf("Do you want to perform another operation? (y/n): ");
        scanf(" %c", &continueOperation);  // Space to ignore any leftover newline

    } while (continueOperation == 'y' || continueOperation == 'Y');

    return 0;
}
