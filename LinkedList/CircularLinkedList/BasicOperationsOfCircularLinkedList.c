#include <stdio.h>
#include <stdlib.h>

// Define a node structure
struct CircularNode {
    int value;
    struct CircularNode* next;
};

// Function to create a new node
struct CircularNode* createCircularNode(int value) {
    struct CircularNode* newNode = (struct CircularNode*)malloc(sizeof(struct CircularNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to add a node to the circular linked list
void addNode(struct CircularNode** head, int value) {
    struct CircularNode* newNode = createCircularNode(value);

    if (*head == NULL) {
        newNode->next = newNode;
        *head = newNode;
    } else {
        struct CircularNode* current = *head;
        while (current->next != *head) {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = *head;
    }

    printf("Added %d to the list.\n", value);
}

// Function to remove the last node from the circular linked list
void removeLastNode(struct CircularNode** head) {
    if (*head == NULL) {
        printf("The list is empty. Nothing to remove.\n");
        return;
    }

    struct CircularNode* current = *head;
    if (current->next == *head) {
        *head = NULL;
        free(current);
        printf("Removed the only node from the list.\n");
        return;
    }

    struct CircularNode* previous = NULL;
    while (current->next != *head) {
        previous = current;
        current = current->next;
    }
    previous->next = *head;

    free(current);
    printf("Removed the last node from the list.\n");
}

// Function to display all nodes in the circular linked list
void displayList(struct CircularNode* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    struct CircularNode* current = head;
    printf("Circular Linked List: ");

    do {
        printf("%d ", current->value);
        current = current->next;
    } while (current != head);

    printf("\n");
}

// Main function
int main() {
    struct CircularNode* head = NULL;
    int userChoice, inputValue;

    while (1) {
        // Display menu options
        printf("\nMenu:\n");
        printf("1. Add a node\n");
        printf("2. Remove the last node\n");
        printf("3. Display the list\n");
        printf("4. Exit\n");

        // Get user input
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                printf("Enter value to add: ");
                scanf("%d", &inputValue);
                addNode(&head, inputValue);
                break;
            case 2:
                removeLastNode(&head);
                break;
            case 3:
                displayList(head);
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
