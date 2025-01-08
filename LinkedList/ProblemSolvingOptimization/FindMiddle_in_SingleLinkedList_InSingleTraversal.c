#include <stdio.h>
#include <stdlib.h>

// Definition of the linked list node
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

// Function to find the middle node of the linked list
void findMiddle(struct Node* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    struct Node* slowPointer = head;
    struct Node* fastPointer = head;

    // Traverse the list with two pointers: slowPointer (moves one step at a time) and fastPointer (moves two steps at a time)
    while (fastPointer != NULL && fastPointer->next != NULL) {
        slowPointer = slowPointer->next;
        fastPointer = fastPointer->next->next;
    }

    printf("The middle node is: %d\n", slowPointer->value);
}

// Function to display the linked list
void displayList(struct Node* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    struct Node* currentNode = head;
    while (currentNode != NULL) {
        printf("%d ", currentNode->value);
        currentNode = currentNode->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    int nodeCount, nodeValue;

    // Get the number of nodes from the user
    printf("Enter the number of nodes: ");
    scanf("%d", &nodeCount);

    // Get the values for each node from the user and create the linked list
    printf("Enter the values of the nodes:\n");
    for (int i = 0; i < nodeCount; i++) {
        scanf("%d", &nodeValue);
        struct Node* newNode = createNode(nodeValue);

        // If the list is empty, initialize head and tail
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode; // Link the new node to the last node
            tail = newNode; // Update the tail pointer to the new node
        }
    }

    // Display the linked list
    printf("The linked list is:\n");
    displayList(head);

    // Find and display the middle node
    findMiddle(head);

    return 0;
}
