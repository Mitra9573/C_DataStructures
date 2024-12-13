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

// Function to append a node to the end of the list
void appendToEnd(struct ListNode** head, int value) {
    struct ListNode* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct ListNode* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// Function to display the linked list
void displayList(struct ListNode* head) {
    struct ListNode* current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

// Function to detect a loop in the linked list
int hasLoop(struct ListNode* head) {
    struct ListNode *slowPointer = head, *fastPointer = head;
    while (fastPointer != NULL && fastPointer->next != NULL) {
        slowPointer = slowPointer->next;
        fastPointer = fastPointer->next->next;
        if (slowPointer == fastPointer) {
            return 1;
        }
    }
    return 0;
}

// Function to remove a loop from the linked list
void removeLoop(struct ListNode* head) {
    struct ListNode *slowPointer = head, *fastPointer = head;

    if (!hasLoop(head)) {
        printf("No loop detected.\n");
        return;
    }

    // Detect the meeting point of slow and fast pointers
    while (fastPointer != NULL && fastPointer->next != NULL) {
        slowPointer = slowPointer->next;
        fastPointer = fastPointer->next->next;

        if (slowPointer == fastPointer) {
            break;
        }
    }

    // Find the start of the loop
    slowPointer = head;
    while (slowPointer != fastPointer) {
        slowPointer = slowPointer->next;
        fastPointer = fastPointer->next;
    }

    // Break the loop
    struct ListNode* loopStart = slowPointer;
    while (fastPointer->next != loopStart) {
        fastPointer = fastPointer->next;
    }
    fastPointer->next = NULL;
    printf("Loop removed.\n");
}

int main() {
    struct ListNode* head = NULL;
    int userValue, loopPosition;

    printf("Enter elements for the linked list (enter -1 to stop):\n");
    while (1) {
        printf("Enter value: ");
        scanf("%d", &userValue);
        if (userValue == -1) break;
        appendToEnd(&head, userValue);
    }

    printf("Linked List: ");
    displayList(head);

    printf("Enter position to create a loop (0-based index, -1 for no loop): ");
    scanf("%d", &loopPosition);

    if (loopPosition != -1) {
        struct ListNode* current = head;
        struct ListNode* loopNode = NULL;
        int index = 0;

        while (current->next != NULL) {
            if (index == loopPosition) {
                loopNode = current;
            }
            current = current->next;
            index++;
        }

        if (loopNode != NULL) {
            current->next = loopNode;
            printf("Loop created at position %d.\n", loopPosition);
        }
    }

    removeLoop(head);

    printf("Modified List: ");
    displayList(head);

    return 0;
}
