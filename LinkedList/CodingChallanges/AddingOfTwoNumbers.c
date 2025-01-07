#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a node in the linked list
struct Node {
    int digit;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int digit) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->digit = digit;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the tail of the list
void insertAtTail(struct Node** head, int digit) {
    struct Node* newNode = createNode(digit);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to reverse a linked list
struct Node* reverseList(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

// Function to add two large numbers represented by linked lists
struct Node* addLargeNumbers(struct Node* num1, struct Node* num2) {
    struct Node* result = NULL;
    int carry = 0;

    // Traverse through both lists and add digits
    while (num1 != NULL || num2 != NULL || carry > 0) {
        int sum = carry;

        if (num1 != NULL) {
            sum += num1->digit;
            num1 = num1->next;
        }

        if (num2 != NULL) {
            sum += num2->digit;
            num2 = num2->next;
        }

        carry = sum / 10;
        sum = sum % 10;

        // Insert the sum digit at the tail of the result
        insertAtTail(&result, sum);
    }

    return result;
}

// Function to display the linked list (representing the number)
void display(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d", current->digit);
        current = current->next;
    }
    printf("\n");
}

// Function to create a linked list from a string representation of a number
struct Node* createListFromString(char* number) {
    struct Node* head = NULL;
    int length = strlen(number);

    // Iterate the number string in reverse order to create the list
    for (int i = length - 1; i >= 0; i--) {
        insertAtTail(&head, number[i] - '0');
    }

    return head;
}

// Main function
int main() {
    char *num1, *num2;

    // Dynamically allocate memory for input strings
    num1 = (char*)malloc(1000 * sizeof(char));
    num2 = (char*)malloc(1000 * sizeof(char));

    if (num1 == NULL || num2 == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // Input for two large numbers as strings
    printf("Enter the first large number: ");
    scanf("%s", num1);

    printf("Enter the second large number: ");
    scanf("%s", num2);

    // Create linked lists from the input strings
    struct Node* list1 = createListFromString(num1);
    struct Node* list2 = createListFromString(num2);

    // Add the two numbers
    struct Node* result = addLargeNumbers(list1, list2);

    // Reverse the result to display in correct order
    result = reverseList(result);

    // Display the result
    printf("The sum is: ");
    display(result);

    // Free dynamically allocated memory
    free(num1);
    free(num2);

    return 0;
}
