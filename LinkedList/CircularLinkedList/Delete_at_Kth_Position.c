#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in a circular linked list
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
        printf("Added %d as the first node.\n", value);
        return;
    }

    struct CircularNode* current = *head;
    while (current->next != *head) {
        current = current->next;
    }

    current->next = newNode;
    newNode->next = *head;
    printf("Added %d to the list.\n", value);
}

// Function to display the circular linked list
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

// Function to remove the k-th node from the circular linked list
void removeNodeAtPosition(struct CircularNode** head, int position) {
    if (*head == NULL) {
        printf("The list is empty. Nothing to remove.\n");
        return;
    }

    struct CircularNode* current = *head;
    struct CircularNode* previous = NULL;

    // Handle the case when the position is 1 (removing the head node)
    if (position == 1) {
        while (current->next != *head) {
            current = current->next;
        }
        if (current == *head) { // Single node in the list
            free(*head);
            *head = NULL;
            printf("Removed the only node from the list.\n");
            return;
        }
        current->next = (*head)->next;
        struct CircularNode* temp = *head;
        *head = (*head)->next;
        free(temp);
        printf("Removed node at position %d (head node).\n", position);
        return;
    }

    previous = *head;
    current = (*head)->next;
    int counter = 2;

    // Traverse to the k-th node
    while (current != *head && counter < position) {
        previous = current;
        current = current->next;
        counter++;
    }

    if (counter == position && current != *head) {
        previous->next = current->next;
        free(current);
        printf("Removed node at position %d.\n", position);
    } else {
        printf("Position %d does not exist in the list.\n", position);
    }
}

int main() {
    struct CircularNode* head = NULL;
    int choice, value, position;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add a node to the list\n");
        printf("2. Remove a node at a specific position\n");
        printf("3. Display the list\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting program.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter value to add: ");
                if (scanf("%d", &value) != 1) {
                    printf("Invalid input. Operation aborted.\n");
                    break;
                }
                addNode(&head, value);
                break;

            case 2:
                printf("Enter the position of the node to remove: ");
                if (scanf("%d", &position) != 1 || position < 1) {
                    printf("Invalid position. Operation aborted.\n");
                    break;
                }
                removeNodeAtPosition(&head, position);
                break;

            case 3:
                displayList(head);
                break;

            case 4:
                printf("Exiting program...\n");
                if (head != NULL) {
                    struct CircularNode* current = head->next;
                    while (current != head) {
                        struct CircularNode* nextNode = current->next;
                        free(current);
                        current = nextNode;
                    }
                    free(head);
                }
                return 0;

            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    }

    return 0;
}
