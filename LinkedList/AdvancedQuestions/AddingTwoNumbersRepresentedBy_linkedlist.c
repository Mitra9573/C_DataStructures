#include <stdio.h>
#include <stdlib.h>

// Node structure
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

// Function to append a node to the list
void appendNode(struct Node** headRef, int value) {
    struct Node* newNode = createNode(value);
    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    struct Node* tempNode = *headRef;
    while (tempNode->next != NULL) {
        tempNode = tempNode->next;
    }
    tempNode->next = newNode;
}

// Function to print the list
void printList(struct Node* head) {
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

// Function to reverse a linked list
struct Node* reverseList(struct Node* head) {
    struct Node* prevNode = NULL;
    struct Node* currentNode = head;
    struct Node* nextNode = NULL;

    while (currentNode) {
        nextNode = currentNode->next;
        currentNode->next = prevNode;
        prevNode = currentNode;
        currentNode = nextNode;
    }
    return prevNode;
}

// Function to add two numbers represented as linked lists
struct Node* addTwoNumbers(struct Node* list1, struct Node* list2) {
    struct Node* resultList = NULL;
    struct Node** resultTail = &resultList;
    int carryOver = 0;

    while (list1 || list2 || carryOver) {
        int sum = carryOver;

        if (list1) {
            sum += list1->value;
            list1 = list1->next;
        }
        if (list2) {
            sum += list2->value;
            list2 = list2->next;
        }

        int digit = sum % 10;
        carryOver = sum / 10;

        *resultTail = createNode(digit);
        resultTail = &((*resultTail)->next);
    }

    return resultList;
}

// Main function
int main() {
    struct Node* number1 = NULL;
    struct Node* number2 = NULL;

    // Create the first number
    appendNode(&number1, 3);
    appendNode(&number1, 4);
    appendNode(&number1, 2);

    // Create the second number
    appendNode(&number2, 4);
    appendNode(&number2, 6);
    appendNode(&number2, 5);

    printf("First number: ");
    printList(number1);
    printf("Second number: ");
    printList(number2);

    // Reverse the lists
    number1 = reverseList(number1);
    number2 = reverseList(number2);

    // Add the two numbers
    struct Node* sumList = addTwoNumbers(number1, number2);

    // Reverse the result to match the correct order
    sumList = reverseList(sumList);

    printf("Sum: ");
    printList(sumList);

    return 0;
}
