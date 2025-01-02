#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the linked list
struct ListNode {
    int value;
    struct ListNode* next;
};

// Function to create a new node
struct ListNode* createNewNode(int value) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to find the middle node of the linked list
struct ListNode* findMiddleNode(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct ListNode* slowPointer = head;
    struct ListNode* fastPointer = head->next;

    while (fastPointer != NULL && fastPointer->next != NULL) {
        slowPointer = slowPointer->next;
        fastPointer = fastPointer->next->next;
    }
    return slowPointer;
}

// Function to merge two sorted linked lists
struct ListNode* mergeSortedLists(struct ListNode* left, struct ListNode* right) {
    struct ListNode dummyNode;
    struct ListNode* mergedTail = &dummyNode;
    dummyNode.next = NULL;

    while (left != NULL && right != NULL) {
        if (left->value <= right->value) {
            mergedTail->next = left;
            left = left->next;
        } else {
            mergedTail->next = right;
            right = right->next;
        }
        mergedTail = mergedTail->next;
    }

    // Attach the remaining nodes
    if (left != NULL) {
        mergedTail->next = left;
    } else {
        mergedTail->next = right;
    }

    return dummyNode.next;
}

// Function to perform merge sort on the linked list
struct ListNode* performMergeSort(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct ListNode* middleNode = findMiddleNode(head);
    struct ListNode* secondHalf = middleNode->next;
    middleNode->next = NULL;

    struct ListNode* leftSorted = performMergeSort(head);
    struct ListNode* rightSorted = performMergeSort(secondHalf);

    return mergeSortedLists(leftSorted, rightSorted);
}

// Function to print the linked list
void displayList(struct ListNode* head) {
    struct ListNode* currentNode = head;
    while (currentNode != NULL) {
        printf("%d ", currentNode->value);
        currentNode = currentNode->next;
    }
    printf("\n");
}

// Main function
int main() {
    struct ListNode* head = createNewNode(50);
    head->next = createNewNode(10);
    head->next->next = createNewNode(30);
    head->next->next->next = createNewNode(20);
    head->next->next->next->next = createNewNode(40);

    printf("Original list:\n");
    displayList(head);

    head = performMergeSort(head);

    printf("Sorted list:\n");
    displayList(head);

    return 0;
}
