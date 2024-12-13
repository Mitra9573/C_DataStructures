#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int value;
    struct ListNode* next;
};

struct ListNode* createNode(int value) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

struct ListNode* findMiddle(struct ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    struct ListNode* slow = head;
    struct ListNode* fast = head;

    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

struct ListNode* mergeLists(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    dummy.next = NULL;

    while (list1 && list2) {
        if (list1->value <= list2->value) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    if (list1) {
        tail->next = list1;
    } else {
        tail->next = list2;
    }

    return dummy.next;
}

struct ListNode* sortList(struct ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    struct ListNode* middle = findMiddle(head);
    struct ListNode* secondHalf = middle->next;
    middle->next = NULL;

    struct ListNode* left = sortList(head);
    struct ListNode* right = sortList(secondHalf);

    return mergeLists(left, right);
}

void printList(struct ListNode* head) {
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct ListNode* head = createNode(5);
    head->next = createNode(1);
    head->next->next = createNode(8);
    head->next->next->next = createNode(3);
    head->next->next->next->next = createNode(6);

    printf("Original list:\n");
    printList(head);

    head = sortList(head);

    printf("Sorted list:\n");
    printList(head);

    return 0;
}
