#include <stdio.h>
#include <stdlib.h>

// Define the structure for a linked list node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to add a node to the end of the list
void addNode(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
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

// Function to display the elements of the linked list
void displayList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to remove duplicate nodes from the list
void removeDuplicates(struct Node* head) {
    struct Node* current = head;
    struct Node* prev = NULL;
    struct Node* temp = NULL;
    int seen[1000] = {0};

    while (current != NULL) {
        if (seen[current->data]) {
            prev->next = current->next;
            free(current);
        } else {
            seen[current->data] = 1;
            prev = current;
        }
        current = prev->next;
    }
}

int main() {
    struct Node* head = NULL;
    int value;

    printf("Enter elements for the linked list (enter -1 to stop):\n");
    while (1) {
        printf("Enter value: ");
        scanf("%d", &value);
        if (value == -1) break;
        addNode(&head, value);
    }

    printf("Linked List before removing duplicates: ");
    displayList(head);

    removeDuplicates(head);

    printf("Linked List after removing duplicates: ");
    displayList(head);

    return 0;
}
