#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the list
void insertAtHead(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// Function to insert a node at the end of the list
void insertAtTail(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
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

// Function to delete a node from the list
void deleteNode(struct Node** head, int data) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = *head;

    // Find the node to be deleted
    while (temp != NULL && temp->data != data) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Node with value %d not found.\n", data);
        return;
    }

    // Update pointers to remove the node
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else { // If the node is the head
        *head = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    free(temp);
    printf("Node with value %d deleted.\n", data);
}

// Function to traverse the list forward
void traverseForward(struct Node* head) {
    printf("List (forward): ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Function to traverse the list backward
void traverseBackward(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    // Move to the end of the list
    while (head->next != NULL) {
        head = head->next;
    }
    printf("List (backward): ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->prev;
    }
    printf("\n");
}

// Main function
int main() {
    struct Node* head = NULL;
    int userChoice, userData;

    printf("Doubly Linked List Operations:\n");
    printf("1. Insert at Head\n");
    printf("2. Insert at Tail\n");
    printf("3. Delete Node\n");
    printf("4. Traverse Forward\n");
    printf("5. Traverse Backward\n");
    printf("6. Exit\n");

    while (1) {
        printf("\nEnter your choice (1-6): ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                printf("Enter value to insert at head: ");
                scanf("%d", &userData);
                insertAtHead(&head, userData);
                break;
            case 2:
                printf("Enter value to insert at tail: ");
                scanf("%d", &userData);
                insertAtTail(&head, userData);
                break;
            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &userData);
                deleteNode(&head, userData);
                break;
            case 4:
                traverseForward(head);
                break;
            case 5:
                traverseBackward(head);
                break;
            case 6:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
