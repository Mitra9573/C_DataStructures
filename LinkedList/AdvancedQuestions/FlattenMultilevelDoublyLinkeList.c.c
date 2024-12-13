#include <stdio.h>
#include <stdlib.h>

// Define the structure for a multilevel doubly linked list node
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
    struct Node* child;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->child = NULL;
    return newNode;
}

// Function to flatten the multilevel linked list
struct Node* flatten(struct Node* head) {
    struct Node* current = head;

    while (current) {
        if (current->child) {
            struct Node* child = flatten(current->child);
            struct Node* next = current->next;

            current->next = child;
            child->prev = current;
            current->child = NULL;

            struct Node* tail = child;
            while (tail->next) {
                tail = tail->next;
            }
            if (next) {
                tail->next = next;
                next->prev = tail;
            }
        }
        current = current->next;
    }

    return head;
}

// Function to display the list
void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to get user input and build the list
struct Node* createList() {
    int value, hasChild;
    struct Node *head = NULL, *tail = NULL;

    printf("Enter values for the list (-1 to stop):\n");
    while (1) {
        printf("Enter value: ");
        scanf("%d", &value);
        if (value == -1) break;

        struct Node* newNode = createNode(value);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        printf("Does this node have a child? (1 for yes, 0 for no): ");
        scanf("%d", &hasChild);
        if (hasChild) {
            printf("Creating child list for node %d:\n", value);
            newNode->child = createList();
        }
    }

    return head;
}

// Main function
int main() {
    struct Node* head = NULL;

    printf("Create the multilevel doubly linked list:\n");
    head = createList();

    printf("\nOriginal list:\n");
    displayList(head);

    head = flatten(head);

    printf("\nFlattened list:\n");
    displayList(head);

    return 0;
}
