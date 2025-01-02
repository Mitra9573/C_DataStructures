#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the linked list
struct Node {
    int value;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to append a node to the linked list
void appendNode(struct Node** headRef, int value) {
    struct Node* newNode = createNode(value);
    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    struct Node* currentNode = *headRef;
    while (currentNode->next != NULL) {
        currentNode = currentNode->next;
    }
    currentNode->next = newNode;
}

// Function to reverse nodes in groups of k
struct Node* reverseKGroup(struct Node* head, int k) {
    struct Node* currentNode = head;
    struct Node* previousNode = NULL;
    struct Node* nextNode = NULL;
    int count = 0;

    // Count the total number of nodes
    struct Node* tempNode = head;
    int totalNodes = 0;
    while (tempNode) {
        totalNodes++;
        tempNode = tempNode->next;
    }

    // If there are fewer than k nodes, return the list as is
    if (totalNodes < k) {
        return head;
    }

    // Reverse the first k nodes
    while (currentNode != NULL && count < k) {
        nextNode = currentNode->next;
        currentNode->next = previousNode;
        previousNode = currentNode;
        currentNode = nextNode;
        count++;
    }

    // After reversing, 'nextNode' is the start of the next group
    if (nextNode != NULL) {
        head->next = reverseKGroup(nextNode, k);
    }

    // 'previousNode' is the new head after reversing k nodes
    return previousNode;
}

// Function to display the linked list
void displayList(struct Node* head) {
    struct Node* currentNode = head;
    while (currentNode != NULL) {
        printf("%d ", currentNode->value);
        currentNode = currentNode->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int userChoice, inputValue, groupSize;

    while (1) {
        printf("\n1. Append node\n2. Reverse in k groups\n3. Display list\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                printf("Enter value to append: ");
                scanf("%d", &inputValue);
                appendNode(&head, inputValue);
                break;
            case 2:
                printf("Enter the value of k: ");
                scanf("%d", &groupSize);
                head = reverseKGroup(head, groupSize);
                printf("List reversed in groups of %d.\n", groupSize);
                break;
            case 3:
                printf("Current List: ");
                displayList(head);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
