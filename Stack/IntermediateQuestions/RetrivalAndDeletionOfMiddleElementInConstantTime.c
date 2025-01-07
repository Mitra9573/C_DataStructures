#include <stdio.h>
#include <stdlib.h>

// Node structure for the doubly linked list
struct Node {
    int value;
    struct Node* previous;
    struct Node* next;
};

// Stack structure with top, middle, and size tracking
struct DoublyLinkedStack {
    struct Node* topElement;
    struct Node* middleElement;
    int elementCount;
};

// Function to create a new node
struct Node* createNewNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->value = value;
    newNode->previous = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize the stack
void initializeDoublyLinkedStack(struct DoublyLinkedStack* stack) {
    stack->topElement = NULL;
    stack->middleElement = NULL;
    stack->elementCount = 0;
}

// Push a value onto the stack
void pushToStack(struct DoublyLinkedStack* stack, int value) {
    struct Node* newNode = createNewNode(value);

    if (stack->topElement == NULL) {
        stack->topElement = newNode;
        stack->middleElement = newNode;
    } else {
        newNode->next = stack->topElement;
        stack->topElement->previous = newNode;
        stack->topElement = newNode;
    }

    stack->elementCount++;

    if (stack->elementCount == 1) {
        stack->middleElement = stack->topElement;
    } else if (stack->elementCount % 2 == 0) {
        stack->middleElement = stack->middleElement->previous;
    }

    printf("Pushed %d onto the stack.\n", value);
}

// Pop a value from the stack
int popFromStack(struct DoublyLinkedStack* stack) {
    if (stack->topElement == NULL) {
        printf("Stack is empty! Cannot pop.\n");
        return -1;
    }

    struct Node* tempNode = stack->topElement;
    int poppedValue = tempNode->value;

    stack->topElement = stack->topElement->next;
    if (stack->topElement != NULL) {
        stack->topElement->previous = NULL;
    }

    stack->elementCount--;

    if (stack->elementCount == 0) {
        stack->middleElement = NULL;
    } else if (stack->elementCount % 2 != 0) {
        stack->middleElement = stack->middleElement->next;
    }

    free(tempNode);
    printf("Popped %d from the stack.\n", poppedValue);
    return poppedValue;
}

// Get the middle value of the stack
int getMiddleValue(struct DoublyLinkedStack* stack) {
    if (stack->middleElement == NULL) {
        printf("Stack is empty! No middle element.\n");
        return -1;
    }
    return stack->middleElement->value;
}

// Delete the middle value from the stack
int removeMiddleValue(struct DoublyLinkedStack* stack) {
    if (stack->middleElement == NULL) {
        printf("Stack is empty! Cannot delete middle element.\n");
        return -1;
    }

    struct Node* tempNode = stack->middleElement;
    int removedValue = tempNode->value;

    if (tempNode->previous != NULL) {
        tempNode->previous->next = tempNode->next;
    }
    if (tempNode->next != NULL) {
        tempNode->next->previous = tempNode->previous;
    }

    if (stack->elementCount == 1) {
        stack->topElement = NULL;
        stack->middleElement = NULL;
    } else if (stack->elementCount % 2 == 0) {
        stack->middleElement = stack->middleElement->previous;
    } else {
        stack->middleElement = stack->middleElement->next;
    }

    free(tempNode);
    stack->elementCount--;
    printf("Deleted the middle element: %d\n", removedValue);
    return removedValue;
}

// Display the elements in the stack
void displayStackElements(struct DoublyLinkedStack* stack) {
    struct Node* currentNode = stack->topElement;
    printf("Stack elements: ");
    while (currentNode != NULL) {
        printf("%d ", currentNode->value);
        currentNode = currentNode->next;
    }
    printf("\n");
}

// Main function to test the stack operations
int main() {
    struct DoublyLinkedStack stack;
    initializeDoublyLinkedStack(&stack);

    pushToStack(&stack, 10);
    pushToStack(&stack, 20);
    pushToStack(&stack, 30);
    pushToStack(&stack, 40);
    pushToStack(&stack, 50);

    displayStackElements(&stack);
    printf("Middle element: %d\n", getMiddleValue(&stack));

    popFromStack(&stack);
    printf("Middle element after pop: %d\n", getMiddleValue(&stack));

    removeMiddleValue(&stack);
    printf("Middle element after deleting middle: %d\n", getMiddleValue(&stack));

    displayStackElements(&stack);

    return 0;
}
