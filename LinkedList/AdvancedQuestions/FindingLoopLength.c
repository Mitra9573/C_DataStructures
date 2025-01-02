#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the linked list
struct Node {
    int value;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to detect a loop and find its length
int findLoopLength(struct Node* head) {
    if (!head) return 0;
    
    struct Node* slowPointer = head;
    struct Node* fastPointer = head;
    
    while (fastPointer && fastPointer->next) {
        slowPointer = slowPointer->next;        
        fastPointer = fastPointer->next->next;  
        
        if (slowPointer == fastPointer) {
            break;
        }
    }

    if (slowPointer != fastPointer) {
        return 0;
    }

    int loopLength = 1;
    struct Node* currentPointer = slowPointer->next;
    while (currentPointer != slowPointer) {
        currentPointer = currentPointer->next;
        loopLength++;
    }
    
    return loopLength;
}

// Function to create a loop in the linked list
void createLoop(struct Node* head, int loopStartIndex) {
    struct Node* currentPointer = head;
    struct Node* loopStartPointer = NULL;
    int currentIndex = 0;
    
    while (currentPointer->next) {
        if (currentIndex == loopStartIndex) {
            loopStartPointer = currentPointer;
        }
        currentPointer = currentPointer->next;
        currentIndex++;
    }

    if (loopStartPointer) {
        currentPointer->next = loopStartPointer;
    }
}

// Function to print the linked list
void printList(struct Node* head) {
    struct Node* tempPointer = head;
    while (tempPointer) {
        printf("%d ", tempPointer->value);
        tempPointer = tempPointer->next;
    }
    printf("\n");
}

// Main function to demonstrate the functionality
int main() {
    struct Node* head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    head->next->next->next = createNode(40);
    head->next->next->next->next = createNode(50);

    // Create a loop in the linked list
    createLoop(head, 3);

    // Detect loop and find its length
    int loopLength = findLoopLength(head);
    
    if (loopLength > 0) {
        printf("Loop detected. Loop length: %d\n", loopLength);
    } else {
        printf("No loop detected.\n");
    }
    
    return 0;
}
