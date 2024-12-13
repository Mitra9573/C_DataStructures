#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* random;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->random = NULL;
    return newNode;
}

void displayList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("Data: %d", current->data);
        if (current->random != NULL) {
            printf(", Random points to: %d", current->random->data);
        } else {
            printf(", Random points to: NULL");
        }
        printf("\n");
        current = current->next;
    }
    printf("\n");
}

void insertClones(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* clone = createNode(current->data);
        clone->next = current->next;
        current->next = clone;
        current = clone->next;
    }
}

void updateRandomPointers(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        if (current->random != NULL) {
            current->next->random = current->random->next;
        }
        current = current->next->next;
    }
}

struct Node* separateClonedList(struct Node* head) {
    struct Node* current = head;
    struct Node* clonedHead = NULL;
    struct Node* clonedTail = NULL;

    while (current != NULL) {
        struct Node* clone = current->next;
        current->next = clone->next;

        if (clonedHead == NULL) {
            clonedHead = clone;
            clonedTail = clone;
        } else {
            clonedTail->next = clone;
            clonedTail = clone;
        }

        current = current->next;
    }

    return clonedHead;
}

int main() {
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);

    head->random = head->next->next;
    head->next->random = head;
    head->next->next->random = head->next->next->next;
    head->next->next->next->random = head->next;

    printf("Original List with Random Pointers:\n");
    displayList(head);

    insertClones(head);
    updateRandomPointers(head);
    struct Node* clonedHead = separateClonedList(head);

    printf("Original List after Separation:\n");
    displayList(head);

    printf("Cloned List:\n");
    displayList(clonedHead);

    return 0;
}
