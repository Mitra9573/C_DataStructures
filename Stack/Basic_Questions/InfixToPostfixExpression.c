#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// StackNode structure definition
struct StackNode {
    char value;
    struct StackNode* next;
};

// Function to create a new node
struct StackNode* createNode(char value) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to push a value onto the stack
void push(struct StackNode** stackTop, char value) {
    struct StackNode* newNode = createNode(value);
    newNode->next = *stackTop;
    *stackTop = newNode;
}

// Function to pop a value from the stack
char pop(struct StackNode** stackTop) {
    if (*stackTop == NULL) {
        printf("Stack underflow!\n");
        return -1;
    }
    struct StackNode* temp = *stackTop;
    char poppedValue = temp->value;
    *stackTop = (*stackTop)->next;
    free(temp);
    return poppedValue;
}

// Function to peek at the top value of the stack
char peek(struct StackNode* stackTop) {
    if (stackTop == NULL) {
        return -1;
    }
    return stackTop->value;
}

// Function to determine operator precedence
int getPrecedence(char operator) {
    if (operator == '+' || operator == '-') {
        return 1;
    }
    if (operator == '*' || operator == '/') {
        return 2;
    }
    return 0;
}

// Function to convert infix expression to postfix
void convertInfixToPostfix(char* infix, char* postfix) {
    struct StackNode* operatorStack = NULL;
    int postfixIndex = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char currentChar = infix[i];

        if (isdigit(currentChar)) {
            postfix[postfixIndex++] = currentChar;
        } else if (currentChar == '(') {
            push(&operatorStack, currentChar);
        } else if (currentChar == ')') {
            while (peek(operatorStack) != '(') {
                postfix[postfixIndex++] = pop(&operatorStack);
                if (operatorStack == NULL) {
                    printf("Error: Mismatched parentheses.\n");
                    exit(1);
                }
            }
            pop(&operatorStack);  // Pop '('
        } else {
            while (operatorStack != NULL && getPrecedence(peek(operatorStack)) >= getPrecedence(currentChar)) {
                postfix[postfixIndex++] = pop(&operatorStack);
            }
            push(&operatorStack, currentChar);
        }
    }

    while (operatorStack != NULL) {
        if (peek(operatorStack) == '(') {
            printf("Error: Mismatched parentheses.\n");
            exit(1);
        }
        postfix[postfixIndex++] = pop(&operatorStack);
    }
    postfix[postfixIndex] = '\0';
}

// Function to evaluate a postfix expression
int evaluatePostfixExpression(char* postfix) {
    struct StackNode* operandStack = NULL;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char currentChar = postfix[i];

        if (isdigit(currentChar)) {
            push(&operandStack, currentChar - '0');
        } else {
            int secondOperand = pop(&operandStack);
            int firstOperand = pop(&operandStack);
            int result;

            switch (currentChar) {
                case '+': result = firstOperand + secondOperand; break;
                case '-': result = firstOperand - secondOperand; break;
                case '*': result = firstOperand * secondOperand; break;
                case '/': 
                    if (secondOperand == 0) {
                        printf("Error: Division by zero.\n");
                        exit(1);
                    }
                    result = firstOperand / secondOperand; 
                    break;
                default: 
                    printf("Error: Invalid operator %c.\n", currentChar);
                    exit(1);
            }

            push(&operandStack, result);
        }
    }

    return pop(&operandStack);
}

int main() {
    char infix[100], postfix[100];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    convertInfixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

    int result = evaluatePostfixExpression(postfix);
    printf("Result: %d\n", result);

    return 0;
}
