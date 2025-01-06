#include <stdio.h>
#include <stdlib.h>

// Node structure for a doubly linked list
struct Node {
    int value;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the tail (end) of the list
void insertAtTail(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to display the list
void displayList(struct Node* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    printf("List: ");
    while (head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

// Function to reverse the doubly linked list
void reverseList(struct Node** head) {
    if (*head == NULL) return;

    struct Node* temp = NULL;
    struct Node* current = *head;

    // Swap the next and prev pointers for all nodes
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev; // Move to the next node
    }

    // Adjust head pointer
    if (temp != NULL) {
        *head = temp->prev;
    }
}

// Main function
int main() {
    struct Node* head = NULL;
    int userChoice, userValue;

    printf("Doubly Linked List Operations:\n");
    printf("1. Insert at Tail\n");
    printf("2. Display List\n");
    printf("3. Reverse List\n");
    printf("4. Exit\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &userValue);
                insertAtTail(&head, userValue);
                break;

            case 2:
                displayList(head);
                break;

            case 3:
                reverseList(&head);
                printf("List has been reversed.\n");
                break;

            case 4:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
