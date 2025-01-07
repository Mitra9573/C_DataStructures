#include <stdio.h>
#include <stdlib.h>

// Node structure for a singly linked list
struct Node {
    int value;         // Data for the node
    struct Node* next; // Pointer to the next node
};

// Function to create a new node
struct Node* createNode(int value) {
       
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to merge two sorted lists
struct Node* mergeTwoLists(struct Node* list1, struct Node* list2) {
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;

    struct Node* mergedList = NULL;

    if (list1->value < list2->value) {
        mergedList = list1;
        mergedList->next = mergeTwoLists(list1->next, list2);
    } else {
        mergedList = list2;
        mergedList->next = mergeTwoLists(list1, list2->next);
    }

    return mergedList;
}

// Function to merge k sorted linked lists
struct Node* mergeKLists(struct Node* lists[], int k) {
    if (k == 0) return NULL;
    if (k == 1) return lists[0];
    
    int mid = k / 2;
    struct Node* left = mergeKLists(lists, mid);
    struct Node* right = mergeKLists(lists + mid, k - mid);

    return mergeTwoLists(left, right);
}

// Function to print a linked list
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

// Function to create a user-defined sorted linked list
struct Node* createUserList() {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    int size, data;

    printf("Enter the number of elements in the list: ");
    scanf("%d", &size);

    for (int i = 0; i < size; i++) {
        printf("Enter data for element %d: ", i + 1);
        scanf("%d", &data);
        struct Node* newNode = createNode(data);

        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}

int main() {
    int k;

    // Ask for the number of sorted linked lists
    printf("Enter the number of sorted linked lists (k): ");
    scanf("%d", &k);

    // Dynamically allocate space for the array of lists
    struct Node* lists[k];

    // Create k sorted linked lists
    for (int i = 0; i < k; i++) {
        printf("Creating sorted linked list %d:\n", i + 1);
        lists[i] = createUserList();
    }

    // Merge the k sorted linked lists
    printf("\nMerging all sorted linked lists...\n");
    struct Node* mergedList = mergeKLists(lists, k);

    // Print the merged sorted linked list
    printf("Merged sorted linked list:\n");
    printList(mergedList);

    return 0;
}
