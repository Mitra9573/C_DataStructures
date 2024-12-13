#include <stdio.h>
#include <stdlib.h>

// Define the structure for a linked list node
struct ListNode {
    int value;
    struct ListNode* next;
};

// Function to create a new node
struct ListNode* createNode(int value) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the list
struct ListNode* appendToEnd(struct ListNode* head, int value) {
    struct ListNode* newNode = createNode(value);
    if (head == NULL) {
        return newNode; // If the list is empty, newNode becomes the head
    }
    struct ListNode* current = head;
    while (current->next != NULL) {
        current = current->next; // Traverse to the end of the list
    }
    current->next = newNode;
    return head;
}

// Function to display the linked list
void displayLinkedList(struct ListNode* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    struct ListNode* current = head;
    printf("Linked List: ");
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

// Function to find the nth node from the end of the list
struct ListNode* findNthFromEnd(struct ListNode* head, int positionFromEnd) {
    struct ListNode* forwardPointer = head;
    struct ListNode* targetPointer = head;

    // Move the 'forwardPointer' positionFromEnd steps ahead
    for (int step = 0; step < positionFromEnd; step++) {
        if (forwardPointer == NULL) {
            return NULL; // If the list has fewer than positionFromEnd nodes
        }
        forwardPointer = forwardPointer->next;
    }

    // Move both pointers until the 'forwardPointer' reaches the end
    while (forwardPointer != NULL) {
        forwardPointer = forwardPointer->next;
        targetPointer = targetPointer->next;
    }

    return targetPointer; // The 'targetPointer' is now at the nth node from the end
}

// Main function
int main() {
    struct ListNode* head = NULL;
    int inputValue, position;

    printf("Enter elements for the linked list (enter -1 to finish):\n");
    while (1) {
        printf("Enter value: ");
        scanf("%d", &inputValue);
        if (inputValue == -1) break; // Stop when the user enters -1
        head = appendToEnd(head, inputValue); // Add the value to the end of the list
    }

    displayLinkedList(head);

    printf("Enter the position from the end to find: ");
    scanf("%d", &position);

    struct ListNode* resultNode = findNthFromEnd(head, position);
    if (resultNode != NULL) {
        printf("The %dth node from the end is: %d\n", position, resultNode->value);
    } else {
        printf("The list has fewer than %d nodes.\n", position);
    }

    return 0;
}
