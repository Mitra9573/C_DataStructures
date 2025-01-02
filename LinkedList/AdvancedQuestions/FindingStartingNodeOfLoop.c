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

// Function to detect the starting node of the loop
struct Node* detectLoopStart(struct Node* head) {
    struct Node* slowPointer = head;
    struct Node* fastPointer = head;

    // Step 1: Detect if a loop exists
    while (fastPointer != NULL && fastPointer->next != NULL) {
        slowPointer = slowPointer->next;
        fastPointer = fastPointer->next->next;

        // If slowPointer and fastPointer meet, a loop exists
        if (slowPointer == fastPointer) {
            // Step 2: Find the starting node of the loop
            slowPointer = head;  // Reset slowPointer to the head
            while (slowPointer != fastPointer) {
                slowPointer = slowPointer->next;
                fastPointer = fastPointer->next;
            }
            return slowPointer;  // The meeting point is the start of the loop
        }
    }

    return NULL;  // No loop detected
}

// Function to display the linked list (useful for debugging)
void printList(struct Node* head) {
    struct Node* currentNode = head;
    while (currentNode != NULL) {
        printf("%d ", currentNode->value);
        currentNode = currentNode->next;
    }
    printf("\n");
}

// Main function to test the loop detection
int main() {
    struct Node* head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    head->next->next->next = createNode(40);
    head->next->next->next->next = createNode(50);

    // Create a loop for testing
    head->next->next->next->next->next = head->next->next;  // 50 -> 30

    struct Node* loopStartNode = detectLoopStart(head);
    if (loopStartNode != NULL) {
        printf("Loop starts at node with value: %d\n", loopStartNode->value);
    } else {
        printf("No loop detected in the linked list.\n");
    }

    return 0;
}
