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

void swapListNodes(struct ListNode** head, int val1, int val2) {
    if (val1 == val2) return;

    struct ListNode *prev1 = NULL, *current1 = *head;
    struct ListNode *prev2 = NULL, *current2 = *head;

    while (current1 != NULL && current1->value != val1) {
        prev1 = current1;
        current1 = current1->next;
    }

    while (current2 != NULL && current2->value != val2) {
        prev2 = current2;
        current2 = current2->next;
    }

    if (current1 == NULL || current2 == NULL) {
        printf("One or both nodes not found.\n");
        return;
    }

    if (prev1 != NULL) {
        prev1->next = current2;
    } else {
        *head = current2;
    }

    if (prev2 != NULL) {
        prev2->next = current1;
    } else {
        *head = current1;
    }

    struct ListNode* temp = current1->next;
    current1->next = current2->next;
    current2->next = temp;
}

int main() {
    struct ListNode* head = NULL;
    int inputValue, val1, val2;

    printf("Enter elements for the linked list (enter -1 to stop):\n");
    while (1) {
        printf("Enter value: ");
        scanf("%d", &inputValue);
        if (inputValue == -1) break;
        appendToList(&head, inputValue);
    }

    printf("Original Linked List: ");
    printList(head);

    printf("Enter two values to swap: ");
    scanf("%d %d", &val1, &val2);

    swapListNodes(&head, val1, val2);

    printf("Linked List after swapping nodes %d and %d: ", val1, val2);
    printList(head);

    return 0;
}
