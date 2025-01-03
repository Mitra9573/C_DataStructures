#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char* elements;
    int topIndex;
    int maxCapacity;
} Stack;

void initializeStack(Stack* stack, int capacity) {
    stack->elements = (char*)malloc(capacity * sizeof(char));
    stack->topIndex = -1;
    stack->maxCapacity = capacity;
}

void push(Stack* stack, char character) {
    if (stack->topIndex == stack->maxCapacity - 1) {
        printf("Stack overflow! Cannot push '%c'.\n", character);
        return;
    }
    stack->elements[++stack->topIndex] = character;
}

char pop(Stack* stack) {
    if (stack->topIndex == -1) {
        return '\0'; 
    }
    return stack->elements[stack->topIndex--];
}

bool isEmpty(Stack* stack) {
    return stack->topIndex == -1;
}

bool isOpeningBracket(char character) {
    return character == '(' || character == '{' || character == '[';
}

bool isMatchingBracket(char openBracket, char closeBracket) {
    return (openBracket == '(' && closeBracket == ')') ||
           (openBracket == '{' && closeBracket == '}') ||
           (openBracket == '[' && closeBracket == ']');
}

bool checkBalancedBrackets(char* expression) {
    int length = 0;
    while (expression[length] != '\0') length++; 

    Stack stack;
    initializeStack(&stack, length);

    for (int i = 0; i < length; i++) {
        char currentChar = expression[i];

        if (isOpeningBracket(currentChar)) {
            push(&stack, currentChar); 
        } else if (currentChar == ')' || currentChar == '}' || currentChar == ']') {
            char topBracket = pop(&stack);  
            if (!isMatchingBracket(topBracket, currentChar)) {
                free(stack.elements);
                return false;  
            }
        }
    }

    bool isBalanced = isEmpty(&stack); 
    free(stack.elements);  
    return isBalanced;
}

int main() {
    char inputExpression[100];

    printf("Enter an expression: ");
    scanf("%s", inputExpression);

    if (checkBalancedBrackets(inputExpression)) {
        printf("The expression is balanced.\n");
    } else {
        printf("The expression is not balanced.\n");
    }

    return 0;
}
