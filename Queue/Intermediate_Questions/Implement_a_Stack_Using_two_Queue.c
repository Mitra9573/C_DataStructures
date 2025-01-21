#include <stdio.h>
#include <stdlib.h>

// Node structure to hold the data and pointer to the next node
struct Node {
    int data;
    struct Node* next;
};

// Stack and auxiliary queue structures
struct Node* primaryQueueFront = NULL;
struct Node* primaryQueueRear = NULL;
struct Node* auxiliaryQueueFront = NULL;
struct Node* auxiliaryQueueRear = NULL;

// Function to create a new node with the given data
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Enqueue operation: Adds data to the end of the queue
void enqueue(struct Node** front, struct Node** rear, int data) {
    struct Node* newNode = createNode(data);
    if (*rear == NULL) {
        *front = *rear = newNode;
        return;
    }
    (*rear)->next = newNode;
    *rear = newNode;
}

// Dequeue operation: Removes data from the front of the queue
int dequeue(struct Node** front, struct Node** rear) {
    if (*front == NULL) {
        printf("Queue is empty!\n");
        return -1;
    }
    struct Node* temp = *front;
    int data = temp->data;
    *front = (*front)->next;
    if (*front == NULL) {
        *rear = NULL;
    }
    free(temp);
    return data;
}

// Check if the queue is empty
int isEmpty(struct Node* front) {
    return front == NULL;
}

// Push operation: Adds data to the stack using the primary queue
void push(int data) {
    enqueue(&primaryQueueFront, &primaryQueueRear, data);
}

// Pop operation: Removes data from the stack using two queues
int pop() {
    if (isEmpty(primaryQueueFront)) {
        printf("Stack is empty!\n");
        return -1;
    }

    // Transfer all elements except the last one to the auxiliary queue
    while (primaryQueueFront->next != NULL) {
        int data = dequeue(&primaryQueueFront, &primaryQueueRear);
        enqueue(&auxiliaryQueueFront, &auxiliaryQueueRear, data);
    }

    // The last element in primaryQueueFront is the popped element
    int poppedData = dequeue(&primaryQueueFront, &primaryQueueRear);

    // Swap the roles of primary and auxiliary queues
    struct Node* tempFront = primaryQueueFront;
    struct Node* tempRear = primaryQueueRear;
    primaryQueueFront = auxiliaryQueueFront;
    primaryQueueRear = auxiliaryQueueRear;
    auxiliaryQueueFront = tempFront;
    auxiliaryQueueRear = tempRear;

    return poppedData;
}

// Display the current elements in the stack
void displayStack() {
    if (isEmpty(primaryQueueFront)) {
        printf("Stack is empty!\n");
        return;
    }

    struct Node* temp = primaryQueueFront;
    printf("Stack: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function to drive the program
int main() {
    int choice, data;

    do {
        printf("\nStack Operations using Two Queues:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to push: ");
                scanf("%d", &data);
                push(data);
                break;

            case 2:
                data = pop();
                if (data != -1) {
                    printf("Popped: %d\n", data);
                }
                break;

            case 3:
                displayStack();
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    // Free memory allocated for the queues
    while (!isEmpty(primaryQueueFront)) {
        dequeue(&primaryQueueFront, &primaryQueueRear);
    }
    while (!isEmpty(auxiliaryQueueFront)) {
        dequeue(&auxiliaryQueueFront, &auxiliaryQueueRear);
    }

    return 0;
}
