#include <stdio.h>
#include <stdlib.h>

// Node structure for the linked list
struct Node {
    int value;         // Value of the node
    struct Node* next; // Pointer to the next node
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to get the length of the linked list
int getLength(struct Node* head) {
    int length = 0;
    struct Node* current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

// Function to split the linked list into k parts
struct Node** splitList(struct Node* head, int k) {
    int length = getLength(head);
    int partSize = length / k;        // Base size of each part
    int extraNodes = length % k;      // Extra nodes to be distributed among the parts

    struct Node** parts = (struct Node**)malloc(k * sizeof(struct Node*));
    struct Node* current = head;
    struct Node* previous = NULL;

    // Loop to split the list into k parts
    for (int i = 0; i < k; i++) {
        parts[i] = current; 
        int currentPartSize = partSize + (extraNodes > 0 ? 1 : 0);
        extraNodes--;

        // Move to the next part
        for (int j = 0; j < currentPartSize && current != NULL; j++) {
            previous = current;
            current = current->next;
        }
        // Break the link for the current part if it's not the last one
        if (previous != NULL) {
            previous->next = NULL;
        }
    }

    return parts;
}

// Function to display the linked list
void displayList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

// Main function
int main() {
    struct Node* head = NULL;
    struct Node* tail = NULL;

    int numElements, partCount, nodeValue;
    printf("Enter the number of elements in the linked list: ");
    scanf("%d", &numElements);

    printf("Enter the elements:\n");
    for (int i = 0; i < numElements; i++) {
        scanf("%d", &nodeValue);
        struct Node* newNode = createNode(nodeValue);
        if (head == NULL) {
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    printf("Enter the number of parts to split the list into (k): ");
    scanf("%d", &partCount);

    if (partCount <= 0) {
        printf("Invalid value of k. Must be greater than 0.\n");
        return 1;
    }

    struct Node** parts = splitList(head, partCount);
    printf("The linked list split into %d parts:\n", partCount);
    for (int i = 0; i < partCount; i++) {
        printf("Part %d: ", i + 1);
        displayList(parts[i]);
    }

    // Free the allocated memory for parts array
    free(parts);

    return 0;
}
