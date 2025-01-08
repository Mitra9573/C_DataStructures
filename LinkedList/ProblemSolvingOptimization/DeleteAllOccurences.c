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

// Function to delete all occurrences of a given value in the list
void deleteOccurrences(struct Node** head, int valueToDelete) {
    if (*head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    struct Node* current = *head;
    struct Node* previous = NULL;

    // Delete occurrences from the start of the list
    while (current != NULL && current->value == valueToDelete) {
        *head = current->next;
        free(current);
        current = *head;
    }

    // Delete occurrences from the rest of the list
    while (current != NULL) {
        if (current->value == valueToDelete) {
            previous->next = current->next;
            free(current);
            current = previous->next;
        } else {
            previous = current;
            current = current->next;
        }
    }

    printf("All occurrences of %d have been deleted.\n", valueToDelete);
}

// Function to display the linked list
void displayList(struct Node* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    int nodeCount, nodeValue, keyToDelete;

    // Get the number of nodes from the user
    printf("Enter the number of nodes: ");
    scanf("%d", &nodeCount);

    printf("Enter the values of the nodes:\n");
    for (int i = 0; i < nodeCount; i++) {
        scanf("%d", &nodeValue);
        struct Node* newNode = createNode(nodeValue);
        
        if (head == NULL) {
            head = tail = newNode; // First node
        } else {
            tail->next = newNode; // Link the new node to the last node
            tail = newNode; // Update the tail
        }
    }

    printf("The linked list is:\n");
    displayList(head);

    // Get the key to delete
    printf("Enter the value to delete: ");
    scanf("%d", &keyToDelete);

    // Delete all occurrences of the given value
    deleteOccurrences(&head, keyToDelete);

    printf("The updated linked list is:\n");
    displayList(head);

    return 0;
}
