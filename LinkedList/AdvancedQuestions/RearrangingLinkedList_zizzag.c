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

// Function to append a node to the linked list
void appendNode(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// Rearrange the linked list in zigzag order using modified logic
void rearrangeZigzag(struct Node* head) {
    int isLessThan = 1;  // 1 indicates "<" condition, 0 indicates ">" condition
    struct Node* current = head;

    while (current != NULL && current->next != NULL) {
        if ((isLessThan && current->value > current->next->value) || 
            (!isLessThan && current->value < current->next->value)) {
            // Swap values if the condition is not met
            int temp = current->value;
            current->value = current->next->value;
            current->next->value = temp;
        }
        isLessThan = !isLessThan;  // Toggle the condition
        current = current->next;
    }
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

// Main function to interact with the linked list
int main() {
    struct Node* head = NULL;
    int choice, inputValue;

    while (1) {
        printf("\n1. Append node\n2. Rearrange in zigzag order\n3. Display list\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to append: ");
                scanf("%d", &inputValue);
                appendNode(&head, inputValue);
                break;
            case 2:
                rearrangeZigzag(head);
                printf("List rearranged in zigzag order.\n");
                break;
            case 3:
                printf("Current List: ");
                displayList(head);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
