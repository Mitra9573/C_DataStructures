#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the structure for a linked list node
struct ListNode {
    int value;
    struct ListNode* nextNode;
};

// Function to create a new node
struct ListNode* createNewNode(int value) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
    newNode->value = value;
    newNode->nextNode = NULL;
    return newNode;
}

// Function to append a node to the list
void appendToList(struct ListNode** head, int value) {
    struct ListNode* newNode = createNewNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct ListNode* currentNode = *head;
    while (currentNode->nextNode != NULL) {
        currentNode = currentNode->nextNode;
    }
    currentNode->nextNode = newNode;
}

// Function to display the linked list
void printList(struct ListNode* head) {
    struct ListNode* currentNode = head;
    while (currentNode != NULL) {
        printf("%d ", currentNode->value);
        currentNode = currentNode->nextNode;
    }
    printf("\n");
}

// Function to remove duplicate values from the list
void removeDuplicateValues(struct ListNode* head) {
    struct ListNode* currentNode = head;
    struct ListNode* previousNode = NULL;
    struct ListNode* tempNode = NULL;
    bool valueSeen[1000] = {0};

    while (currentNode != NULL) {
        if (valueSeen[currentNode->value]) {
            previousNode->nextNode = currentNode->nextNode;
            free(currentNode);
        } else {
            valueSeen[currentNode->value] = true;
            previousNode = currentNode;
        }
        currentNode = previousNode->nextNode;
    }
}

int main() {
    struct ListNode* head = NULL;
    int inputValue;

    printf("Enter elements for the linked list (enter -1 to stop):\n");
    while (true) {
        printf("Enter value: ");
        scanf("%d", &inputValue);
        if (inputValue == -1) break;
        appendToList(&head, inputValue);
    }

    printf("Linked List before removing duplicates: ");
    printList(head);

    removeDuplicateValues(head);

    printf("Linked List after removing duplicates: ");
    printList(head);

    return 0;
}
