#include <stdio.h>
#include <stdlib.h>

// Node structure for the linked list with child pointers
struct Node {
       
    int value;        // Data for the node
    struct Node* next;  // Pointer to the next node in the main list
    struct Node* child; // Pointer to the head of the child list
};

// Function to create a new node with dynamic memory allocation
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->value = value;
    newNode->next = NULL;
    newNode->child = NULL;
    return newNode;
}

// Function to merge two sorted lists
struct Node* mergeLists(struct Node* list1, struct Node* list2) {
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;

    struct Node* result;

    if (list1->value < list2->value) {
        result = list1;
        result->child = mergeLists(list1->child, list2);
    } else {
        result = list2;
        result->child = mergeLists(list1, list2->child);
    }

    return result;
}

// Function to flatten the list
struct Node* flattenList(struct Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Recursively flatten the next part of the list
    head->next = flattenList(head->next);

    // Merge current node's child list with the flattened next list
    head = mergeLists(head, head->next);

    return head;
}

// Function to print the flattened list
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->child;
    }
    printf("\n");
}

// Function to dynamically create the linked list with user input
struct Node* createDynamicList() {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    int mainListSize, data, childCount;

    printf("Enter the number of nodes in the main list: ");
    scanf("%d", &mainListSize);

    for (int i = 0; i < mainListSize; i++) {
        printf("Enter value for node %d in the main list: ", i + 1);
        scanf("%d", &data);

        struct Node* newNode = createNode(data);

        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        printf("Enter the number of child nodes for node %d: ", i + 1);
        scanf("%d", &childCount);

        struct Node* childHead = NULL;
        struct Node* childTail = NULL;

        for (int j = 0; j < childCount; j++) {
            printf("Enter value for child node %d of node %d: ", j + 1, i + 1);
            scanf("%d", &data);
            struct Node* childNode = createNode(data);

            if (childHead == NULL) {
                childHead = childTail = childNode;
            } else {
                childTail->child = childNode;
                childTail = childNode;
            }
        }
        newNode->child = childHead;
    }

    return head;
}

// Main function
int main() {
    struct Node* head = createDynamicList();

    struct Node* flattenedList = flattenList(head);

    printf("\nFlattened sorted linked list:\n");
    printList(flattenedList);

    return 0;
}
