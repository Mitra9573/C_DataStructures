#include <stdio.h>
#include <stdlib.h>

// Node structure for the doubly linked list
struct Node {
    int value;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the list
void insertAtTail(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to display the list
void displayList(struct Node* head) {
    printf("List: ");
    while (head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

// Function to find pairs with a given sum
void findPairs(struct Node* head, int targetSum) {
    struct Node* left = head;
    struct Node* right = head;

    // Move 'right' to the last node
    while (right->next != NULL) {
        right = right->next;
    }

    int found = 0;
    printf("Pairs with sum %d:\n", targetSum);
    while (left != NULL && right != NULL && left != right && right->next != left) {
        int currentSum = left->value + right->value;

        if (currentSum == targetSum) {
            printf("(%d, %d)\n", left->value, right->value);
            found = 1;
            left = left->next;
            right = right->prev;
        } else if (currentSum < targetSum) {
            left = left->next;
        } else {
            right = right->prev;
        }
    }

    if (!found) {
        printf("No pairs found.\n");
    }
}

// Main function
int main() {
    struct Node* head = NULL;
    int userChoice, userValue, targetSum;

    printf("\nMenu:\n");
    printf("1. Insert element\n");
    printf("2. Display list\n");
    printf("3. Find pairs with a target sum\n");
    printf("4. Exit\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &userValue);
                insertAtTail(&head, userValue);
                break;

            case 2:
                displayList(head);
                break;

            case 3:
                if (head == NULL) {
                    printf("The list is empty. Please insert elements first.\n");
                } else {
                    printf("Enter the target sum: ");
                    scanf("%d", &targetSum);
                    findPairs(head, targetSum);
                }
                break;

            case 4:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
