#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
    char **pages;  // Dynamic array of strings for storing page URLs
    int top;
    int capacity;  // Current capacity of the stack
} Stack;

void initStack(Stack *stack, int capacity) {
    stack->capacity = capacity;
    stack->top = -1;
    stack->pages = (char **)malloc(capacity * sizeof(char *));  // Allocating memory for the stack
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

void resizeStack(Stack *stack) {
    stack->capacity *= 2;
    stack->pages = (char **)realloc(stack->pages, stack->capacity * sizeof(char *));  // Resize stack when full
}

void push(Stack *stack, const char *url) {
    if (isFull(stack)) {
        resizeStack(stack);  // Resize stack if full
    }
    stack->pages[++stack->top] = strdup(url);  // Copy the URL into the stack
}

char *pop(Stack *stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    char *url = stack->pages[stack->top];
    stack->top--;
    return url;
}

char *peek(Stack *stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    return stack->pages[stack->top];
}

void freeStack(Stack *stack) {
    for (int i = 0; i <= stack->top; i++) {
        free(stack->pages[i]);  // Free each allocated URL string
    }
    free(stack->pages);  // Free the stack's page array
}

int main() {
    Stack historyStack, forwardStack;
    int initialCapacity = 10;

    initStack(&historyStack, initialCapacity);
    initStack(&forwardStack, initialCapacity);

    char *currentUrl = strdup("home");  // Initial current page is "home"
    int choice;

    printf("Browser Navigation Simulation\n");
    printf("Current Page: %s\n", currentUrl);

    while (1) {
        printf("\nOptions:\n");
        printf("1. Visit a new page\n");
        printf("2. Go Back\n");
        printf("3. Go Forward\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        char newPage[50];

        switch (choice) {
            case 1:
                printf("Enter the new page URL: ");
                scanf("%s", newPage);
                push(&historyStack, currentUrl);  // Push current URL to history
                free(currentUrl);  // Free memory for the old page
                currentUrl = strdup(newPage);  // Set the new current URL
                freeStack(&forwardStack);  // Clear forward stack when visiting a new page
                printf("Current Page: %s\n", currentUrl);
                break;

            case 2:
                if (isEmpty(&historyStack)) {
                    printf("No previous page to go back to.\n");
                } else {
                    push(&forwardStack, currentUrl);  // Push current URL to forward stack
                    free(currentUrl);  // Free memory for the old page
                    currentUrl = pop(&historyStack);  // Set current URL to the popped page
                    printf("Current Page: %s\n", currentUrl);
                }
                break;

            case 3:
                if (isEmpty(&forwardStack)) {
                    printf("No forward page to go to.\n");
                } else {
                    push(&historyStack, currentUrl);  // Push current URL to history stack
                    free(currentUrl);  // Free memory for the old page
                    currentUrl = pop(&forwardStack);  // Set current URL to the popped forward page
                    printf("Current Page: %s\n", currentUrl);
                }
                break;

            case 4:
                printf("Exiting browser simulation.\n");
                free(currentUrl);  // Free the current page before exiting
                freeStack(&historyStack);  // Free history stack
                freeStack(&forwardStack);  // Free forward stack
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
