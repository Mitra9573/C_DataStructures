#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int value;
    struct ListNode* next;
};

struct ListNode* createListNode(int value) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void appendToList(struct ListNode** head, int value) {
    struct ListNode* newNode = createListNode(value);
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

void printList(struct ListNode* head) {
    struct ListNode* current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int calculateLength(struct ListNode* head) {
    int count = 0;
    struct ListNode* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void rotateLeft(struct ListNode** head, int positions) {
    if (*head == NULL || positions == 0) return;

    int length = calculateLength(*head);
    positions = positions % length;

    if (positions == 0) return;

    struct ListNode* current = *head;
    int steps = 1;
    while (steps < positions && current != NULL) {
        current = current->next;
        steps++;
    }

    struct ListNode* newHead = current->next;
    current->next = NULL;

    struct ListNode* tail = newHead;
    while (tail != NULL && tail->next != NULL) {
        tail = tail->next;
    }

    if (tail != NULL) {
        tail->next = *head;
    }

    *head = newHead;
}

void rotateRight(struct ListNode** head, int positions) {
    if (*head == NULL || positions == 0) return;

    int length = calculateLength(*head);
    positions = positions % length;

    if (positions == 0) return;

    rotateLeft(head, length - positions);
}

int main() {
    struct ListNode* head = NULL;
    int inputValue, rotations, direction;

    printf("Enter elements for the linked list (enter -1 to stop):\n");
    while (1) {
        printf("Enter value: ");
        scanf("%d", &inputValue);
        if (inputValue == -1) break;
        appendToList(&head, inputValue);
    }

    printf("Original Linked List: ");
    printList(head);

    printf("Enter the number of positions to rotate: ");
    scanf("%d", &rotations);

    printf("Choose rotation direction:\n1. Left Rotation\n2. Right Rotation\n");
    scanf("%d", &direction);

    if (direction == 1) {
        rotateLeft(&head, rotations);
        printf("List after left rotation by %d positions: ", rotations);
    } else if (direction == 2) {
        rotateRight(&head, rotations);
        printf("List after right rotation by %d positions: ", rotations);
    } else {
        printf("Invalid choice.\n");
        return 0;
    }

    printList(head);
    return 0;
}
