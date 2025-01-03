#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct StackNode {
    int value;
    struct StackNode* next;
};

// Function to create a new stack node
struct StackNode* createStackNode(int value) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to push a value onto the stack
void pushToStack(struct StackNode** stackTop, int value) {
    struct StackNode* newNode = createStackNode(value);
    newNode->next = *stackTop;
    *stackTop = newNode;
}

// Function to pop a value from the stack
int popFromStack(struct StackNode** stackTop) {
    if (*stackTop == NULL) {
        printf("Stack underflow!\n");
        return -1;
    }
    struct StackNode* tempNode = *stackTop;
    int poppedValue = tempNode->value;
    *stackTop = (*stackTop)->next;
    free(tempNode);
    return poppedValue;
}

// Function to evaluate a postfix expression
int evaluatePostfixExpression(char* expression) {
    struct StackNode* stackTop = NULL; 
    
    for (int index = 0; expression[index] != '\0'; index++) {
        char currentChar = expression[index];

        if (isdigit(currentChar)) {
            pushToStack(&stackTop, currentChar - '0'); // Convert char to int
        } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
            int operand2 = popFromStack(&stackTop);
            int operand1 = popFromStack(&stackTop);
            int result;

            switch (currentChar) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
                default: result = 0; break;
            }
            pushToStack(&stackTop, result);
        }
    }
    return popFromStack(&stackTop);
}

int main() {
    char postfixExpression[100];

    printf("Enter a postfix expression: ");
    scanf("%s", postfixExpression);

    int evaluationResult = evaluatePostfixExpression(postfixExpression);
    printf("Result: %d\n", evaluationResult);

    return 0;
}
