#include <stdio.h>
#include <stdlib.h>

// Node structure for the linked list
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

// Function to reverse k nodes in the linked list
struct Node* reverseKNodes(struct Node* head, int k, int reverse) {
    if (head == NULL || k <= 0) {
        return head;
    }

    struct Node* current = head;
    struct Node* prev = NULL;
    struct Node* next = NULL;
    int count = 0;

    // If reverse is 1, reverse k nodes
    if (reverse) {
        while (current != NULL && count < k) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
            count++;
        }
        // Recursively reverse the remaining nodes
        if (next != NULL) {
            head->next = reverseKNodes(next, k, 0);
        }
        return prev;
    } else {
        // Skip k nodes without reversing
        while (current != NULL && count < k) {
            prev = current;
            current = current->next;
            count++;
        }
        // Recursively reverse the next k nodes
        if (current != NULL) {
            prev->next = reverseKNodes(current, k, 1);
        }
        return head;
    }
}

// Function to print the linked list
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

// Main function
int main() {
    int numNodes, groupSize, nodeValue;
    struct Node* head = NULL;
    struct Node* tail = NULL;

    // Dynamic input for the number of nodes
    printf("Enter the number of nodes in the linked list: ");
    scanf("%d", &numNodes);

    // Dynamically create the linked list based on user input
    printf("Enter the values of the nodes:\n");
    for (int i = 0; i < numNodes; i++) {
        scanf("%d", &nodeValue);
        struct Node* newNode = createNode(nodeValue);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Dynamic input for the value of k
    printf("Enter the value of k (group size for reversal): ");
    scanf("%d", &groupSize);

    // Display the original list
    printf("Original linked list:\n");
    printList(head);

    // Reverse k nodes at a time
    head = reverseKNodes(head, groupSize, 1);

    // Display the modified list
    printf("Modified linked list (Reversed alternate k nodes):\n");
    printList(head);

    return 0;
}
